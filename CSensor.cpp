//#include "stdafx.h"
#include "CSensor.h"


CSensor::CSensor()
{
	open("Pi");
	
	CSensor::_distance = 0;
	
	//Initiate the pins
	gpioSetMode(TRIGGER, PI_OUTPUT);
	gpioSetMode(ECHO, PI_INPUT);
	
}

int CSensor::open(std::string comm)
{
	if (gpioInitialise() < 0)
		return 1;
	else
		return 2;
}

void CSensor::sonarTrigger(void)
{
   /* trigger a sonar reading */

   gpioWrite(TRIGGER, HIGH);

   gpioDelay(10); /* 10us trigger pulse */

   gpioWrite(TRIGGER, LOW);
}

void CSensor::sonarEcho(int gpio, int level, uint32_t tick)
{
   static uint32_t startTick, firstTick=0;

   int diffTick;

   if (!firstTick) firstTick = tick;

   if (level == PI_ON)
   {
      startTick = tick;
   }
   else if (level == PI_OFF)
   {
	  // double dist = 0;
      diffTick = tick - startTick;
     CSensor::_distance = ((diffTick*34300))/2000000;
	//std::cout << "diffTick: " << diffTick << " | Distance: " << dist << "\n";
      //printf("%u %u\n", tick-firstTick, diffTick);
   }
}

/*
void CSensor::getDistance()
{
	double diffTick;
	uint32_t startTick, endTick, now, maxTime = 3000;
	
	//send a pulse and get the distance
	gpioWrite(TRIGGER, HIGH);
	gpioSleep(PI_TIME_RELATIVE, 0, 10);
	gpioWrite(TRIGGER, LOW);
	
	now = gpioTick();
	//std::cout << "Sending pulse\n";
	while(gpioRead(ECHO) == LOW && (gpioTick() - now) < maxTime)
	{
	gpioSleep(PI_TIME_RELATIVE, 0, 100);
	}
	
	startTick = gpioTick();
	//std::cout << "Waiting pulse\n";
	while(gpioRead(ECHO) == HIGH && (gpioTick() - startTick < maxTime))
	{
		gpioSleep(PI_TIME_RELATIVE, 0, 100);
	}
	endTick = gpioTick();
	
	//std::cout << "Start: " << startTick/1000000 << "s | End time: " << endTick/1000000 << "\n";
	diffTick = endTick - startTick;
	//std::cout << "Elapsed time: " << diffTick << " us\n";
	for(int j = 1; j < MOVING_AVE; j++)
		_distances[j] = _distances[j-1];
		
	_distances[0] = ((diffTick/1000000) * 34300)/2;
}
*/
void CSensor::enable()
{
	gpioWrite(TRIGGER, LOW);
	cv::waitKey(500);
	
	gpioSetTimerFunc(0,50, sonarTrigger);
	gpioSetAlertFunc(ECHO, sonarEcho);
	
}

void CSensor::retrieveDistance(double &dist)
{
	//double average = 0;
	
	//for(int i = 0; i < MOVING_AVE; i++)
		//average += (_distances[i]);

	//dist = average/MOVING_AVE;
	dist = CSensor::_distance;
}

CSensor::~CSensor()
{
	gpioTerminate();
}

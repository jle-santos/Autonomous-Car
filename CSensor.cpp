//#include "stdafx.h"
#include "CSensor.h"


CSensor::CSensor()
{
	open("Pi");

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
	//std::cout << "Elapsed time: " << diffTick/1000000 << " us | D: " << _distance << " cm\n";
	/*
	struct timeval start;
	struct timeval timeOut;
    struct timeval end;
    struct timeval total;
	
	double elapsedTime;
	
	gpioWrite(TRIGGER, HIGH);
	gpioSleep(PI_TIME_RELATIVE, 0, 10);
	gpioWrite(TRIGGER, LOW);
	
    gettimeofday(&start, NULL);
    gettimeofday(&timeOut, NULL);
    
	while(gpioRead(ECHO) == LOW && (timeOut.tv_usec - start.tv_usec) < 5000)
		{
		gettimeofday(&timeOut, NULL);
		//gpioSleep(PI_TIME_RELATIVE, 0, 10);
		//std::cout << "ECHO LOW: ";
		//std::cout << gpioRead(ECHO) << " | " << timeOut.tv_usec - start.tv_usec << "us timeout\n";
		}
	
	gettimeofday(&start, NULL);
	gettimeofday(&timeOut, NULL);
	while(gpioRead(ECHO) == HIGH && (timeOut.tv_usec - start.tv_usec) < 50000)
		{
		gettimeofday(&timeOut, NULL);

		}
    gettimeofday(&end, NULL);
    
    timersub(&end, &start, &total);
    
	elapsedTime = total.tv_sec + total.tv_usec/1e6;
	
	for(int j = 1; j < MOVING_AVE; j++)
		_distances[j] = _distances[j-1];
	
	_distances[0] = ((elapsedTime) * 34300)/2;
	
	//std::cout << "Distance: " << _distance << " cm\n";
	//std::cout << "Elapsed time: " << elapsedTime*1e6 << "us | Distance: " << _distance << " cm\n";
	//std::cout << "Elapsed: " << total.tv_sec << "s, " << total.tv_usec << "us \n";

	/*
	double startTick, endTick, diffTick, elapsedTime;
	
	//std::cout << "HIGH\n";
	gpioWrite(TRIGGER, HIGH);
	gpioSleep(PI_TIME_RELATIVE, 0, 10);
	gpioWrite(TRIGGER, LOW);
	//std::cout << "LOW\n";
	//gpioSleep(PI_TIME_RELATIVE, 4, 0);

	
	startTick = cv::getTickCount();
	while(gpioRead(ECHO) == LOW && (cv::getTickCount() - startTick) < 10000);
	startTick = cv::getTickCount();
	
	while(gpioRead(ECHO) == HIGH && (cv::getTickCount() - startTick) < 10000);
	endTick = cv::getTickCount();
	
	diffTick = endTick - startTick;
	elapsedTime = diffTick*(1/cv::getTickFrequency());
	_distance = ((elapsedTime) * 34300)*100/2;
	std::cout << "Elapsed time: " << diffTick << "us | Distance: " << _distance << " cm\n";
	*/
}

void CSensor::enable()
{
	gpioWrite(TRIGGER, LOW);
	cv::waitKey(500);
}

void CSensor::retrieveDistance(double &dist)
{
	double average = 0;
	
	for(int i = 0; i < MOVING_AVE; i++)
		average += (_distances[i]);

	dist = average/MOVING_AVE;
	//dist = _distances[0];
}

CSensor::~CSensor()
{
	gpioTerminate();
}

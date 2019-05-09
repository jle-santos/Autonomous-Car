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
	struct timeval start;
    struct timeval end;
    struct timeval total;
	
	
    gettimeofday(&start, NULL);
    gpioWrite(TRIGGER, HIGH);
	gpioSleep(PI_TIME_RELATIVE, 0, 10);
	gpioWrite(TRIGGER, LOW);
	
    gettimeofday(&end, NULL);
    timersub(&end, &start, &total);

	std::cout << "Elapsed: " << total.tv_sec << "s, " << total.tv_usec << "us \n";

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

}

CSensor::~CSensor()
{
	gpioTerminate();
}

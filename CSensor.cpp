//#include "stdafx.h"
#include "CSensor.h"


CSensor::CSensor()
{
	open("Pi");

	//Initiate the pins
	gpioSetMode(TRIGGER, PI_OUTPUT);
	gpioSetMode(ECHO, PI_OUTPUT);
	
	gpioWrite(TRIGGER, LOW);
	cv::waitKey(500);
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
	double startTick, endTick, diffTick, elapsedTime;
	
	gpioWrite(TRIGGER, HIGH);
	gpioSleep(PI_TIME_RELATIVE, 0, 10);
	gpioWrite(TRIGGER, LOW);
	
	startTick = cv::getTickCount();
	while(gpioRead(ECHO) == LOW && (cv::getTickCount() - startTick) < 10000);
	startTick = cv::getTickCount();
	
	while(gpioRead(ECHO) == HIGH && (cv::getTickCount() - startTick) < 10000);
	endTick = cv::getTickCount();
	
	diffTick = endTick - startTick;
	elapsedTime = diffTick*(1/cv::getTickFrequency());
	std::cout << "Elapsed time: " << elapsedTime << "\n";
	
}

void CSensor::retrieveDistance(double &dist)
{

}

CSensor::~CSensor()
{
	gpioTerminate();
}

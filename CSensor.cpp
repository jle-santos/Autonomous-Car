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
	struct timeval timeOut;
    struct timeval end;
    struct timeval total;
	
	double elapsedTime;
	
	gpioWrite(TRIGGER, HIGH);
	gpioSleep(PI_TIME_RELATIVE, 0, 10);
	gpioWrite(TRIGGER, LOW);
	
    gettimeofday(&start, NULL);
    gettimeofday(&timeOut, NULL);
    
	while(gpioRead(ECHO) == LOW && (timeOut.tv_usec - start.tv_usec) < 500000)
		{
		gettimeofday(&timeOut, NULL);
		//gpioSleep(PI_TIME_RELATIVE, 0, 10);
		std::cout << "ECHO LOW: ";
		std::cout << gpioRead(ECHO) << " | " << timeOut.tv_usec - start.tv_usec << "us timeout\n";
		}
	
	gettimeofday(&start, NULL);
	gettimeofday(&timeOut, NULL);
	while(gpioRead(ECHO) == HIGH && (timeOut.tv_usec - start.tv_usec) < 500000)
		{
		gettimeofday(&timeOut, NULL);
		std::cout << "ECHO HIGH\n";
		}
    gettimeofday(&end, NULL);
    
    timersub(&end, &start, &total);
    
	elapsedTime = total.tv_sec + total.tv_usec/1e6;
	_distance = ((elapsedTime) * 34300)/2;
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

}

CSensor::~CSensor()
{
	gpioTerminate();
}

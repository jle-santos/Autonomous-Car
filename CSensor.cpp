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

CSensor::~CSensor()
{
	gpioTerminate();
}

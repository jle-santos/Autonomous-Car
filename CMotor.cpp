//#include "stdafx.h"
#include "CMotor.h"


CMotor::CMotor()
{
	open("Pi");

	//Initiate the pins
	gpioSetMode(AIN1, PI_OUTPUT);
	gpioSetMode(AIN2, PI_OUTPUT);
	gpioSetMode(PWMA, PI_OUTPUT);
	gpioSetMode(BIN1, PI_OUTPUT);
	gpioSetMode(BIN2, PI_OUTPUT);
	gpioSetMode(PWMB, PI_OUTPUT);
	gpioSetMode(STBY, PI_OUTPUT);
}

int CMotor::open(std::string comm)
{
	if (gpioInitialise() < 0)
		return 1;
	else
		return 2;
}

void CMotor::enable()
{
	
	gpioWrite(STBY, ON);
	std::cout << "Initiating H-Bridge: \nWritten: " << gpioRead(STBY) << " to GPIO: " << STBY << "\n";
}

void CMotor::disable()
{
	gpioWrite(STBY, OFF);
}

void CMotor::set_pwm_left(int val)
{
	gpioPWM(PWMA, val);
}

void CMotor::set_pwm_right(int val)
{
	gpioPWM(PWMB, val);
}

int CMotor::get_pwm_left()
{
	return gpioGetPWMdutycycle(PWMA);
}

int CMotor::get_pwm_right()
{
	return gpioGetPWMdutycycle(PWMB);
}

void CMotor::pedestrian()
{
	//gpioWrite(BIN1, ON);
	//gpioWrite(BIN2, OFF);	
	forward(2);
	std::cout << "Written: " << gpioRead(BIN1) << " to GPIO: " << BIN1 << "\n";
	std::cout << "Written: " << gpioRead(BIN2) << " to GPIO: " << BIN2 << "\n";
	
	gpioSleep(PI_TIME_RELATIVE, 2, 0);
	
	stop();
	
	std::cout << "\n Switching Directions.\n";
	backward(2);
	
	std::cout << "Written: " << gpioRead(BIN1) << " to GPIO: " << BIN1 << "\n";
	std::cout << "Written: " << gpioRead(BIN2) << " to GPIO: " << BIN2 << "\n";
	
}

void CMotor::autoRun()
{
	//Make Motor A CW
	gpioWrite(AIN1, ON);
	gpioWrite(AIN2, OFF);

	//Make Motor B CW
	gpioWrite(BIN1, ON);
	gpioWrite(BIN2, OFF);
}


void CMotor::stop()
{
	//Make Motor A low
	gpioWrite(AIN1, OFF);
	gpioWrite(AIN2, OFF);
	
	//Make Motor B low
	gpioWrite(BIN1, OFF);
	gpioWrite(BIN2, OFF);
}

void CMotor::forward(float time)
{
	//Make Motor A CW
	gpioWrite(AIN1, ON);
	gpioWrite(AIN2, OFF);

	//Make Motor B CW
	gpioWrite(BIN1, ON);
	gpioWrite(BIN2, OFF);
	
	//std::cout << "Written: " << gpioRead(AIN1) << " to GPIO: " << AIN1 << "\n";
	//std::cout << "Written: " << gpioRead(AIN2) << " to GPIO: " << AIN2 << "\n";
	//std::cout << "Written: " << gpioRead(BIN1) << " to GPIO: " << BIN1 << "\n";
	//std::cout << "Written: " << gpioRead(BIN2) << " to GPIO: " << BIN2 << "\n";
	
	gpioSleep(PI_TIME_RELATIVE, 0, time*1000000);
	//stop();
}

void CMotor::backward(float time)
{
	//Make Motor A CCW
	gpioWrite(AIN1, OFF);
	gpioWrite(AIN2, ON);

	//Make Motor B CCW
	gpioWrite(BIN1, OFF);
	gpioWrite(BIN2, ON);

	gpioSleep(PI_TIME_RELATIVE, 0, time*1000000);
	//stop();
}

void CMotor::left(float time, float usec)
{
	//Make Motor A CW
	gpioWrite(AIN1, OFF);
	gpioWrite(AIN2, OFF);

	//Make Motor B CW
	gpioWrite(BIN1, ON);
	gpioWrite(BIN2, OFF);

	gpioSleep(PI_TIME_RELATIVE, time, usec);
	//stop();

}
void CMotor::right(float time, float usec)
{
	//Make Motor A CW
	gpioWrite(AIN1, ON);
	gpioWrite(AIN2, OFF);

	//Make Motor B CW
	gpioWrite(BIN1, OFF);
	gpioWrite(BIN2, OFF);

	gpioSleep(PI_TIME_RELATIVE, time, usec);
	//stop();
}

CMotor::~CMotor()
{
	gpioTerminate();
}

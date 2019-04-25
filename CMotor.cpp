#include "stdafx.h"
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
}

void CMotor::disable()
{
	gpioWrite(STBY, OFF);
}

void CMotor::set_pwm_left(int val)
{
	gpioPWM(AIN1, val);
}

void CMotor::set_pwm_right(int val)
{
	gpioPWM(BIN1, val);
}

int CMotor::get_pwm_left()
{
	return gpioGetPWMdutycycle(AIN1);
}

int CMotor::get_pwm_right()
{
	return gpioGetPWMdutycycle(BIN1);
}

void CMotor::pedestrian()
{

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

	gpioSleep(PI_TIME_RELATIVE, time, 0);
	stop();
}

void CMotor::backward(float time)
{
	//Make Motor A CCW
	gpioWrite(AIN1, OFF);
	gpioWrite(AIN2, ON);

	//Make Motor B CCW
	gpioWrite(BIN1, OFF);
	gpioWrite(BIN2, ON);

	gpioSleep(PI_TIME_RELATIVE, time, 0);
	stop();
}

void CMotor::left(float time)
{
	//Make Motor A CW
	gpioWrite(AIN1, OFF);
	gpioWrite(AIN2, ON);

	//Make Motor B CW
	gpioWrite(BIN1, ON);
	gpioWrite(BIN2, OFF);

	gpioSleep(PI_TIME_RELATIVE, time, 0);
	stop();

}
void CMotor::right(float time)
{
	//Make Motor A CW
	gpioWrite(AIN1, ON);
	gpioWrite(AIN2, OFF);

	//Make Motor B CW
	gpioWrite(BIN1, OFF);
	gpioWrite(BIN2, ON);

	gpioSleep(PI_TIME_RELATIVE, time, 0);
	stop();
}

CMotor::~CMotor()
{
	gpioTerminate();
}

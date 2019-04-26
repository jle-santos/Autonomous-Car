//#include "stdafx.h"
#include "CCar.h"


CCar::CCar()
{
}

void CCar::drive()
{
	//_motors.set_pwm_right(255);
	//_motors.forward(2);
	_motors.enable();	
	_motors.set_pwm_right(255);
	_motors.set_pwm_left(255);
	std::cout << "\nPWM Set to: " << _motors.get_pwm_right() << "\n";
	std::cout << "\nPWM Set to: " << _motors.get_pwm_left() << "\n";
	_motors.pedestrian();
	
}


CCar::~CCar()
{
}

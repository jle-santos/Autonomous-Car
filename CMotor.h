#pragma once

//Import PiGPIO library
#include "pigpio.h"

//Misc Libraries
#include <string>
#include <iostream>

//Set input/output pins

//GPIO Pins for the H-Bridge

//Motor A (left)
#define AIN1 17
#define AIN2 27
#define PWMA 22

//Motor B (right)
#define BIN1 5
#define BIN2 6
#define PWMB 13

//H-Bridge Enable (keep high)
#define STBY 18

//Constants
enum {OFF, ON};

class CMotor
{
private:
	int _speed_left;
	int _speed_right;
	
public:
	CMotor();
	~CMotor();

	int open(std::string comm);

	void enable();
	void disable();

	void set_pwm_left(int val);
	void set_pwm_right(int val);
	int get_pwm_left();
	int get_pwm_right();

	void auto_run();

	void pedestrian();
	void stop();
	void forward(float time);
	void backward(float time);
	void left(float time);
	void right(float time);
};

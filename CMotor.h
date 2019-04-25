#pragma once

//Import PiGPIO library
#include "pigpio.h"

//Misc Libraries
#include <string>

//Set input/output pins

//GPIO Pins for the H-Bridge

//Motor A (left)
#define AIN1 17
#define AIN2 27
#define PWMA 22

//Motor B (right)
#define BIN1 2
#define BIN2 3
#define PWMB 4

//H-Bridge Enable (keep high)
#define STBY 18

//Constants
enum {OFF, ON};

class CMotor
{
private:

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

	void pedestrian();
	void stop();
	void forward(float time);
	void backward(float time);
	void left(float time);
	void right(float time);
};
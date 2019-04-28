#pragma once

//#include "Server.h"
#include "CMotor.h"
#include "CGuidance.h"
#include "CCommunication.h"

#include <iostream>
#include <thread>

#include <opencv2/opencv.hpp>


class CCar
{
private:
	CMotor _motors;
	CGuidance _guidance;
	CCommunication _comm;
	
	bool _thread_exit;
	
	static void serverthrd(CCar *ptr);
	static void imagethrd(CCar *ptr);

public:
	CCar();
	~CCar();

	cv::Mat _car_vision;

	void transmit();
	void autonomous();
	void drive();
	void test();
};


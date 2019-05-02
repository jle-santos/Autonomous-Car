#pragma once

//#include "Server.h"
#include "CMotor.h"
#include "CGuidance.h"
//#include "CCommunication.h"
#include "server.h"

#include <iostream>
#include <thread>
#include <mutex> 

#include <opencv2/opencv.hpp>


class CCar
{
private:
	CMotor _motors;
	CGuidance _guidance;
	Server _serv;
	//CCommunication _comm;
	
	cv::Mat _car_vision;
	
	std::mutex _carX;
	
	bool _thread_exit;
	
	static void serverthrd(CCar *ptr);
	static void imagethrd(CCar *ptr);
	
	void serverfunc();
	void serverimgfunc();
	


public:
	CCar();
	~CCar();



	//void transmit();
	void autonomous();
	void drive();
	void test();
};


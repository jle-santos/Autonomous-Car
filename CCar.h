#pragma once

#include "CMotor.h"
#include "CGuidance.h"
#include "CCommunication.h"
#include "CSensor.h"

#include <iostream>
#include <thread>
#include <mutex> 

#include <opencv2/opencv.hpp>

const std::string W_KEY = "119";
const std::string A_KEY = "97";
const std::string S_KEY = "115";
const std::string D_KEY = "100";
const std::string E_KEY = "101";
const std::string Q_KEY = "113";



class CCar
{
private:
	CMotor _motors;
	CGuidance _guidance;
	CSensor _sensor;
	//Server _serv;
	CCommunication _comm;
	
	std::vector<std::string> _commands;
	
	std::string _direction;
	
	int _speed;
	int _left;
	int _right;
	//double _distance;
	
	cv::Mat _car_vision;
	
	std::mutex _carX;
	
	bool _thread_exit;
	
	static void serverthrd(CCar *ptr);
	static void imagethrd(CCar *ptr);
	static void sendthrd(CCar *ptr);
	static void distthrd(CCar *ptr);
	//static void camthrd(CCar *ptr);
	//void serverfunc();
	//void serverimgfunc();
	


public:
	CCar();
	~CCar();


	
	void transmit();
	void autonomous();
	void drive();
	void test();
	void stop();
	void parse_cmd(std::string cmd);
};


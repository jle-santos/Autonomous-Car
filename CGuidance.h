#pragma once

#include <opencv2/opencv.hpp>
#include "raspicam_cv.h"

#define SIZE 480

class CGuidance
{
private:
	cv::Mat _display_im;
	//cv::Mat _raw, _binary, _hsv;
	int _dY;
	
	raspicam::RaspiCam_Cv _cap;
	
	int _speed;
	
public:
	CGuidance();
	~CGuidance();

	void update();
	void get_im(cv::Mat &im);
	
	void get_speed(int motor_speed); 
	
	
};


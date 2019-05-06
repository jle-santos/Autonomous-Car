#pragma once

#include <opencv2/opencv.hpp>
#include "raspicam_cv.h"

#define SIZE_X 480
#define SIZE_Y 360
#define CENTER_RAD 30
class CGuidance
{
private:
	cv::Mat _display_im;
	//cv::Mat _raw, _binary, _hsv;
	int _dY;
	
	cv::Point _centerScreen;
	int _speed_left;
	int _speed_right;
	
	
	raspicam::RaspiCam_Cv _cap;
	
	int _speed;
	
public:
	CGuidance();
	~CGuidance();

	void update();
	void get_im(cv::Mat &im);
	
	void set_motor_speed(int &left, int &right);
	
	void get_speed(int motor_speed); 
	
	
};


#pragma once

#include <opencv2/opencv.hpp>
#include "raspicam_cv.h"

#define SIZE_X 480
#define SIZE_Y 360
#define CENTER_RAD 30

#define STRAIGHT 70
#define TURN 100

#define STOP_DIST 10

class CGuidance
{
private:
	cv::Mat _display_im;
	//cv::Mat _raw, _binary, _hsv;
	
	raspicam::RaspiCam_Cv _cap;
	
	int _speed_left;
	int _speed_right;
	std::string _direction;
	
	double _distance;
	int _speed;
	
public:
	CGuidance();
	~CGuidance();

	int checkColour;
	
	void update();
	void get_im(cv::Mat &im);
	
	void set_motor_speed(int &left,int &right);
	void getDistance(double dist); 
	
	void getDirection(std::string &dir);
	
};


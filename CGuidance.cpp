//#include "stdafx.h"
#include "CGuidance.h"


CGuidance::CGuidance()
{
}

void CGuidance::update()
{
	cv::Mat _raw;
    _cap.open();
	
    if(_cap.isOpened())
    {
		//std::cout << "\nRetrieving image...\n";
        _cap.grab();
        _cap.retrieve(_raw);
        cv::resize(_raw, _raw, cv::Size(640,480));
        cv::putText(_raw, "MOTOR SPEED: " + std::to_string(_speed), cv::Point(50,100), CV_FONT_HERSHEY_PLAIN, 2, cv::Scalar(255,255,255), 2, CV_AA);
  
		
		cv::cvtColor(_raw, _display_im, CV_BGR2GRAY);
		//cv::cvtColor(_display_im, _hsv, CV_BGR2HSV);
		
		// = _binary;
		//cv::resize(_display_im, _display_im, cv::Size(640, 480));
    }
}

/*
void CGuidance::update()
{
	_cap.open();
	
	if(_cap.isOpened())
	{
		_cap.grab();
		_cap.retrieve(_display_im);
		cv::resize(_display_im, _display_im, cv::Size(640,480));
	}
}
*/
void CGuidance::get_speed(int motor_speed)
{
	_speed = motor_speed;
}

void CGuidance::get_im(cv::Mat &im)
{
	_display_im.copyTo(im);
}

CGuidance::~CGuidance()
{
}

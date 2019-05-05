//#include "stdafx.h"
#include "CGuidance.h"


CGuidance::CGuidance()
{
}

void CGuidance::update()
{
	cv::Mat _raw, _hsv, _greenThresh;
    std::vector<cv::Vec3f> circles;
    
    _cap.open();
	
    if(_cap.isOpened())
    {
		//std::cout << "\nRetrieving image...\n";
        _cap.grab();
        _cap.retrieve(_raw);
        cv::resize(_raw, _raw, cv::Size(SIZE, SIZE/1.33));
        //cv::cvtColor(_raw, _display_im, cv::COLOR_BGR2GRAY);
        //cv::resize(_display_im, _display_im, cv::Size(240,240));
        _raw.copyTo(_display_im);
        
		//Convert to HSV
        cv::cvtColor(_raw, _hsv, cv::COLOR_BGR2HSV);
        //cv::putText(_raw, "MOTOR SPEED: " + std::to_string(_speed), cv::Point(50,100), CV_FONT_HERSHEY_PLAIN, 2, cv::Scalar(255,255,255), 2, CV_AA);
		cv::inRange(_hsv, cv::Scalar(50, 100, 100), cv::Scalar(80, 255, 255), _greenThresh);
		//_raw.copyTo(_display_im);
		cv::GaussianBlur(_greenThresh, _greenThresh, cv::Size(9,9), 2, 2);
		cv::HoughCircles(_greenThresh, circles, CV_HOUGH_GRADIENT, 1, _greenThresh.rows/8, 100, 20, 0, 0);
		
		for(size_t circle = 0; circle < circles.size(); circle++)
		{
			cv::Point center(std::round(circles[circle][0]), std::round(circles[circle][1]));
			int radius = std::round(circles[circle][2]);
			cv::circle(_raw, center, radius, cv::Scalar(255, 0, 0), 5);
			cv::line(_raw, center, cv::Point(SIZE/2, SIZE/2), cv::Scalar(255,0,255), 3);
			int _dX = circles[circle][0] - SIZE/2;
			cv::line(_raw, cv::Point(SIZE/2, SIZE/2), cv::Point(circles[circle][0], SIZE/2), cv::Scalar(255,0,255), 3);
		}
		
		
		
		//_greenThresh.copyTo(_display_im);
		//cv::circle(_display_im, cv::Point(SIZE/2, SIZE/2), 60, cv::Scalar(0,0,255), 2, 4);
    }
}

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

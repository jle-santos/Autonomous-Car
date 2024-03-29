//#include "stdafx.h"
#include "CGuidance.h"


CGuidance::CGuidance()
{
	checkColour = 0;
}
/*
void CGuidance::update()
{
	cv::Mat _raw, _hsv, _crop,  _greenThresh, _redThresh_A, _redThresh_B;
    std::vector<cv::Vec3f> circles;
    std::string dir, colour = "NO";
    int largest_circle = 0, largest_circle_rad = 1, xPoint = 0;
    
    //Vectors
    std::vector<std::string> colourSort = {"GRN", "RED"};
    
    //Green Range
    cv::Scalar greenMin = cv::Scalar(50,50,50);
    cv::Scalar greenMax = cv::Scalar(80,255,255);
    
    //Red Range
    cv::Scalar redMin_A = cv::Scalar(0,50,50);
    cv::Scalar redMax_A = cv::Scalar(10,255,255);
    cv::Scalar redMin_B = cv::Scalar(160,50,50);
    cv::Scalar redMax_B = cv::Scalar(179,255,255);
    
    _cap.open();
	
    if(_cap.isOpened())
    {
		//Grab new image
        _cap.grab();
        _cap.retrieve(_raw);
        cv::resize(_raw, _raw, cv::Size(SIZE_X, SIZE_Y));
        
        //_crop = _raw(cv::Rect(10, 100, 600, 100));
        if(checkColour)
        {
        for(int i = 0; i < 2; i++)
        {
			//Convert to HSV
			cv::cvtColor(_raw, _hsv, cv::COLOR_BGR2HSV);
			
			if(i == 0)
				cv::inRange(_hsv, greenMin, greenMax,_greenThresh);
			else
			{
			cv::inRange(_hsv, redMin_A, redMax_A, _redThresh_A);
			cv::inRange(_hsv, redMin_B, redMax_B, _redThresh_B);
			cv::addWeighted(_redThresh_A, 1.0, _redThresh_B, 1.0, 0, _greenThresh);
			}
			
			//Clean up the image
			cv::GaussianBlur(_greenThresh, _greenThresh, cv::Size(9,9), 2, 2);
			
			
			//Find the circles
			cv::HoughCircles(_greenThresh, circles, CV_HOUGH_GRADIENT, 1, _greenThresh.rows/8, 100, 20, 0, 0);
			
			//Iterate through all the circles
			for(size_t circle = 0; circle < circles.size(); circle++)
			{
				cv::Point center(std::round(circles[circle][0]), std::round(circles[circle][1]));
				//int radius = std::round(circles[circle][2]);
				//cv::circle(_raw, center, radius, cv::Scalar(255, 0, 0), 5);
				//cv::line(_raw, center, _centerScreen, cv::Scalar(255,0,255), 3);
				//int _dX = circles[circle][0] - SIZE_X/2;
				//cv::line(_raw, _centerScreen, cv::Point(circles[circle][0], SIZE_Y/2), cv::Scalar(255,0,255), 3);
				
				//find largest circle
				if(circles[circle][2] > largest_circle_rad)
				{
					colour = colourSort[i];
					largest_circle = circle;
					largest_circle_rad = circles[circle][2];
					xPoint = circles[largest_circle][0];
				}
				else
					colour = "STR";
			}
		}
		/*if(largest_circle_rad < 50 && largest_circle_rad > 5)
			{
				if(xPoint < SIZE_X/2 - CENTER_RAD)
				{
					dir = "L";
					_speed_left = STRAIGHT;
					_speed_right = TURN;
				}
				else if(xPoint > SIZE_X/2 + CENTER_RAD)
				{
					dir = "R";
					_speed_left = TURN;
					_speed_right = STRAIGHT;
				}
				else
				{
					dir = "S";
					_speed_left = STRAIGHT;
					_speed_right = STRAIGHT;
				}
			}
		//else
		//{
			if(colour == "GRN")
			{
			_direction = "RIGHT";
			_speed_left = 200;
			_speed_right = 0;
			}
			else if (colour == "RED")
			{
			_direction = "LEFT";
			_speed_left = 0;
			_speed_right = 200;
			}
			else
			{
				_direction = "STOP";
				_speed_left = 0;
				_speed_right = 0;;
			}
		//}
		
		}
		else
			{
				_direction = "STRAIGHT";
				//_speed_left = STRAIGHT;
				//_speed_right = STRAIGHT;
			}
		//std::cout << "Largest circle found: " << largest_circle << " | Radius: " << largest_circle_rad << "\n";
		//cv::circle(_display_im, cv::Point(SIZE_X/2, SIZE_Y/2), CENTER_RAD, cv::Scalar(0,0,255), 2, 4);
		 //cv::putText(_raw, "DIR: " + _direction + " | L: " + std::to_string(_speed_left) + " | R" + std::to_string(_speed_right), cv::Point(10,100), CV_FONT_HERSHEY_PLAIN, 2, cv::Scalar(255,255,255), 2, CV_AA);
		 
		 cv::putText(_raw, "Wall in: " + std::to_string(_distance), cv::Point(10,30), CV_FONT_HERSHEY_PLAIN, 2, cv::Scalar(255,255,255), 2, CV_AA);
		 _raw.copyTo(_display_im);
		 //.copyTo(_display_im);
		//_greenThresh.copyTo(_display_im);
		
    }
}
*/

void CGuidance::update()
{
	cv::Rect green;
	cv::Rect orange;
	
	cv::Mat dilation;
	
	std::vector<cv::Vec4i> hierarchy;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Point> contour;
	
	_cap.open();
	
	if(_cap.isOpened())
    {
		//Grab new image
        _cap.grab();
        _cap.retrieve(_raw);
        cv::resize(_raw, _raw, cv::Size(SIZE_X, SIZE_Y));
		
		cv::cvtColor(_raw, _hsv, CV_RGB2HSV);

		//Find Green
		cv::inRange(_hsv, greenMin, greenMax, _greenThresh);
		cv::erode(_greenThresh, dilation, cv::Mat(), cv::Point(-1,-1), 1);
		cv::dilate(dilation, dilation, cv::Mat(), cv::Point(-1,-1), 1);
		
		cv::findContours(dilation, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		for (unsigned int i = 0; i < contours.size(); i++)
		 {
			green = boundingRect(contours.at(i));
			
		 }
		 
		 cv::rectangle(_raw, green, cv::Scalar(0, 255, 0), 2);
		
	
		//Find Orange
		cv::inRange(_hsv, cv::Scalar(111, 117, 119), cv::Scalar(127,255,255), _redThresh_A);
		cv::erode(_redThresh_A, dilation, cv::Mat(), cvPoint(-1,-1),2);
		cv::dilate(dilation, dilation, cv::Mat(), cv::Point(-1,-1), 1);
	    cv::findContours(dilation, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		
		for (unsigned int i = 0; i < contours.size(); i++)
		 {
			orange = cv::boundingRect(contours.at(i));
			
		 }
		 rectangle(_raw, orange, cv::Scalar(0, 80, 255), 2);
		 
		//Tracking - track until size is X
		//Get coordinates of box
		cv::Point orange_center = cv::Point(orange.x + orange.width/2, orange.y + orange.height/2);
		cv::Point green_center = cv::Point(green.x + green.width/2, green.y + green.height/2);
		
		if(orange_center.x || green_center.x >= SIZE_X/2)
		{
			_speed_left = 70;
			_speed_right = 100;
			std::cout << "TWEAK LEFT";
		}
		else if(orange_center.x || green_center.x < SIZE_X/2)
		{
			_speed_left = 100;
			_speed_right = 70;
			std::cout << "TWEAK RIGHT";
		}
		else
		{
			_speed_left = 100;
			_speed_right = 90;
		}
		
		//Check which colour
		if((green.area() > 150) && (orange.area() > 150))	
			_direction = "END";
		else if(green.area() > 150)
		{
			cv::line(_raw, green_center, _centerScreen,  cv::Scalar(0, 255, 0), 3);
			_direction = "GREEN";
		}
		else if(orange.area() > 150)
		{
			cv::line(_raw, orange_center, _centerScreen,  cv::Scalar(0, 80, 255), 3);
			_direction = "ORANGE";
		}
		else
			_direction = "STRAIGHT";

		
		//cv::putText(_raw, "ORANGE: " + std::to_string(orange.area()) + " | GREEN: " + std::to_string(green.area()) , cv::Point(10,100), CV_FONT_HERSHEY_PLAIN, 2, cv::Scalar(255,255,255), 2, CV_AA);
		cv::putText(_raw, "DIR: " + _direction , cv::Point(10,100), CV_FONT_HERSHEY_PLAIN, 2, cv::Scalar(255,255,255), 2, CV_AA);
		//cv::imshow("Raw,", _raw);
		_raw.copyTo(_display_im);
	
	}
	
}

void CGuidance::getDirection(std::string &dir)
{
	dir = _direction;
}

void CGuidance::set_motor_speed(int &left, int &right)
{
	left = _speed_left;
	right = _speed_right;
}
void CGuidance::getDistance(double distance)
{
	_distance = distance;
}

void CGuidance::get_im(cv::Mat &im)
{
	_display_im.copyTo(im);
}

CGuidance::~CGuidance()
{
}

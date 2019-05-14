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
	cv::Mat _raw, _hsv, _crop,  _greenThresh, _redThresh_A, _redThresh_B;
    std::vector<cv::Vec3f> circles;
    std::string dir, colour = "NO";
    int largest_circle = 0, largest_circle_rad = 1, xPoint;
    cv::Point _centerScreen = cv::Point(SIZE_X/2, SIZE_Y/2);
    //Vectors
    std::vector<std::string> colourSort = {"GRN", "RED"};
    
    int orange_radius;
    int green_radius;
    
    //Green Range
    cv::Scalar greenMin = cv::Scalar(50,50,50);
    cv::Scalar greenMax = cv::Scalar(80,255,255);
    
    //Red Range
    cv::Scalar redMin_A = cv::Scalar(0,50,50);
    cv::Scalar redMax_A = cv::Scalar(10,255,255);
    cv::Scalar redMin_B = cv::Scalar(160,50,50);
    cv::Scalar redMax_B = cv::Scalar(179,255,255);
	
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


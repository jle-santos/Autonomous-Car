#pragma once

#include <opencv2/opencv.hpp>
#include "raspicam_cv.h"

class CGuidance
{
private:
	cv::Mat _display_im;
	raspicam::RaspiCam_Cv _cap;
	
public:
	CGuidance();
	~CGuidance();

	void update();
	cv::Mat get_im();
};


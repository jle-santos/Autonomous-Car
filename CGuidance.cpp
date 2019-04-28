//#include "stdafx.h"
#include "CGuidance.h"


CGuidance::CGuidance()
{
}

void CGuidance::update()
{
    _cap.open();
	
    if(_cap.isOpened())
    {
		std::cout << "\nRetrieving image...\n";
        _cap.grab();
        _cap.retrieve(_display_im);
        //cv::imshow("Car", _display_im);
       //hile (cv::waitKey(5) != ' ');
    }
  
}

void CGuidance::get_im(cv::Mat &im)
{
    im = _display_im;
}

CGuidance::~CGuidance()
{
}

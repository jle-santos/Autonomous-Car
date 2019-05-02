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
		//std::cout << "\nRetrieving image...\n";
        _cap.grab();
        _cap.retrieve(_display_im);
        cv::resize(_display_im, _display_im, cv::Size(640, 480));
    }
  
}

/*void CGuidance::get_im(cv::Mat &im)
{
    im = _display_im;
}*/

void CGuidance::get_im(cv::Mat &im)
{
	_display_im.copyTo(im);
}

CGuidance::~CGuidance()
{
}

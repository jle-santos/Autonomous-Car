#include "CCommunication.h"


CCommunication::CCommunication()
{
	
}

void CCommunication::set_port(int port_name)
{
	_port = port_name;
}

void CCommunication::start_server()
{
	_serv.start(_port);
}

void CCommunication::transmit_images()
{
  
  
  if(!_car_im.empty())
  {
  cv::resize(_car_im, _car_im, cv::Size(640, 480));
  //cv::imshow("Car Image", _car_im);
  _serv.set_txim(_car_im);
  while (cv::waitKey(20) != ' ');
  }
  /*
  if (vid.isOpened() == TRUE)
  {
    do
    {
      cv::Mat frame;
      
      vid.grab();
      vid.retrieve(frame);
	  
	  cv::resize(frame, frame, cv::Size(640, 480));
      serv.set_txim(frame);
    }
    while (cv::waitKey(5) != ' ');
  }*/
}

void CCommunication::get_image(cv::Mat car_image)
{
    _car_im = car_image;
}

CCommunication::~CCommunication()
{
}

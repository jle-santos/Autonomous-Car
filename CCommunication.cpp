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
	//std::cout << "Server Thread\n";
	_serv.start(4618);
}

void CCommunication::transmit_images()
{
 
 //do
 //{  
	std::cout << "Sending image: _car_im\n";
	cv::resize(_car_im, _car_im, cv::Size(640,480));
  _serv.set_txim(_car_im);
 //}
 //while (cv::waitKey(30) != ' ');
 
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

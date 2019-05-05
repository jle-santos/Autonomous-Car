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
 
 do
 {  
	//std::cout << "Sending image: _car_im\n";
    _serv.set_txim(_car_im);
 }
 while (cv::waitKey(5) != ' ');
}

void CCommunication::get_image(cv::Mat &car_image)
{
    car_image.copyTo(_car_im);
}

void CCommunication::get_commands(std::vector<std::string> &commands)
{
	_serv.get_cmd(commands);
}

CCommunication::~CCommunication()
{
}

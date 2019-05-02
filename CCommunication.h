#pragma once

#include "server.h"

#include <iostream>
#include <opencv2/opencv.hpp>

class CCommunication
{
private:
    Server _serv;

    cv::Mat _car_im;
    int _port;

	
public:
	CCommunication();
	~CCommunication();

    void set_port(int port_name);

    void start_server();
	void transmit_images();

    void get_image(cv::Mat &car_image);
};


//#include "stdafx.h"
#include "CCar.h"


CCar::CCar()
{
}

void CCar::transmit()
{
	std::thread t1 (&CCar::serverthrd, this);
	t1.detach();
	
	std::thread t2 (&CCar::imagethrd, this);
	t2.detach();
	
}

void CCar::serverthrd(CCar * ptr)
{
  	while(ptr->_thread_exit == false)
  	{
		ptr->_comm.start_server();
	}
}

void CCar::imagethrd(CCar * ptr)
{
  	  	while(ptr->_thread_exit == false)
  	{
		ptr->_comm.transmit_images();
	}
}

void CCar::drive()
{
	_comm.set_port(4618);

	transmit();

	for(int i = 1000; i <= 1000; i++)
	{
		std::cout << "Transmitting...\n";
		_guidance.update();
		std::cout << "Updated image...\n";
		_guidance.get_im(_car_vision);
		//cv::imshow("Car", _car_vision);
		//cv::waitKey(10);
		std::cout << "Sending image...\n";
		_comm.get_image(_car_vision);
	}
}

void CCar::autonomous()
{

}

void CCar::test()
{
	//_motors.set_pwm_right(255);
	//_motors.forward(2);
	/*_motors.enable();	
	_motors.set_pwm_right(255);
	_motors.set_pwm_left(255);
	std::cout << "\nPWM Set to: " << _motors.get_pwm_right() << "\n";
	std::cout << "\nPWM Set to: " << _motors.get_pwm_left() << "\n";
	_motors.pedestrian();*/
	
	int cmd = 1;
	int pwm = 255;
	int time = 0;
	
	while(cmd != 6)
		{
			_motors.enable();
			std::cout << "\nMotor Drive Menu\n";
			std::cout << "(1) Set PWM of Motors.\n";
			std::cout << "(2) Drive Forward.\n";
			std::cout << "(3) Drive Reverse";
			std::cout << "(4) Turn Left.\n";
			std::cout << "(5) Turn Right.\n";
			std::cout << "(6) Quit Program\n>>";
			std::cin >> cmd;
			
			switch(cmd)
			{
				case 1 : 	std::cout << "\nEnter PWM speed (0-255): >> ";
							std::cin >> pwm;
							_motors.set_pwm_left(pwm);
							_motors.set_pwm_right(pwm);
							std::cout << "\nPWM Set to: " << _motors.get_pwm_right() << "\n";
							std::cout << "\nPWM Set to: " << _motors.get_pwm_left() << "\n";
							break;
							
				case 2 : 	std::cout << "\nF: Enter time in seconds: >> ";
							std::cin >> time;
							_motors.forward(time);
							break;
							
				case 3 : 	std::cout << "\nB: Enter time in seconds: >> ";
							std::cin >> time;
							_motors.backward(time);
							break;
							
				case 4 : 	std::cout << "\nL: Enter time in seconds: >> ";
							std::cin >> time;
							_motors.left(time);
							break;
							
				case 5 : 	std::cout << "\nR: Enter time in seconds: >> ";
							std::cin >> time;
							_motors.right(time);
							break;
			
		}
		
	
	}
}


CCar::~CCar()
{
}

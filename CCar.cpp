//#include "stdafx.h"
#include "CCar.h"


CCar::CCar()
{
	//_thread_exit = false;
}

void CCar::transmit()
{
	std::thread t1 (&CCar::serverthrd, this);
	t1.detach();
	
	std::thread t2 (&CCar::imagethrd, this);
	t2.detach();
	
	std::thread t3 (&CCar::sendthrd, this);
	t3.detach();
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

void CCar::sendthrd(CCar * ptr)
{
	  	  	while(ptr->_thread_exit == false)
  	{
		ptr->_guidance.update();
	}
}

void CCar::drive()
{
	transmit();
	_motors.enable();
	_sensor.enable();
	//_speed = 255;
	
	//_motors.set_pwm_left(_speed);
	//_motors.set_pwm_right(_speed);
	
	while(true) 
	{
		//_guidance.update();
		_guidance.get_im(_car_vision);
		//std::cout << "Test\n";
		_sensor.getDistance();
		cv::waitKey(20);
		_comm.get_image(_car_vision);
		_comm.get_commands(_commands);
		if(!_commands.empty())
			parse_cmd(_commands[0]);
	};
}

void CCar::parse_cmd(std::string cmd)
{
	std::cout << "Commands recieved: " << cmd << "\n";
	_motors.set_pwm_left(_speed);
	_motors.set_pwm_right(_speed);
	std::cout << "Speed: " << _speed << "\n";
	if(cmd == W_KEY)
		_motors.forward(1);
	else if (cmd == S_KEY)
		_motors.backward(1);
	else if (cmd == A_KEY)
		_motors.left(0.2);
	else if (cmd == D_KEY)
		_motors.right(0.2);
	else if (cmd == E_KEY)
	{
		if(_speed < 255)
			_speed += 20;
		
		if(_speed > 255)
			_speed = 255;
	}
	else if (cmd == Q_KEY)
	{
		if(_speed > 100)
			_speed -= 20;
			
		if(_speed < 100)
			_speed = 100;
	}
	else 
		std::cout << "\nInvalid key\n";
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

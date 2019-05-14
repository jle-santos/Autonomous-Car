//#include "stdafx.h"
#include "CCar.h"


CCar::CCar()
{
	//_thread_exit = false;
	_speed = 100;
}

void CCar::transmit()
{
	std::thread t1 (&CCar::serverthrd, this);
	t1.detach();
	
	std::thread t2 (&CCar::imagethrd, this);
	t2.detach();
	
	//std::thread t3 (&CCar::sendthrd, this);
	//t3.detach();
	
	//std::thread t4(&CCar::distthrd, this);
	//t4.detach();
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
/*
void CCar::distthrd(CCar *ptr)
{
	while(ptr->_thread_exit == false)
	{
		ptr->_sensor.getDistance();
	}
}
*/
void CCar::autonomous()
{
	_sensor.enable();
	_motors.enable();
	transmit();
	
	//Autonomous mode only

	
	
	//_speed = 255;
	double _distance;
	_left = 100;
	_right = 100;
	_motors.autoRun();
	//_motors.set_pwm_left(100);
	//_motors.set_pwm_right(100);
	
	while(true) 
	{
		
		_guidance.set_motor_speed(_left, _right);
		_motors.set_pwm_left(_left);
		_motors.set_pwm_right(_right);
		//std::cout << "PWM: " << _motors.get_pwm_left() << "\n";
	    
	    _sensor.retrieveDistance(_distance);
	    std::cout << _distance << "cm \n";
	    
	    if(_distance <= 7 && _distance >= 3)
	    {
		_motors.stop();
		_guidance.update();
		_guidance.getDirection(_direction);
	    if(_direction == "GREEN")
			{
				_motors.stop();
				_motors.right(1, 50000);
				_motors.stop();
				_motors.forward(0.5);
				_direction = "STRAIGHT";
			}
		else if(_direction == "ORANGE")
		{
				_motors.stop();
				_motors.left(1, 100000);
				_motors.stop();
				_direction = "STRAIGHT";
				_motors.forward(0.5);
		}
		else
			_motors.stop();
		}
		else
			_motors.forward(0.01);
	    
		//_sensor.retrieveDistance(_distance);
		//_guidance.getDistance(_distance);
		
		
		
		/*
		if(_distance <= 10)
			{
			//_motors.stop();
			////_guidance.checkColour = 1;
			//_guidance.set_motor_speed(_left, _right);
			//_motors.set_pwm_left(_left);
			//_motors.set_pwm_right(_right);
			//_guidance.checkColour = 0;
			
			if(_right == 0 && _left == 200)
				_motors.right(0.5);
			else if(_left == 0 && _right == 200)
				_motors.left(0.45);
			else
				_motors.forward(0.01);
			
			//cv::waitKey(100);
			//_guidance.checkColour = 1;
			/*
			_guidance.getDirection(_direction);
			if(_direction == "RIGHT")
			{
				_motors.stop();
				_motors.right(0.5);
			}
			else if(_direction == "LEFT")
			{
				_motors.stop();
				_motors.right(0.5);
			}
			else if(_direction == "STOP")
				_motors.stop();
			}
		else
		{
			_guidance.checkColour = 0;
			_motors.forward(0.01);
			_motors.set_pwm_left(100);
			_motors.set_pwm_right(100);
		}

		*		
		//_guidance.getDistance(_distance);
		//std::cout << "Distance: " << _distance << "| check Colour? "<< _guidance.checkColour << " | Direction: " << _direction << "\n";
		
		*/
		
		
		//std::cout << "Test\n";
		//_sensor.getDistance();
		cv::waitKey(20);
		_guidance.get_im(_car_vision);
		_comm.get_image(_car_vision);
	};
}


/*
void CCar::autonomous()
{
	_sensor.enable();
	_motors.enable();
	transmit();
	
	
	//_speed = 255;
	double _distance;
	_motors.set_pwm_left(100);
	_motors.set_pwm_right(100);
	
	while(true) 
	{
		//_motors.autoRun();
		//_motors.set_pwm_left(_left);
		//_motors.set_pwm_right(_right);
	    //_guidance.set_motor_speed(_left, _right);
	    
	    //_sensor.getDistance();
		_sensor.retrieveDistance(_distance);
		if(_distance <= 10)
			{
			_motors.stop();
			_guidance.checkColour = 1;
			_guidance.set_motor_speed(_left, _right);
			_motors.set_pwm_left(_left);
			_motors.set_pwm_right(_right);
			//_guidance.checkColour = 0;
			
			if(_right == 0 && _left == 200)
			{
				_motors.right(0.5);
				_motors.stop();
			}
			else if(_left == 0 && _right == 200)
			{
				_motors.left(0.45);
				_motors.stop();
			}
			else
				_motors.stop();
				
			cv::waitKey(200);
			//_guidance.checkColour = 0;
			//cv::waitKey(100);
			//_guidance.checkColour = 1;
			/*
			_guidance.getDirection(_direction);
			if(_direction == "RIGHT")
			{
				_motors.stop();
				_motors.right(0.5);
			}
			else if(_direction == "LEFT")
			{
				_motors.stop();
				_motors.right(0.5);
			}
			else if(_direction == "STOP")
				_motors.stop();
			}
		else
		{
			_guidance.checkColour = 0;
			_motors.forward(0.01);
			_motors.set_pwm_left(100);
			_motors.set_pwm_right(100);
		}

		_guidance.get_im(_car_vision);
		
		//_guidance.getDistance(_distance);
		std::cout << "Distance: " << _distance << "| check Colour? "<< _guidance.checkColour << " | Direction: " << _direction << "\n";
		
		
		
		
		//std::cout << "Test\n";
		//_sensor.getDistance();
		cv::waitKey(20);
		_comm.get_image(_car_vision);
	};
}
*/
void CCar::stop()
{
	_motors.stop();
}

void CCar::parse_cmd(std::string cmd)
{
	//std::cout << "Commands recieved: " << cmd << "\n";
	_motors.set_pwm_left(_speed);
	_motors.set_pwm_right(_speed);
	//std::cout << "Speed: " << _speed << "\n";
	if(cmd == "w")
	{
		_motors.forward(0.01);
		//std::cout << "\nForward detected\n";
	}
	else if (cmd == "s")
		_motors.backward(0.01);
	else if (cmd == "a")
		_motors.left(0,1000);
	else if (cmd == "d")
		_motors.right(0,1000);
	else if (cmd == "e")
	{
		if(_speed < 255)
			_speed += 20;
		
		if(_speed > 255)
			_speed = 255;
	}
	else if (cmd == "q")
	{
		if(_speed > 100)
			_speed -= 20;
			
		if(_speed < 100)
			_speed = 100;
	}
	else 
	{
		//std::cout << "\nInvalid key\n";
		_motors.stop();
	}
}

void CCar::drive()
{
	double _distance;
	_sensor.enable();
	_motors.enable();
	transmit();
	
	
	while(true)
	{
		_sensor.retrieveDistance(_distance);
		_guidance.getDistance(_distance);
		//cv::waitKey(20);
		_guidance.get_im(_car_vision);
		_comm.get_image(_car_vision);
		
		
		_comm.get_commands(_commands);
		if(!_commands.empty())
			parse_cmd(_commands[0]);
	}
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
							_motors.left(time, 0);
							break;
							
				case 5 : 	std::cout << "\nR: Enter time in seconds: >> ";
							std::cin >> time;
							_motors.right(time, 0);
							break;
			
		}
		
	
	}
}


CCar::~CCar()
{
}

//Main 

#include "CCar.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "AutoCar V1.0\n";
	std::cout << "ELEX 4699\n";
	
	CCar car;

	//Starts the Car Server threads

	car.drive();
	//car.test();
	
	return 0;
}

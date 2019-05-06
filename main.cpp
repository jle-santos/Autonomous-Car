//Main 

#include "CCar.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "AutoCar V1.0\n";
	std::cout << "ELEX 4699\n";
	
	CCar car;
	int mode = 0;
	
	std::cout << "\nMode: \n1 - Auto\n2 - Drive, \n3 - Test>> ";
	std::cin >> mode;
	//Starts the Car Server threads
	
	if(mode  == 1)
		car.self();
	else if(mode == 2)
		car.drive();
	else if(mode == 3)
		car.stop();
	else
		car.test();
	
	return 0;
}

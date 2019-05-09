//Import PiGPIO library
#include "pigpio.h"

//Misc Libraries
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

//Set input/output pins
#define TRIGGER 23
#define ECHO 24



//Constants
enum {LOW, HIGH};

class CSensor
{
private:
	int _distance;
public:
	CSensor();
	~CSensor();

	int open(std::string comm);
	
	void getDistance();
	void retrieveDistance(double &dist);

};

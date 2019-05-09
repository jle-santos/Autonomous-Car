//Import PiGPIO library
#include "pigpio.h"

//Misc Libraries
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/time.h>

//Set input/output pins
#define TRIGGER 23
#define ECHO 24

#define MOVING_AVE 20

//Constants
enum {LOW, HIGH};

class CSensor
{
private:
	double _distances[20] = {0};
public:
	CSensor();
	~CSensor();

	int open(std::string comm);
	
	void enable();
	void getDistance();
	void retrieveDistance(double &dist);

};
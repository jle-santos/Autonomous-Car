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

#define MOVING_AVE 5

//Constants
enum {LOW, HIGH};

class CSensor
{
private:
	static double _distance;
public:
	CSensor();
	~CSensor();

	int open(std::string comm);
	
	static void sonarTrigger(void);
	static void sonarEcho(int gpio, int level, uint32_t tick);
	
	void enable();
	void getDistance();
	void retrieveDistance(double &dist);

};

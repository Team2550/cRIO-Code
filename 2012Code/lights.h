#ifndef HAVE_LIGHTS_H
#define HAVE_LIGHTS_H

#include "WPILib.h"

class Lights {
public:
	Lights();
	~Lights();
	
	void FlashLights();
private:
	Solenoid *light1;
	Solenoid *light2;
	Solenoid *light3;
	Timer *counter;
	float On;
	float Step;
	Joystick *test;
	float lightd;
	bool first;
	int intcounter;
	double lastcount;
	
};

#endif

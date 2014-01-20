#ifndef DRIVE_H
#define DRIVE_H
#include "WPILib.h"
#include "stick.h"

class Drive
{
	public:
		Drive();
		~Drive();
		void autoDrive();
		void remoteDrive();
		//left and right joysticks of xbox remote
		float LeftStickY;
		float RightStickY; 
	private:
		//left and right drive motors
		Jaguar* Left1;
		Jaguar* Left2;
		Jaguar* Right1;
		Jaguar* Right2;
};

#endif

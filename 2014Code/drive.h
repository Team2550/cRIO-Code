#ifndef DRIVE_H
#define DRIVE_H
#include <math.h>
#include "WPILib.h"
#include "xBox.h"

class Drive
{
	public:
		Drive(const int stickPort);
		~Drive();

		void autoDrive();
		void remoteDrive();
	private:
		Joystick* stick;
		//left and right drive motors
		Jaguar* Left;
		Jaguar* Right;
};

#endif






#ifndef DRIVE_H
#define DRIVE_H
#include "WPILib.h"
#include <cmath>

class Drive
{
	public:
		Drive();
		~Drive();

		void autoDrive();
		void remoteDrive(Joystick* stick);
	private:
		//left and right drive motors
		Jaguar* Left;
		Jaguar* Right;
};

#endif

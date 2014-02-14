#ifndef DRIVE_H
#define DRIVE_H
#include <math.h>
#include "WPILib.h"
#include "xBox.h"

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

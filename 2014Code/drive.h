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
		float getSpeedMult();
	private:
		Joystick* stick;
		//left and right drive motors
		Jaguar* left;
		Jaguar* right;
		float speedMult;//speed multiplier
};

#endif






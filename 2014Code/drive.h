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

		void move(float leftS, float rightS);
		void remoteDrive();
		void stop();
		float getSpeedMult();
	private:
		Joystick* stick;
		//left and right drive motors
		Victor* left;
		Victor* right;
		float speedMult;//speed multiplier
};

#endif






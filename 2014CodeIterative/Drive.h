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

		void move(float leftSpeed, float rightSpeed);
		void remoteDrive(float leftStick, float rightStick, bool boost);
		void stop();
		float getSpeedMult();
	private:
		//left and right Drive motors
		Victor* left;
		Victor* right;
		float speedMult;//speed multiplier
};

#endif






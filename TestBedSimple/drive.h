#ifndef DRIVE_H
#define DRIVE_H
#include <WPILib.h>
#include <cmath>

class drive
{
	public:
		drive();
		~drive();
		void RemoteDrive();
		void AutoDrive();
		float LeftStickY;
		float RightStickY;
	private:
		Joystick *xbox;
		Victor *LeftMotor;//motor controller
		Victor *RightMotor;
};

#endif

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
		// AutoDrive();
	private:
		Joystick *LeftStick;
		Joystick *RightStick;
		Victor *LeftMotor;//motor controller
		Victor *RightMotor;
};

#endif

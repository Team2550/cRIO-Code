#ifndef DRIVE_H
#define DRIVE_H
#include <WPILib.h>

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
	Victor *LeftMotor;
	Victor *RightMotor;
};

#endif

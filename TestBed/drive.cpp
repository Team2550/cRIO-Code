#include "drive.h"

drive::drive()
{
	LeftStick = new Joystick(2);// 2 is port number
	RightStick = new Joystick(1);
	LeftMotor = new Victor(1);//change these to ports that they are plugged into
	RightMotor = new Victor(2);
}

drive::~drive()
{
	delete LeftStick;
	delete RightStick;
	delete LeftMotor;
	delete RightMotor;
}

//bare bones implementation of motor control with xbox controller...
void drive::RemoteDrive()
{
	float LeftStickY = -LeftStick -> GetRawAxis(5);//up is negative for xbox controller axis
	float RightStickY = -RightStick -> GetRawAxis(2);
	//moves motors
	if (abs(LeftStickY) > 0.1)// 0.1 accounts for joystick dead zone
		LeftMotor->Set(LeftStickY);
	if (abs(RightStickY) > 0.1)
		RightMotor->Set(RightStickY);
}

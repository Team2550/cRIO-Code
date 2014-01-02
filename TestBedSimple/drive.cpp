#include "drive.h"

drive::drive()
{
	LeftStick = new Joystick(1);// argument is the index number of joystick
	RightStick = new Joystick(5);
	LeftMotor = new Victor(1);
	RightMotor = new Victor(2);
}

drive::~drive()
{
	delete LeftStick;
	delete RightStick;
	delete LeftMotor;
	delete RightMotor;
}

void drive::AutoDrive()
{
	LeftMotor->Set(.75);
	Wait(5);
	LeftMotor->Set(0);
}

//bare bones implementation of motor control with xbox controller...
void drive::RemoteDrive()
{
	LeftStickY = -LeftStick -> GetRawAxis(5);//up is negative for xbox controller axis
	RightStickY = -RightStick -> GetRawAxis(2);
	//moves motors
	if (abs(LeftStickY) > 0.1)// number accounts for joystick dead zone
		LeftMotor->Set(LeftStickY);
	else
		LeftMotor->Set(0);
	if (abs(RightStickY) > 0.1)
		RightMotor->Set(RightStickY);
	else
		LeftMotor->Set(0);
}

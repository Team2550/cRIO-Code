#include "drive.h"

drive::drive()
{
	xbox = new Joystick(1);// argument is the index number of joystick
	LeftMotor = new Victor(4);
	RightMotor = new Victor(2);
}

drive::~drive( )
{
	delete xbox;
	delete LeftMotor;
	delete RightMotor;
}

void drive::AutoDrive()
{
	LeftMotor->Set(.75);
	Wait(2);
	LeftMotor->Set(0);
	//////////////////////////
	RightMotor->Set(.75);
	Wait(2);
	RightMotor->Set(0);
}

//bare bones implementation of motor control with xbox controller...
void drive::RemoteDrive()
{
	LeftStickY = -xbox -> GetRawAxis(1);//up is negative for xbox controller axis
	RightStickY = -xbox -> GetRawAxis(2);
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

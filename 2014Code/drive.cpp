#include "drive.h"

Drive::Drive()
{
	//motor creation
	Left1 = new Jaguar(1);
	Left2 = new Jaguar(2);
	Right1 = new Jaguar(3);
	Right2 = new Jaguar(4);
}
Drive::~Drive()
{
	//motor deletion
	delete Left1;
	delete Left2;
	delete Right1;
	delete Right2;
}

void Drive::autoDrive()
{
	//will eventually be programmed to go forward into 
	//team zone must be calibrated
}

void Drive::remoteDrive(Joystick* remote)
{
	//See documentation repository on Git server for axis
		//mappings of xbox controller
	float leftStick = -remote->GetRawAxis(1);
	float rightStick = -remote->GetRawAxis(2);
	
	//basic movements
	//fabs() is the flaot version of abs()
	if (fabs(leftStick) > 0.1)
	{
		// number accounts for joystick dead zone
		Left1->Set(leftStick);
		Left2->Set(leftStick);
	}
	else
	{
		Left1->Set(0);
		Left2->Set(0);
	}
	if (fabs(rightStick) > 0.1)
	{
		Right1->Set(rightStick);
		Right2->Set(rightStick);
	}
	else
	{
		Right1->Set(0);
		Right2->Set(0);
	}
}

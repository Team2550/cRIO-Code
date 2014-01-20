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
	//will eventually be programmed to go forward into team zone
	//must be calibrated
}

//CHOOSE CONTROLS FOR 2014 ROBOT W/ TEAM!!!!!!!!!!!!!!!!!!!!!
void Drive::remoteDrive()
{
	//See documentation repository on Git server for axis mappings
		//of xbox controller
	LeftStickY = -xbox->GetRawAxis(1);
	RightStickY = -xbox->GetRawAxis(2);
	
	//basic movements
	if (abs(LeftStickY) > 0.1)// number accounts for joystick dead zone
	{
		Left1->Set(LeftStickY);
		Left2->Set(LeftStickY);
	}
	else
	{
		Left1->Set(0);
		Left2->Set(0);
	}
	if (abs(RightStickY) > 0.1)
	{
		Right1->Set(RightStickY);
		Right2->Set(RightStickY);
	}
	else
	{
		Right1->Set(0);
		Right2->Set(0);
	}
}

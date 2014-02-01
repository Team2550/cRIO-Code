#include "drive.h"

Drive::Drive()
{
	//motor creation
	Left = new Jaguar(1);
	Right = new Jaguar(3);
}
Drive::~Drive()
{
	delete Left;
	delete Right;
}

/*
 * FUNCTION: autoDrive
 * AUTHOR: Caleb Reister
 * DESCRIPTION:
 * 	autoDrive runs any drivetrain-related
 * 	movements during the autonomous period of
 * 	the match.
 */
void Drive::autoDrive()
{
}

/*
 * FUNCTION: remoteDrive
 * AUTHOR: Caleb Reister
 * DESCRIPTION:
 * 	Handles movement based on joystick input.
 * 	Currently configured for xbox controllers.
 * PARAMETERS:
 * 	(I) remote - the joystick to use for input
 * 		pointed due to WPILib size
 */
void Drive::remoteDrive(Joystick* remote)
{
	//See documentation repository on Git server for axis
		//mappings of xbox controller
	float leftStick = -remote->GetRawAxis(1);
	float rightStick = -remote->GetRawAxis(2);
	
	//basic movements
	//fabs() is the float version of abs()
	if (fabs(leftStick) > 0.1)//number accounts for dead zone
		Left->Set(leftStick);
	else
		Left->Set(0);
	if (fabs(rightStick) > 0.1)
		Right->Set(rightStick);
	else
		Right->Set(0);
}

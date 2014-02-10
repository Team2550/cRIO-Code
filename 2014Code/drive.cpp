#include "drive.h"

Drive::Drive()
{
	//motor creation
	Left = new Jaguar(1);
	Right = new Jaguar(2);
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
 * 	(I) stick - the joystick to use for input
 * 		pointed due to WPILib size
 */
void Drive::remoteDrive(Joystick* stick)
{
	//See documentation repository on Git server for axis
		//mappings of xbox controller
	float leftStick = stick->GetRawAxis(2);
	float rightStick = stick->GetRawAxis(5);
	
	//basic movements
	//fabs() is the float version of abs()
	if (fabs(leftStick) > 0.2)//number accounts for dead zone
		Left->Set(-leftStick * .25);
	else
		Left->Set(0);
	if (fabs(rightStick) > 0.2)
		Right->Set(rightStick * .25);
	else
		Right->Set(0);
}

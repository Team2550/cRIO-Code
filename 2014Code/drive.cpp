#include "drive.h"

Drive::Drive(const int stickPort)
{
	stick = new Joystick(stickPort);
	//motor creation
	left = new Jaguar(1);
	right = new Jaguar(2);
	speedMult = .5;
}
Drive::~Drive()
{
	delete stick; 
	delete left;
	delete right;
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
	left->Set(.5);
	right->Set(.5);
	Wait(3);
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
void Drive::remoteDrive()
{
	//See documentation repository on Git server for axis
		//mappings of xbox controller
	float leftStick = stick->GetRawAxis(xbox::axis::leftY);
	float rightStick = stick->GetRawAxis(xbox::axis::rightY);
	
	//basic movements
	//fabs() is the float version of abs()
	if (fabs(leftStick) > 0.2)//number accounts for dead zone
		left->Set(-leftStick * speedMult);
	else
		left->Set(0);
	if (fabs(rightStick) > 0.2)
		right->Set(rightStick * speedMult);
	else
		right->Set(0);
	
	//speed limiting
	if (stick->GetRawButton(xbox::btn::back))
		speedMult = .5;
	else if (stick->GetRawButton(xbox::btn::start))
		speedMult = 1;
}

/*
 * FUNCTION: getSpeedMult
 * RETURN: speed multiplier of drive object
 */
float Drive::getSpeedMult()
{
	return speedMult;
}

#include "Drive.h"

Drive::Drive(const int stickPort)
{
	stick = new Joystick(stickPort);
	//motor creation
	left = new Victor(1);
	right = new Victor(2);
	speedMult = .65;
}
Drive::~Drive()
{
	delete stick; 
	delete left;
	delete right;
}

void Drive::move(float leftS, float rightS)
{
	left->Set(leftS);
	right->Set(-rightS);
}

/*
 * FUNCTION: stop
 * DESCRIPTION: stops all Drive motors
 */
void Drive::stop()
{
	left->Set(0);
	right->Set(0);
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
	if (stick->GetRawButton(xbox::btn::rb))
		speedMult = 1;
	else
		speedMult = .65;
}

/*
 * FUNCTION: getSpeedMult
 * RETURN: speed multiplier of Drive object
 */
float Drive::getSpeedMult()
{
	return speedMult;
}

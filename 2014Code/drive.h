#ifndef DRIVE_H
#define DRIVE_H
#include "WPILib.h"
#include <cmath>

class Drive
{
	public:
		Drive();
		~Drive();
		/*
		 * FUNCTION: autoDrive
		 * AUTHOR: Caleb Reister
		 * DESCRIPTION:
		 * 	autoDrive runs any drivetrain-related
		 * 	movements during the autonomous period of
		 * 	the match.
		 */
		void autoDrive();
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
		void remoteDrive(Joystick* remote);
	private:
		//left and right drive motors
		Jaguar* Left1;
		Jaguar* Left2;
		Jaguar* Right1;
		Jaguar* Right2;
};

#endif

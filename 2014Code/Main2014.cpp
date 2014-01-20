/*
 * AUTHOR: CALEB REISTER
 * EMAIL: calebreister@gmail.com
 * DATE: 2014-01-19
 * DEV ENV: Windriver
 * TEMPLATE: TestBedSimple, SimpleRobot
 * DESCRIPTION:
 * 	This is the primary code for the 2014 competition
 */

#include "Main2014.h"

robot::robot()
{
	//Watchdog must be enabled for the competition
	//I have left it disabled for testing
	GetWatchdog().SetEnabled(false);
	DriveSys = new Drive();
}
robot::~robot()
{
	delete DriveSys;
}

void robot::Autonomous()
{
	//implement this!
}

void robot::OperatorControl()
{
	
}

START_ROBOT_CLASS(robot);

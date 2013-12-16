/*
 * AUTHOR: Caleb Reister
 * EMAIL: calebreister@gmail.com
 * DATE: 2013-12-16
 * DEV ENV: WindRiver
 * TEMPLATE: SimpleRobot
 * DESCRIPTION:
 * 	This is a program for the Team 2550 test bed used for the purpose of training
 * 	programmers.
 */

#include "MyRobot.h"

TestBed::TestBed(void)//initialization function
{
	GetWatchdog().SetEnabled(false);
	DriveSys = new drive();
}

/*void TestBed::Autonomous(void)
{
	//not yet implemented
}*/

void TestBed::OperatorControl(void)
{
	while (IsOperatorControl())
	{
		DriveSys->RemoteDrive();
		Wait(0.005);// wait for a motor update time
	}
}

TestBed::~TestBed(void)
{
	delete DriveSys;
}

START_ROBOT_CLASS(TestBed);


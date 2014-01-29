#include "Main2014.h"

robot::robot()
{
	//Watchdog must be enabled for the competition
	//I have left it disabled for testing
	GetWatchdog().SetEnabled(false);
	tank = new Drive();
	xbox = new Joystick(1);
	launcher = new DoublePiston(1,2,3,4);
}
robot::~robot()
{
	delete tank;
}

void robot::Autonomous()
{
	//implement this!
	tank->autoDrive();
}

void robot::OperatorControl()
{
	launcher->pull();
	tank->remoteDrive(xbox);
}

START_ROBOT_CLASS(robot);

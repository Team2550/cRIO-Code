#include "Main2014.h"

robot::robot()
{
	//Watchdog must be enabled for the competition
	//I have left it disabled for testing
	GetWatchdog().SetEnabled(false);
	//CONTROL
	xbox = new Joystick(1);
	tank = new Drive();
	//PNEUMATICS
	compressor = new Relay(1);//FINALIZE PORT
	launcher = new DoublePiston(1,2,3,4);
}
robot::~robot()
{
	delete xbox;
	delete tank;
	delete compressor;
	delete launcher;
}

void robot::Autonomous()
{
	compressor->Set(Relay::kOn);
	launcher->push();//prime catapult
	
	tank->autoDrive();//Not yet implemented
}

void robot::OperatorControl()
{
	while (IsOperatorControl())
	{
		tank->remoteDrive(xbox);
		//launch catapult
		if (xbox->GetRawButton(6))//check RB on xbox
			launcher->pull();
		//reprime catapult
		if (xbox->GetRawButton(5))//check LB
			launcher->push();
	}
	
	launcher->off();
	compressor->Set(Relay::kOff);
}

START_ROBOT_CLASS(robot);

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
	comp = new Compressor(1, 2);
	launcher = new DoublePiston(1, 2, 3, 4);
}
robot::~robot()
{
	delete xbox;
	delete tank;
	delete comp;
	delete launcher;
}

void robot::Autonomous()
{
	comp->Start();
	//tank->autoDrive();//Not yet implemented
}

void robot::OperatorControl()
{	
	while (IsOperatorControl())
	{	
		comp->Start();
		SmartDashboard::PutNumber("Compressor:", comp->GetPressureSwitchValue());
		
		tank->remoteDrive(xbox);
		
		//launch catapult
		if (xbox->GetRawButton(6))//check RB on xbox remote
		{
			//NOTE: REVERSE PUSH AND PULL
			launcher->pull();
			SmartDashboard::PutString("Launcher:", "PULL");
		}
		//reprime catapult
		if (xbox->GetRawButton(5))//check LB
		{
			launcher->push();
			SmartDashboard::PutString("Launcher:", "PUSH");
		}

	}
	
	launcher->off();
	comp->Stop();
}

START_ROBOT_CLASS(robot);

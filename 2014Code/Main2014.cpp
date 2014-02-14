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
	pult = new launcher();
}
robot::~robot()
{
	delete xbox;
	delete tank;
	delete comp;
	delete pult;
}

void robot::Autonomous()
{
	//comp->Start();
	//tank->autoDrive();//Not yet implemented
}

void robot::OperatorControl()
{
	comp->Start();
	while (IsOperatorControl())
	{	
		tank->remoteDrive(xbox);
		pult->set(xbox);
		dashSend();
	}
	
	pult->off();
	comp->Stop();
}

void robot::dashSend()
{
	SmartDashboard::PutBoolean("Compressor:", comp->GetPressureSwitchValue());
	SmartDashboard::PutString("Launcher:", pult->getStatus());
}

START_ROBOT_CLASS(robot);

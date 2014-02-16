#include "Main2014.h"

robot::robot()
{
	//Watchdog must be enabled for the competition
	//I have left it disabled for testing
	GetWatchdog().SetEnabled(false);
	//CONTROL
	driver = new Joystick(DRIVER_PORT);
	pultCtrl = new Joystick(PULT_CTRL_PORT);
	
	//MOTORS
	tank = new Drive(DRIVER_PORT);
	elToro = new lift(PULT_CTRL_PORT);

	//PNEUMATICS
	comp = new Compressor(1, 1);
	pult = new launcher(PULT_CTRL_PORT);
}
robot::~robot()
{
	delete driver;
	delete pultCtrl;
	delete tank;
	delete elToro;
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
		tank->remoteDrive();
		elToro->run();
		pult->set();
		dashSend();
	}
	
	pult->off();
	comp->Stop();
}

void robot::dashSend()
{
	SmartDashboard::PutBoolean("Compressor:", comp->GetPressureSwitchValue());
	SmartDashboard::PutString("Launcher:", pult->getStatus());
	SmartDashboard::PutString("Lift:", elToro->getStatus());
}

START_ROBOT_CLASS(robot);

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
	move = new Drive(DRIVER_PORT);
	elToro = new lift(PULT_CTRL_PORT);

	//PNEUMATICS
	comp = new Compressor(1, 1);
	pult = new launcher(PULT_CTRL_PORT);
}
robot::~robot()
{
	delete driver;
	delete pultCtrl;
	delete move;
	delete elToro;
	delete comp;
	delete pult;
}

void robot::Autonomous()
{
	//comp->Start();
	//move->autoDrive();//Not yet implemented
}

void robot::OperatorControl()
{
	comp->Start();
	while (IsOperatorControl())
	{	
		move->remoteDrive();
		elToro->run();
		pult->set();
		dashSend();
	}
	
	pult->off();
	comp->Stop();
}

void robot::dashSend()
{
	SmartDashboard::PutBoolean("Compressor", comp->GetPressureSwitchValue());
	//SmartDashboard::PutBoolean("Launcher", pult->getLaunch());
	//SmartDashboard::PutBoolean("Trigger", pult->getTrigger());
	//SmartDashboard::PutNumber("El Toro", -pultCtrl->GetRawAxis(xbox::axis::leftY));
		
	SmartDashboard::PutNumber("Left Motors",
			-driver->GetRawAxis(xbox::axis::leftY));
	SmartDashboard::PutNumber("Right Motors",
			-driver->GetRawAxis(xbox::axis::rightY));
	SmartDashboard::PutNumber("Speed Multiplier", move->getSpeedMult());
}

START_ROBOT_CLASS(robot);
;

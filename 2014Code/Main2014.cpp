#include "Main2014.h"

robot::robot()
{
	//Watchdog must be enabled for the competition
	//I have left it disabled for testing
	GetWatchdog().SetEnabled(true);
	//CONTROL
	driver = new Joystick(DRIVER_PORT);
	pultCtrl = new Joystick(PULT_CTRL_PORT);
	
	//MOTORS
	move = new Drive(DRIVER_PORT);
	elChuro = new lift(PULT_CTRL_PORT);

	//PNEUMATICS
	comp = new Compressor(1, 1);
	pult = new launcher(PULT_CTRL_PORT);
	feed();
}
robot::~robot()
{
	delete driver;
	delete pultCtrl;
	delete move;
	delete elChuro;
	delete comp;
	delete pult;
}

void robot::Autonomous()
{
	elChuro->autoRun(-.5);
	Wait(.5);
	feed();
	elChuro->autoRun(.5);
	move->autoDrive(1, 1, 1, false);
	feed();
	pult->load();
	feed();
	//move->autoDrive(.25, .5, 3);
	feed();
	//pult->autoLaunch();
	feed();
	elChuro->autoRun(0);
}

void robot::OperatorControl()
{
	comp->Start();
	while (IsOperatorControl())
	{
		move->remoteDrive();
		elChuro->run();
		feed();
		pult->remoteLaunch();
		feed();
		dashSend();
		feed();
	}
	
	pult->off();
	comp->Stop();
}

/*
 * FUNCTION: feed
 * DESCRIPTION: just makes feeding watchdog line less overwhelming
 * 	among the rest of the code
 */
void robot::feed()
{
	GetWatchdog().Feed();
}

/*
 * FUNCTION: dashSend
 * DESCRIPTION: send SmartDashboard collected data
 * DATA SENT:
 * 	compressor status (running?)
 * 	launcher status (ready?)
 * 	trigger status (ready?)
 * 	El Toro status (running? direction?)
 * 	left motor status (speed? direction?)
 * 	right motor status (speed? direction?)
 * 	speed multiplier
 */
void robot::dashSend()
{
	SmartDashboard::PutBoolean("Compressor", comp->GetPressureSwitchValue());
	SmartDashboard::PutBoolean("Launcher", pult->getLaunchStatus());
	SmartDashboard::PutBoolean("Trigger", pult->getTriggerStatus());
	SmartDashboard::PutNumber("El Toro", -pultCtrl->GetRawAxis(xbox::axis::leftY));
		
	SmartDashboard::PutNumber("Left Motors",
			-driver->GetRawAxis(xbox::axis::leftY));
	SmartDashboard::PutNumber("Right Motors",
			-driver->GetRawAxis(xbox::axis::rightY));
	SmartDashboard::PutNumber("Speed Multiplier", move->getSpeedMult());
}

START_ROBOT_CLASS(robot);
;

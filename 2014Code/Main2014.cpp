#include "Main2014.h"

robot::robot()
{
	//Watchdog must be enabled for the competition
	GetWatchdog().SetEnabled(true);
	
	//CONTROL
	Driver = new Joystick(DRIVER_PORT);
	pultCtrl = new Joystick(PULT_CTRL_PORT);
	
	//MOTORS
	move = new Drive(DRIVER_PORT);
	elChuro = new Lift(PULT_CTRL_PORT);

	//PNEUMATICS
	comp = new Compressor(1, 1);
	pult = new Launcher(PULT_CTRL_PORT, DRIVER_PORT);
	
	sonic = new AnalogChannel(2);
}

void robot::RobotInit()
{
	//ULTRASONIC SENSOR
	sonicInches = 0;
	for (int i = 0; i < SONIC_SAMPLE; i++)
		sonicLog[i] = 0;
	sonicHotZone = false;
	feed();
}
robot::~robot()
{
	delete Driver;
	delete pultCtrl;
	delete move;
	delete elChuro;
	delete comp;
	delete pult;
	delete sonic;
}

void robot::AutonomousInit()
{	
	elChuro->autoRun(1);
	move->move(.55, .5);
	feed();
	Wait(.5);
	pult->load();
	feed();
	elChuro->autoRun(0);
	feed();
	
	//Drive
	/*do
	{
		move->move(.55, .5);
		sonicInches = sonic->GetVoltage() / VOLTS_INCH;
		//This if statement appears to be necessary
		//in order to deal with some erratic values from the ultrasonic sensor.
		if (sonicInches < 20)
			sonicInches = 49;
		feed();
	} while (sonicInches > 48);*/
	move->move(.55, .5);
	for (int i = 0; i < 42; i++)//wait 4.2 seconds
	{
		Wait(.1);
		feed();
	}
	move->stop();
	/*for (int i = 0; i < 15; i++)
	{
		Wait(.1);
		feed();
	}
	pult->autoLaunch();*/
	feed();
}

void robot::TeleopPeriodic()
{
	move->remoteDrive();
	elChuro->run();
	
	const double wdExpire = GetWatchdog().GetExpiration();
	GetWatchdog().SetExpiration(1.25);
	pult->remoteLaunch();
	GetWatchdog().SetExpiration(wdExpire);
	
	sonicInches = sonic->GetVoltage() / VOLTS_INCH;
	if (sonicInches > 66
		&& sonicInches < 74)
		sonicHotZone = true;
	else
		sonicHotZone = false;
	
	dashSend();
	feed();
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
 * 	Launcher status (ready?)
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
	//SmartDashboard::PutNumber("El Toro", -pultCtrl->GetRawAxis(xbox::axis::leftY));
	std::cout << setw(10) << "sonicInches: " << sonicInches << endl;
	SmartDashboard::PutBoolean("LAUNCH ZONE", sonicHotZone);
}

START_ROBOT_CLASS(robot);

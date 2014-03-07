#include "Main2014.h"

robot::robot()
{
	//Watchdog must be enabled for the competition
	GetWatchdog().SetEnabled(true);
	
	//CONTROL
	driver = new Joystick(DRIVER_PORT);
	pultCtrl = new Joystick(PULT_CTRL_PORT);
	
	//MOTORS
	move = new Drive(DRIVER_PORT);
	elChuro = new lift(PULT_CTRL_PORT);

	//PNEUMATICS
	comp = new Compressor(1, 1);
	pult = new launcher(PULT_CTRL_PORT, DRIVER_PORT);
	
	//ULTRASONIC SENSOR
	sonic = new AnalogChannel(2);
	sonicInches = 0;
	sonicHotZone = false;
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
	delete sonic;
}

void robot::Autonomous()
{
	//float wdExpire = GetWatchdog().GetExpiration();
	elChuro->autoRun(1);
	Wait(.2);																							
	feed();
	
	move->move(.55, .5);
	Wait(.5);
	pult->load();
	feed();
	
	sonicInches = sonic->GetVoltage() / VOLTS_INCH;
	//drive
	while (sonicInches > 48)
	{
		sonicInches = sonic->GetVoltage() / VOLTS_INCH;
		feed();
	}
	move->stop();	
	
	//pult->autoLaunch();
	feed();
	elChuro->autoRun(0);
	comp->Start();
	feed();
}

void robot::OperatorControl()
{
	comp->Start();
	while (IsOperatorControl())
	{
		move->remoteDrive();
		elChuro->run();
		pult->remoteLaunch();
		
		sonicInches = sonic->GetVoltage() / VOLTS_INCH;
		if (sonicInches > 46
			&& sonicInches < 5)
			sonicHotZone = true;
		else
			sonicHotZone = false;
		
		dashSend();
		feed();
	}
	
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
	//SmartDashboard::PutNumber("El Toro", -pultCtrl->GetRawAxis(xbox::axis::leftY));
	std::cout << setw(10) << "sonicInches: " << sonicInches << endl;
	SmartDashboard::PutBoolean("LAUNCH ZONE", sonicHotZone);
}

START_ROBOT_CLASS(robot);

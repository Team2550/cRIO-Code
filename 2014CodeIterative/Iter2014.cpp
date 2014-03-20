#include "Iter2014.h"

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
	
	//ULTRASONIC SENSOR
	sonic = new AnalogChannel(2);
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
/////////////////////////////////////////////////////////////
void robot::RobotInit()
{
	feed();
}

void robot::AutonomousInit()
{	
	//fill the ultrasonic sensor array so that averaging
	//is accurate
	for (int i = 0; i < SONIC_SAMPLE * 2; i++)
		sonicRead();
	
	elChuro->autoRun(1);
	move->move(.55, .5);
	feed();
	Wait(.5);
	pult->load();
	feed();
	elChuro->autoRun(0);
	feed();
	
	//Drive
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

void robot::AutonomousPeriodic()
{

}
/////////////////////////////////////////////////////////////////////////
void robot::TeleopInit()
{

}

void robot::TeleopPeriodic()
{
	move->remoteDrive();
	elChuro->run();
	
	const double wdExpire = GetWatchdog().GetExpiration();
	GetWatchdog().SetExpiration(1.25);
	pult->remoteLaunch();
	GetWatchdog().SetExpiration(wdExpire);

	dashSend();
	feed();
}
///////////////////////////////////////////////////////////////////
void robot::DisabledInit()
{
	
}

void robot::DisabledPeriodic()
{
	dashSend();
}
///////////////////////////////////////////////////////////////////
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
 * DESCRIPTION: send data to the driverstation
 */
void robot::dashSend()
{
	SmartDashboard::PutBoolean("Compressor", comp->GetPressureSwitchValue());
	SmartDashboard::PutBoolean("Launcher", pult->getLaunchStatus());
	SmartDashboard::PutBoolean("Trigger", pult->getTriggerStatus());
	
	SonicData sonicIn = sonicRead();
	std::cout << setw(10) << "Inches: " << sonicIn.avg << "NAVG: " << sonic->GetVoltage() / VOLTS_INCH << endl;
	SmartDashboard::PutBoolean("LAUNCH ZONE", sonicIn.hotZone);
}

//Averages and returns the inch reading of the ultrasonic sensor
//Updates sonicHotZone
SonicData robot::sonicRead()
{
	static long double sonicLog[SONIC_SAMPLE];
	SonicData out;
	out.avg = 0;
	
	//shift sonicLog data
	sonicLog[SONIC_SAMPLE - 1] = sonicLog[SONIC_SAMPLE - 2];//shift last value
	for (int i = 1; i < SONIC_SAMPLE - 1; i++)//shift mid values
		sonicLog[i] = sonicLog[i - 1];
	sonicLog[0] = sonic->GetVoltage() / VOLTS_INCH;//add new 1st value
	
	//get the average of sonicLog
	for(int i = 0; i < SONIC_SAMPLE; i++)
		out.avg += sonicLog[i];
	out.avg /= SONIC_SAMPLE;
	
	//Check for hot zone
	if (out.avg > 66
		&& out.avg < 74)
		out.hotZone = true;
	else
		out.hotZone = false;
	
	return out;
}


START_ROBOT_CLASS(robot);

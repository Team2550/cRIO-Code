#include "Iter2014.hh"

robot::robot()
{
	//Watchdog must be enabled for the competition
	GetWatchdog().SetEnabled(true);
	
	//CONTROL
	driver = new Joystick(DRIVER_PORT);
	pultCtrl = new Joystick(PULT_CTRL_PORT);
	
	//MOTORS
	move = new Drive();
	elChuro = new Lift();

	//PNEUMATICS
	comp = new Compressor(1, 1);
	pult = new Launcher();
	
	//ULTRASONIC SENSOR
	sonic = new AnalogChannel(2);
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
/////////////////////////////////////////////////////////////
void robot::RobotInit()
{
	//fill the ultrasonic sensor array so that averaging
	//is accurate
	for (int i = 0; i < SONIC_SAMPLE * 2; i++)
		sonicRead();
	feed();
	comp->Start();
}

void robot::AutonomousInit()
{
	//pult->setState(triggerBack);
	//elChuro->autoRun(1);
	//feed();
	//Wait(.5);
	//pult->setState(load);
	feed();
	//elChuro->autoRun(0);
	feed();
	
	//Drive
	//96in/2s
	move->move(.5, .45);
	for (int i = 0; i < 20; i++)//wait with feed
	{
		Wait(.1);
		feed();
	}
	move->stop();
	//pult->setState(launch);
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
	move->remoteDrive(driver->GetRawAxis(xbox::axis::leftY),
					  driver->GetRawAxis(xbox::axis::rightY),
					  driver->GetRawButton(xbox::btn::rb));
	elChuro->run(pultCtrl->GetRawAxis(xbox::axis::leftY));
	
	//Launcher control
	if (pultCtrl->GetRawButton(xbox::btn::rb) && driver->GetRawButton(xbox::btn::b))
	{
		const double wdExpire = GetWatchdog().GetExpiration();
		GetWatchdog().SetExpiration(1.25);
		pult->setState(launch);
		GetWatchdog().SetExpiration(wdExpire);
	}
	else if (pultCtrl->GetRawButton(xbox::btn::lb)) 
		pult->setState(load);
	else if (pultCtrl->GetRawButton(xbox::btn::y))
		pult->setState(triggerBack);
	else if (pultCtrl->GetRawButton(xbox::btn::x))
		pult->setState(triggerFwd);

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
	cout << setw(10) << "ULTRASONIC IN: " << sonicIn.avg << endl;
	//SmartDashboard::PutNumber("ULTRASONIC IN", sonicIn.avg);
	SmartDashboard::PutBoolean("LAUNCH ZONE", sonicIn.hotZone);
}

//Averages and returns the inch reading of the ultrasonic sensor
//Updates sonicHotZone
SonicData robot::sonicRead()
{
    //Ultrasonic hot zone
	const int TOO_FAR = 120;
	const int TOO_CLOSE = 60;
	
	static long double sonicLog[SONIC_SAMPLE];
	SonicData out;
	out.avg = 0;
	
	//collect data
	for (int i = 0; i < SONIC_SAMPLE; i++)
		sonicLog[i] = sonic->GetVoltage() / VOLTS_INCH;
	
	//get the average of sonicLog
	for(int i = 0; i < SONIC_SAMPLE; i++)
	{
		if (sonicLog[i] < 25)
			sonicLog[i] = sonic->GetVoltage() / VOLTS_INCH;
		out.avg += sonicLog[i];
	}
	out.avg /= SONIC_SAMPLE;
	
	//Check for hot zone
	if (out.avg > TOO_CLOSE
		&& out.avg < TOO_FAR)
		out.hotZone = true;
	else
		out.hotZone = false;
	
	return out;
}


START_ROBOT_CLASS(robot);

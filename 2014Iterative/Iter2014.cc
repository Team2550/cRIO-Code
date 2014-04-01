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
}

void robot::AutonomousInit()
{	
	pult->setState(triggerBack);
	elChuro->autoRun(1);
	//move->move(.25, .2);
	//feed();
	//Wait(.5);
	pult->setState(load);
	feed();
	elChuro->autoRun(0);
	feed();
	
	//Drive
	/*for (int i = 0; i < 42; i++)//wait 4.2 seconds
	{
		Wait(.1);
		feed();
	}*/
	//move->move(.55, .5);
	//move->stop();
	//pult->setState(launch);
	feed();
}

void robot::AutonomousPeriodic()
{
	static bool done;
	if (done == false)
	{
		if (sonicRead().hotZone == true)
		{
			move->stop();
			bool sonicValid = false;
			if (sonicRead().hotZone == true)
				sonicValid = true;
			//init and collect data
			/*const int SONIC_CHECK = 5;
			SonicData sonicCheck[SONIC_CHECK];
			bool sonicValid;
			for (int i = 0; i < SONIC_CHECK; i++)
				sonicCheck[i] = sonicRead();
			feed();
			
			//analyze data
			bool runChecks = true;
			int i = SONIC_CHECK - 1;
			while (i >= 0 && runChecks == true)
			{
				if (sonicCheck[i].hotZone != true)
				{
					sonicValid = false;
					runChecks = false;
				}
				i--;
				feed();
			}
			
			std::cout << sonicValid << " ";
			
			//make decision*/
			if (sonicValid)
			{
				pult->setState(launch);
				done = true;
			}
			else
				done = false;
		}
		else
		{
			move->move(.25, .2);
			done = false;
		}
		feed();
	}
	else
	{
		move->stop();
		dashSend();
	}
	
	feed();
	std::cout << done << std::endl;
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
	std::cout << setw(10) << "ULTRASONIC IN: " << sonicIn.avg << std::endl;
	SmartDashboard::PutNumber("ULTRASONIC IN", sonicIn.avg);
	SmartDashboard::PutBoolean("LAUNCH ZONE", sonicIn.hotZone);
}

//Averages and returns the inch reading of the ultrasonic sensor
//Updates sonicHotZone
SonicData robot::sonicRead()
{
	const int TOO_FAR = 74;
	const int TOO_CLOSE = 66;
	
	//forward is fire
	//reverse is too far
	//off is too close
	Relay tooFarLight(2, Relay::kForwardOnly);
	Relay hotZoneLight(3, Relay::kForwardOnly);
	
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
	if (out.avg > TOO_CLOSE
		&& out.avg < TOO_FAR)
		out.hotZone = true;
	else
		out.hotZone = false;
	
	//run indicator lights
	/*if (out.hotZone)
		hotZoneLight.Set(Relay::kOn);
	else if (out.avg >= TOO_FAR)
		tooFarLight.Set(Relay::kOn);
	else
	{
		hotZoneLight.Set(Relay::kOff);
		tooFarLight.Set(Relay::kOff);
	}
	
	tooFarLight.Set(Relay::kOn);*/
	
	return out;
}


START_ROBOT_CLASS(robot);

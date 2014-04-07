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
	//fill the ultrasonic sensor data array
	for (int i = 0; i < SONIC_SAMPLE * 2; i++)
		sonicRead();
	feed();
	
	//Start the compressor, note that it will
	//not run until the robot is enabled
	comp->Start();
}

////////////////////////////////////////////////////////////////
void robot::AutonomousInit()
{
	pult->setState(triggerBack);
	elChuro->autoRun(1);
	pult->setState(load);
	for (int i = 0; i < 5; i++)
	{
		Wait(.1);
		feed();
	}
	elChuro->autoRun(0);
	elChuro->autoRun(-1);
	feed();
	
	//Drive ~120in
	driveStraight(.25, 120);
	move->move(-.6, -.55);
	Wait(.1);
	move->stop();
	for (int i = 0; i < 15; i++)
	{
		Wait(.1);
		feed();
	}
	elChuro->autoRun(0);
	pult->setState(launch);
	feed();
}

void robot::AutonomousPeriodic()
{
}
/////////////////////////////////////////////////////////////////////////
void robot::TeleopInit()
{
	//clear the console
	for (int i = 0; i < 100; i++)
		cout << endl;
    //figured it would be good to flush sonicLog[] again
    for (int i = 0; i < SONIC_SAMPLE * 2; i++)
		sonicRead();
	feed();
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
	for (int i = 0; i < 100; i++)
		cout << endl;
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
	SonicData out;
	out.avg = 0;
	
	//shift sonicLog data
	sonicLog[SONIC_SAMPLE - 1] = sonicLog[SONIC_SAMPLE - 2];//shift last value
	for (int i = 1; i <= SONIC_SAMPLE - 2; i++)//shift mid values
		sonicLog[i] = sonicLog[i - 1];
	//add new 1st value
	sonicLog[0] = sonic->GetVoltage() / VOLTS_INCH;
	
	//get the average of sonicLog
	for(int i = 0; i < SONIC_SAMPLE; i++)
		out.avg += sonicLog[i];
	out.avg /= SONIC_SAMPLE;
	
	//Check for hot zone
	if (out.avg >= TOO_CLOSE
		&& out.avg <= TOO_FAR)
		out.hotZone = true;
	else
		out.hotZone = false;
	
	return out;
}

/**@fn int robot::driveStraight(float minSpeed, float distInches)
   @param minSpeed The minimum speed for either motor to travel
   @param distInches The distance to travel in inches
   @return 0 for successful exit

   This function drives the robot either forward or backwards and attempts
   to make it drive a straight as possible. The right motor moves .05 slower
   than the left. (-) speed makes the robot drive backwards. The slowest this
   function will allow in any direction is .1: if something between .1 and -.1
   is given, it will automatically be changed. Also, if the minSpeed (the speed
   of the right motor) is too fast, it will automatically adjust so that the
   left motor goes as fast as possible. The function also takes watchdog into
   consideration. It uses the conversion factor 96in/2s @ speed (.5, .45).
   
   NOTE: as the distance increases the accuracy decreases due to floating point
   operations.
*/
void robot::driveStraight(double minSpeed, double distInches)
{
    //run value checks
    if (minSpeed < .1 && minSpeed > -.1)
    {
        if (minSpeed > 0)
            minSpeed += (.1 - minSpeed); //.1 = minSpeed + x
        else if (minSpeed < 0)
            minSpeed -= (.1 + minSpeed);//-.1 = minSpeed - x -> x = .1 + minSpeed
    }
    if (minSpeed > .95)
        minSpeed = .95;
    else if (minSpeed < -.95)
        minSpeed = -.95;
        
    //velocity proportion
    double vel = (48 * minSpeed) / .45; // in/s
    //get the travel time @ given speed
    double time = distInches / vel; // s
    
    //deal with watchdog
    feed();
    const double wdExpire = GetWatchdog().GetExpiration();
    GetWatchdog().SetExpiration(time + .5);
    //run motors
    if (minSpeed > 0)
    	move->move(minSpeed + .05, minSpeed);
    else if (minSpeed < 0)
        move->move(minSpeed - .05, minSpeed);
    else
        move->stop();
    Wait(time);
	GetWatchdog().SetExpiration(wdExpire);
	feed();
}

START_ROBOT_CLASS(robot);

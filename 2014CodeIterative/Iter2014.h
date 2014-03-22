#ifndef ITER2014_H
#define ITER2014_H
#include <iostream>
#include <iomanip>
#include "WPILib.h"
#include "xBox.h"
#include "Drive.h"
#include "Launcher.h"
#include "Lift.h"

const int DRIVER_PORT = 1;
const int PULT_CTRL_PORT = 2;

//Ultrasonic Sensor
const double VOLTS_INCH = 0.009765625;//5/512
const int SONIC_SAMPLE = 20;
//Package for ultrasonic sensor data
//Datatype returned by sonicRead function
struct SonicData
{
	long double avg;
	bool hotZone;
};

class robot : public IterativeRobot
{
	private:
		//CONTROL
		Joystick* driver;
		Joystick* pultCtrl;
		
		//motors
		Drive* move;
		Lift* elChuro;//the ball pickupper... nicknamed El Toro
		
		//PNEUMATICS
		Compressor* comp; //short for compressor
		Launcher* pult; //short for catapult
		
		AnalogChannel* sonic;//ultrasonic sensor
				
	public:
		robot();
		~robot();
		void RobotInit();
		void AutonomousInit();
		void AutonomousPeriodic();
		void TeleopInit();
		void TeleopPeriodic();
		void DisabledInit();
		void DisabledPeriodic();
		
		void feed();
		void dashSend();
		SonicData sonicRead();
		
		//ROBOT STATES
		
};

#endif

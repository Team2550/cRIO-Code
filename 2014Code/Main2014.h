#ifndef MAIN2014_H
#define MAIN2014_H
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
const int SONIC_SAMPLE = 10;
		
class robot : public IterativeRobot
{
	public:
		robot();
		void RobotInit();
		void AutonomousInit();
		void TeleopInit();
		void TeleopPeriodic();
		void DisabledInit();
		void DisabledPeriodic();
		
		void feed();
		void dashSend();
	private:
		~robot();
		//CONTROL
		Joystick* Driver;
		Joystick* pultCtrl;
		
		//motors
		Drive* move;
		Lift* elChuro;//the ball pickupper... nicknamed El Toro
		
		//PNEUMATICS
		Compressor* comp; //short for compressor
		Launcher* pult; //short for catapult
		
		//ULTRASONIC
		AnalogChannel* sonic;
		long double sonicInches;
		long double sonicLog[SONIC_SAMPLE];
		long double sonicAvg;
		bool sonicHotZone;
};

#endif

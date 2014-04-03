#ifndef ITER2014_H
#define ITER2014_H
#include <iostream>
#include <iomanip>
#include "WPILib.h"
#include "xBox.hh"
#include "Drive.hh"
#include "Launcher.hh"
#include "Lift.hh"

const int DRIVER_PORT = 1;
const int PULT_CTRL_PORT = 2;

//Ultrasonic Sensor
const int TOO_FAR = 120;
const int TOO_CLOSE = 60;
const double VOLTS_INCH = 0.009765625;//5/512
const int SONIC_SAMPLE = 10;

//Package for ultrasonic sensor data
//Datatype returned by sonicRead function
struct SonicData
{
	long double avg;//average value over SONIC_SAMPLE time
	bool hotZone;//whether or not the robot is in the hot zone
	//HOT ZONE IS SET BY TOO_FAR and TOO_CLOSE
};

class robot : public IterativeRobot
{
	private:
		//CONTROL
		Joystick* driver;
		Joystick* pultCtrl;
		
		//motors
		Drive* move;
		Lift* elChuro;//the ball lift... nicknamed El Churo by mistake
		
		//PNEUMATICS
		Compressor* comp; //short for compressor
		Launcher* pult; //short for catapult
		
		//ULTRASONIC
		AnalogChannel* sonic;//ultrasonic sensor
		long double sonicLog[SONIC_SAMPLE];
				
	public:
		robot();
		~robot();
		//CONTROL
		void RobotInit();
		void AutonomousInit();
		void AutonomousPeriodic();
		void TeleopInit();
		void TeleopPeriodic();
		void DisabledInit();
		void DisabledPeriodic();
		//COMMUNICATION/SENSORS
		void feed();
		void dashSend();
		SonicData sonicRead();
};

#endif

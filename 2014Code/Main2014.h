#ifndef MAIN2014_H
#define MAIN2014_H
#include "WPILib.h"
#include "xBox.h"
#include "drive.h"
#include "launcher.h"
#include "lift.h"

const int DRIVER_PORT = 1;
const int PULT_CTRL_PORT = 2;
const int SONIC_SAMPLE = 10;
const int DASH_UPDATE = 20;

//Volts/inch of Ultrasonic sensor
const double VOLTS_INCH = 0.009765625;//5/512
		
class robot : public SimpleRobot
{
	public:
		robot();//constructor
		~robot();//destructor
		void Autonomous();
		void OperatorControl();
		void feed();
		void dashSend();
	private:		
		//CONTROL
		Joystick* driver;
		Joystick* pultCtrl;
		
		//motors
		Drive* move;
		lift* elChuro;//the ball pickupper... nicknamed El Toro
		
		//PNEUMATICS
		Compressor* comp; //short for compressor
		launcher* pult; //short for catapult
		
		//ULTRASONIC
		AnalogChannel* sonic;
		long double sonicInches;
		bool sonicHotZone;
		long double sonicLog[SONIC_SAMPLE];
};

#endif

#ifndef MAIN2014_H
#define MAIN2014_H
#include "WPILib.h"
#include "xBox.h"
#include "drive.h"
#include "launcher.h"
#include "lift.h"

const int DRIVER_PORT = 1;
const int PULT_CTRL_PORT = 2;
		
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
		Ultrasonic* sonic;
};

#endif

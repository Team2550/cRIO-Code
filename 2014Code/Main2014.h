#ifndef MAIN2014_H
#define MAIN2014_H
#include "WPILib.h"
#include "xBox.h"
#include "drive.h"
#include "DoubleSolenoid.h"
#include "launcher.h"

class robot : public SimpleRobot
{
	public:
		robot();//constructor
		~robot();//destructor
		void Autonomous();
		void OperatorControl();
		void dashSend();
	private:		
		//CONTROL
		Joystick* driver;
		Joystick* pultControl;
		Drive* tank;
		
		//PNEUMATICS
		Compressor* comp; //short for compressor
		launcher* pult; //short for catapult
};

#endif

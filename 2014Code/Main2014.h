#ifndef MAIN2014_H
#define MAIN2014_H
#include "WPILib.h"
#include "drive.h"
#include "DoublePiston.h"

class robot : public SimpleRobot
{
	public:
		robot();//constructor
		~robot();//destructor
		void Autonomous();
		void OperatorControl();
	private:		
		//CONTROL
		Joystick* xbox;
		Drive* tank;
		
		//PNEUMATICS
		Compressor* comp; //short for compressor
		DoublePiston* launcher;
};

#endif

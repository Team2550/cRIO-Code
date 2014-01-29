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
		//point to WPILib classes
		Joystick* xbox;
		Drive* tank;
		DoublePiston* launcher;
};

#endif

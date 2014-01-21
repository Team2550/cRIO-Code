#ifndef MAIN2014_H
#define MAIN2014_H
#include "WPILib.h"
#include "drive.h"

class robot : public SimpleRobot
{
	public:
		robot();//constructor
		~robot();//destructor
		void Autonomous();
		void OperatorControl();
	private:
		Drive* tank;
		Joystick* xbox;
};

#endif

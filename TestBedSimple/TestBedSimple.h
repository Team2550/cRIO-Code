#ifndef MYROBOT_H
#define MYROBOT_H
#include <WPILib.h>
#include "drive.h"
#include <NetworkTables/NetworkTable.h>

class TestBed : public SimpleRobot
{
	public:
		TestBed(void);
		~TestBed(void);	
		void Autonomous(void);
		void OperatorControl(void);
	private:
		drive *DriveSys;
};

#endif

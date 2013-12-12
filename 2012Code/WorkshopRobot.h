#ifndef WORKSHOPROBOT_H
#define WORKSHOPROBOT_H


#include "WPILib.h"
#include "DriveSystem.h"
//#include "Deployer.h"
#include "DriverstationUpdater.h"
//#include "Launcher.h"
#include "arm.h"
#include "Pickuper.h"
#include "lights.h"
//#include "accell.h"
//#include "Accelerometer.h"
//#include "Cannon.h"
class WorkshopRobot : public SimpleRobot
{


public:
	WorkshopRobot(void);

	void Autonomous(void);
	
	void OperatorControl(void);
	~WorkshopRobot();

private:
	DriveSystem *driveSys;
	//Launcher *launcher;
	Pickuper *nathansArm;
	Arm *ramparm;
	Lights *light;
	//Deployer * DeployMech;
	//DriverstationUpdater *DriverStationUpdater2;
	//Cannon *AllCannonRun;
	//Accell *myaccell;
};

#endif 

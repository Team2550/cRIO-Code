#include "WorkshopRobot.h"


WorkshopRobot::WorkshopRobot()	
{
	//GetWatchdog().SetExpiration(0.1);
	GetWatchdog().SetEnabled(true);
	driveSys = new DriveSystem();
	//launcher = new Launcher();
	nathansArm = new Pickuper();
	ramparm = new Arm();
	//light = new Lights();
	//myaccell7 = new Accell();
	//DriverStationUpdater2 = new DriverstationUpdater();
	
}
WorkshopRobot::~WorkshopRobot()
{
	//delete DriverStationUpdater2;
	delete driveSys;
	delete ramparm;
	//delete launcher;
	delete nathansArm;
	//delete light;
}
	
void WorkshopRobot::Autonomous(void)
{
	GetWatchdog().SetEnabled(false);
	ramparm->RunAutoArm();
}

void WorkshopRobot::OperatorControl(void)
{
	printf("2250 start\n");
	GetWatchdog().SetEnabled(true);
	printf("Watchdog Enabled!\n");
	while (IsOperatorControl())
	{
		GetWatchdog().Feed();
		//printf("Feed!\n");
		driveSys->RunDrive();
		//printf("RunDrive Done\n");
		//driveSys->DriveMech();
		nathansArm->RunPickuper();
		//ramparm->RunArm();
		//light->FlashLights();
		//launcher->RunLauncher();
		//DriverStationUpdater2->RunDriverstationUpdater();
		
		Wait(0.005);				// wait for a motor update time
	}	
}

START_ROBOT_CLASS(WorkshopRobot);

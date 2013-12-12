#include "WorkshopRobot.h"

WorkshopRobot::WorkshopRobot(){					//Initialize all the other objects we created in the other files.
	GetWatchdog().SetEnabled(false);
	driveSys = new DriveSystem();
	LauncherMech = new Launcher(); 
}
WorkshopRobot::~WorkshopRobot(){				//Remove objects from ram when the robot shuts down.
	delete driveSys;
	delete LauncherMech;
}
	
void WorkshopRobot::Autonomous(void){			//Called once at the begginning of auto mode.
	bool Stopper = false;						//Should not start stopped.
	printf("2250 auto start\n");				//Check in with the console.
	while (IsAutonomous()){						//Main operating loop.
/*		if(Stopper || driveSys->RunDriveSystem()){	//If the drive has ever returned true, then the launcher code should be deployed.
			printf("Deployed/n"); 				//Check with the console.
			LauncherMech->AutoLauncher();
			Stopper = true;						//This will keep the condition true if it ever becomes true.
		}*/
		Wait(0.005); 							//Minimum motor controller wait time. (also handy for ticks)
	}
}
void WorkshopRobot::OperatorControl(void){
	printf("2250 start\n"); 					//Check in with the console.
	while (IsOperatorControl()){ 				//Called once at the beggining of the teleop mode.
		//printf("Feed!\n");
		driveSys->RunDriveSystem();
		LauncherMech->RunLauncher();
		Wait(0.005); 							//Minimum motor controller wait time. (also handy for ticks)
	}
}

START_ROBOT_CLASS(WorkshopRobot); 				//Tells the first software to use this class to create the main() object for the code.

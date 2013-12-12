#ifndef WORKSHOPROBOT_H
#define WORKSHOPROBOT_H
												// For whatever reason, things don't work properly if these are not both defined as the are.

#include "WPILib.h"
#include "DriveSystem.h"
#include "Launcher.h"

												//Define the class that the .cpp will use. This can be done in the .cpp, but it is much cleaner to initialize here,
												//And have the methods in the .cpp
class WorkshopRobot : public SimpleRobot {
	public:										//Anything inside the public class can be used by whatever scope created it.
		WorkshopRobot(void);
		void Autonomous(void);
		void OperatorControl(void);
		~WorkshopRobot();
		
	private:									//Anything inside the prive class is only availible to the .h and .cpp
		Launcher *LauncherMech;					//These are pointers, by declairing the pointers here, but initializing them in the .cpp, we can effectivly make global variables.
		DriveSystem *driveSys;
};

#endif											//This has something to do with the ifndef at the top, however I have never investigated further.

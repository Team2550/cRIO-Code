#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include "WPILib.h"

class DriveSystem {
	public:
		DriveSystem();
		~DriveSystem();
		void RunDriveSystem();
		bool AutoDrive();
	private:
		Joystick *LeftJoystick;
		Joystick *RightJoystick;
		Victor *motor1;
		Victor *motor2;
		Victor *motor3;
		Victor *motor4;
		float slower;
		int accumdir;
};


#endif


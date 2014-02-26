#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "WPILib.h"
#include "xBox.h"
#include "DoublePiston.h"

class launcher
{
	private:
		//Joystick* stick;
		DoublePiston* pistons;
		DoubleSolenoid* trigger;
		Joystick* ctrlStick;
		Joystick* confirmStick;
		bool launchStatus;
		bool triggerStatus;
	public:
		launcher(const int ctrlPort, const int confirmPort);
		~launcher();
		void load();
		void autoLaunch();
		void remoteLaunch();
		bool getLaunchStatus();
		bool getTriggerStatus();
};

#endif

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "WPILib.h"
#include "xBox.h"
#include "DoublePiston.h"

class Launcher
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
		Launcher(const int ctrlPort, const int confirmPort);
		~Launcher();
		void load();
		void autoLaunch();
		void remoteLaunch();
		bool getLaunchStatus();
		bool getTriggerStatus();
};

#endif

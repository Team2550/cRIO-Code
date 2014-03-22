#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "WPILib.h"
#include "xBox.hh"
#include "DoublePiston.hh"

enum LaunchState
{
	launch,
	load,
	triggerBack,
	triggerFwd
};

class Launcher
{
	private:
		//Joystick* stick;
		DoublePiston* pistons;
		DoubleSolenoid* trigger;
		bool launchStatus;
		bool triggerStatus;
	public:
		Launcher();
		~Launcher();
		void setState(LaunchState state);
		bool getLaunchStatus();
		bool getTriggerStatus();
};

#endif

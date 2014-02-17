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
		Joystick* stick;
		bool launchStatus;
		bool triggerStatus;
	public:
		launcher(const int stickPort);
		~launcher();
		void set();
		void off();
		bool getLaunchStatus();
		bool getTriggerStatus();
};

#endif

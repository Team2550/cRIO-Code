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
	public:
		launcher(const int stickPort);
		~launcher();
		void autoLaunch();
		void remoteLaunch();
		void off();
		std::string getStatus();
};

#endif

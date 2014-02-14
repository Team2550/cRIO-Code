#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "WPILib.h"
#include "xBox.h"
#include "DoubleSolenoid.h"
#include "DoublePiston.h"

class launcher
{
	private:
		DoublePiston* pistons;
		DoubleSolenoid* trigger;
	public:
		launcher();
		~launcher();
		void set(Joystick* stick);
		void off();
		std::string getStatus();
};

#endif

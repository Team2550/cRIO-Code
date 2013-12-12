#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "WPILib.h"

class Launcher{
public:
	Launcher();
	~Launcher();
	void RunLauncher();
	void AutoLauncher();
private:
	Joystick *Joystick1;
	Victor *Motor3;
	int trig;
	int acum3;
};


#endif

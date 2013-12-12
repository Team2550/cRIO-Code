#ifndef HAVE_ARM_H
#define HAVE_ARM_H

#include "WPILib.h"

class Arm {
public:
	Arm();
	~Arm();
	
	void RunArm();
	void RunAutoArm();
private:
	Victor *Main;
	Joystick *RightJoystick;
	Joystick *LeftJoystick;
	float speed;
};

#endif

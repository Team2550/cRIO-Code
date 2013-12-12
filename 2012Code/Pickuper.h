#ifndef HAVE_PICKUPER_H
#define HAVE_PICKUPER_H

#include "WPILib.h"

class Pickuper {
public:
	Pickuper();
	~Pickuper();
	
	void RunPickuper();
	Victor *motor71;
	Joystick *RightJoystick;
	Joystick *LeftJoystick;
	float speed;
	bool LegacyButton;
	bool Button;
	int Timer;
	bool Direction;
	bool Togglefucker;
	bool StartCheck;
};

#endif

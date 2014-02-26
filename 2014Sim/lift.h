#ifndef LIFT_H
#define LIFT_H

#include "WPILib.h"
#include "math.h"
#include "xBox.h"

class lift
{
	private:
		Joystick* stick;
		Victor* a;
		Victor* b;
	public:
		lift(const int stickPort);
		~lift();
		void autoRun(float speed);
		void run();
};

#endif

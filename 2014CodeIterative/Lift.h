#ifndef LIFT_H
#define LIFT_H

#include "WPILib.h"
#include "math.h"
#include "xBox.h"

class Lift
{
	private:
		Joystick* stick;
		Victor* a;
		Victor* b;
	public:
		Lift(const int stickPort);
		~Lift();
		void autoRun(float speed);
		void run();
};

#endif

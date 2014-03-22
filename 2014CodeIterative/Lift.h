#ifndef LIFT_H
#define LIFT_H

#include "WPILib.h"
#include "math.h"
#include "xBox.h"

class Lift
{
	private:
		Victor* a;
		Victor* b;
	public:
		Lift();
		~Lift();
		void autoRun(float speed);
		void run(float stickStatus);
};

#endif

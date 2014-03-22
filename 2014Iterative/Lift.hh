#ifndef LIFT_H
#define LIFT_H

#include <math.h>
#include "WPILib.h"
#include "xBox.hh"

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

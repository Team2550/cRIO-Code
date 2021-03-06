#include "Lift.h"

Lift::Lift(const int stickPort)
{
	stick = new Joystick(stickPort);
	a = new Victor(3);
	b = new Victor(4);
}

Lift::~Lift()
{
	delete stick;
	delete a;
	delete b;
}

/*
 * FUNCTION: autoRun
 * DESCRIPTION: run Lift at set speed
 * PARAMETERS:
 * 	speed - the speed at which to run the motors, positive pulls up, keep value between -1 and 1
 */
void Lift::autoRun(float speed)
{
		a->Set(-speed);
		b->Set(speed / 2);
}

void Lift::run()
{
	float stickStatus = stick->GetRawAxis(xbox::axis::leftY);
	if (fabs(stickStatus) > .2)
	{
		a->Set(stickStatus);
		b->Set(-stickStatus / 2);
	}
	else
	{
		a->Set(0);
		b->Set(0);
	}
}

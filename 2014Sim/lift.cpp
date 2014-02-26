#include "lift.h"

lift::lift(const int stickPort)
{
	stick = new Joystick(stickPort);
	a = new Victor(3);
	b = new Victor(4);
}

lift::~lift()
{
	delete stick;
	delete a;
	delete b;
}

/*
 * FUNCTION: autoRun
 * DESCRIPTION: run lift at set speed
 * PARAMETERS:
 * 	speed - the speed at which to run the motors, positive pulls up, keep value between -1 and 1
 */
void lift::autoRun(float speed)
{
		a->Set(-speed);
		b->Set(speed / 2);
}

void lift::run()
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

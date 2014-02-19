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

void lift::run()
{
	float stickStatus = stick->GetRawAxis(xbox::axis::leftY);
	if (fabs(stickStatus) > .2)
	{
		a->Set(stickStatus);
		b->Set(-stickStatus);
	}
	else
	{
		a->Set(0);
		b->Set(0);
	}
}

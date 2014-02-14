#include "DoublePiston.h"

DoublePiston::DoublePiston(const int port1, const int port2,
		const int port3, const int port4)
{
	a = new DoubleSolenoid(port1, port2);
	b = new DoubleSolenoid(port3, port4);
}

DoublePiston::~DoublePiston()
{
	delete a;
	delete b;
}

void DoublePiston::push()
{
	a->Set(DoubleSolenoid::kForward);
	b->Set(DoubleSolenoid::kForward);
	status = "PUSH";
}

void DoublePiston::pull()
{
	a->Set(DoubleSolenoid::kReverse);
	b->Set(DoubleSolenoid::kReverse);
	status = "PULL";
}

void DoublePiston::off()
{
	a->Set(DoubleSolenoid::kOff);
	b->Set(DoubleSolenoid::kOff);
	status = "VENT";
}

std::string DoublePiston::getStatus()
{
	return status;
}

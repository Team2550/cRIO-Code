#include "launcher.h"

launcher::launcher()
{
	pistons = new DoublePiston(1,2,3,4);
	trigger = new DoubleSolenoid(5,6);
}

launcher::~launcher()
{
	delete pistons;
	delete trigger;
}

void launcher::set(Joystick* stick)
{
	//launch catapult
	if (stick->GetRawButton(xbox::btn::rb))
	{
		trigger->Set(DoubleSolenoid::kForward);
		Wait(.05);
		pistons->pull();
	}
	//reprime catapult
	if (stick->GetRawButton(xbox::btn::lb))
		pistons->push();
	//vent catapult
	if (stick->GetRawButton(xbox::btn::a))
		pistons->off();
	if (stick->GetRawButton(xbox::btn::x))
		trigger->Set(DoubleSolenoid::kReverse);
	delete stick;
}

void launcher::off()
{
	pistons->off();
}

std::string launcher::getStatus()
{
	return pistons->getStatus();
}

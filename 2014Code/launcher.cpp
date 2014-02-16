#include "launcher.h"

launcher::launcher(const int stickPort)
{
	pistons = new DoublePiston(1,2,3,4);
	trigger = new DoubleSolenoid(5,6);
	stick = new Joystick(stickPort);
	
	trigger->Set(DoubleSolenoid::kForward);
}

launcher::~launcher()
{
	delete stick;
	delete pistons;
	delete trigger;
}

void launcher::set()
{
	//prime catapult
	if (stick->GetRawButton(xbox::btn::rb))
	{
		trigger->Set(DoubleSolenoid::kReverse);
		Wait(.1);
		pistons->fwd();
		Wait(.5);
		trigger->Set(DoubleSolenoid::kForward);
	}
	//reload catapult
	if (stick->GetRawButton(xbox::btn::lb)) 
		pistons->back();
	/*if (stick->GetRawButton(xbox::btn::y))
		trigger->Set(DoubleSolenoid::kForward);
	//vent catapult
	if (stick->GetRawButton(xbox::btn::a))
		off();
	if (stick->GetRawButton(xbox::btn::x))
		trigger->Set(DoubleSolenoid::kReverse);*/
}

void launcher::off()
{
	pistons->back();
	Wait(.05);
	pistons->off();
}

std::string launcher::getStatus()
{
	return pistons->getStatus();
}

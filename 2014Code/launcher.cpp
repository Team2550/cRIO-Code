#include "launcher.h"

launcher::launcher(const int stickPort)
{
	pistons = new DoublePiston(1,2,3,4);
	trigger = new DoubleSolenoid(5,6);
	stick = new Joystick(stickPort);
	trigger->Set(DoubleSolenoid::kForward);
	triggerStatus = true;
	launchStatus = false;
}

launcher::~launcher()
{
	delete stick;
	delete pistons;
	delete trigger;
} 

void launcher::load()
{
	pistons->back();
	trigger->Set(DoubleSolenoid::kForward);
	launchStatus = true;
	triggerStatus = true;
}

void launcher::autoLaunch()
{
	trigger->Set(DoubleSolenoid::kReverse);
	Wait(.1);
	pistons->fwd();
	Wait(.5);
	trigger->Set(DoubleSolenoid::kForward);
	launchStatus = false;
	triggerStatus = true;
}

void launcher::remoteLaunch()
{
	//prime catapult
	if (stick->GetRawButton(xbox::btn::rb))
		autoLaunch();
	//reload catapult
	if (stick->GetRawButton(xbox::btn::lb)) 
		load();
	//operate trigger
	if (stick->GetRawButton(xbox::btn::y))
	{
		trigger->Set(DoubleSolenoid::kForward);
		triggerStatus = true;
	}
	if (stick->GetRawButton(xbox::btn::x))
	{
		trigger->Set(DoubleSolenoid::kReverse);
		triggerStatus = false;
	}
}

void launcher::off()
{
	pistons->back();
	Wait(.05);
	pistons->off();
}

bool launcher::getLaunchStatus()
{
	return launchStatus;
}

bool launcher::getTriggerStatus()
{
	return triggerStatus;
}

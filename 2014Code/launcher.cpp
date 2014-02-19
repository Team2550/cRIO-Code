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

void launcher::autoLaunch()
{
	trigger->Set(DoubleSolenoid::kReverse);
	Wait(.1);
	pistons->fwd();
	Wait(.5);
	trigger->Set(DoubleSolenoid::kForward);
}

void launcher::remoteLaunch()
{
	//prime catapult
	if (stick->GetRawButton(xbox::btn::rb))
	{
		trigger->Set(DoubleSolenoid::kReverse);
		Wait(.1);
		pistons->fwd();
		Wait(.5);
		trigger->Set(DoubleSolenoid::kForward);
		launchStatus = false;
		triggerStatus = true;
	}
	//reload catapult
	if (stick->GetRawButton(xbox::btn::lb)) 
	{
		pistons->back();
		trigger->Set(DoubleSolenoid::kForward);
		launchStatus = true;
		triggerStatus = true;
	}
	//operate trigger
	if (stick->GetRawButton(xbox::btn::y))
	{
		trigger->Set(DoubleSolenoid::kForward);
		triggerStatus = true;
	}
	if (stick->GetRawButton(xbox::btn::y))
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

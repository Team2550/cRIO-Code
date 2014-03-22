#include "Launcher.hh"

Launcher::Launcher()
{
	pistons = new DoublePiston(1,2,3,4);
	trigger = new DoubleSolenoid(5,6);

	triggerStatus = true;
	launchStatus = false; 
}

Launcher::~Launcher()
{
	delete pistons;
	delete trigger;
} 

/*
 * FUNCTION: remoteLaunch
 * DESCRIPTION: gets joystick input and preforms actions based upon that.
 * 	In order to launch, the Driver must confirm by pressing and holding B while the
 * 	launch controller presses RB
 */
void Launcher::setState(LaunchState state)
{
	//launch
	switch(state)
	{
		case launch:
			trigger->Set(DoubleSolenoid::kReverse);
			Wait(.1);
			pistons->fwd();
			Wait(1);
			trigger->Set(DoubleSolenoid::kForward);
			launchStatus = false;
			triggerStatus = true;
			break;
		case load:
			trigger->Set(DoubleSolenoid::kForward);
			pistons->back();
			launchStatus = true;
			triggerStatus = true;
			break;
		case triggerBack:
			trigger->Set(DoubleSolenoid::kForward);
			triggerStatus = true;
			break;
		case triggerFwd:
			trigger->Set(DoubleSolenoid::kReverse);
			triggerStatus = false;
			break;
	}
}

bool Launcher::getLaunchStatus()
{
	return launchStatus;
}

bool Launcher::getTriggerStatus()
{
	return triggerStatus;
}

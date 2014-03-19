#include "Launcher.h"

Launcher::Launcher(const int ctrlPort, const int confirmPort)
{
	pistons = new DoublePiston(1,2,3,4);
	trigger = new DoubleSolenoid(5,6);
	
	ctrlStick = new Joystick(ctrlPort);
	confirmStick = new Joystick(confirmPort);
	
	trigger->Set(DoubleSolenoid::kForward);//kForward pulls back
	triggerStatus = true;
	launchStatus = false; 
}

Launcher::~Launcher()
{
	delete ctrlStick;
	delete confirmStick;
	delete pistons;
	delete trigger;
} 

/*
 * FUNCTION: load
 * DESCRIPTION: put the catapult in a loadable position (pull it back).
 * 	Make sure trigger is released
 */
void Launcher::load()
{
	trigger->Set(DoubleSolenoid::kForward);
	pistons->back();
	launchStatus = true;
	triggerStatus = true;
}

/*
 * FUNCTION: autoLaunch
 * DESCRIPTION: run launch sequence for catapult
 * 	Push trigger to lock
 * 	Apply pressure to pistons for launch
 * 	Release trigger
 */
void Launcher::autoLaunch()
{
	trigger->Set(DoubleSolenoid::kReverse);
	Wait(.1);
	pistons->fwd();
	Wait(1);
	trigger->Set(DoubleSolenoid::kForward);
	launchStatus = false;
	triggerStatus = true;
}

/*
 * FUNCTION: remoteLaunch
 * DESCRIPTION: gets joystick input and preforms actions based upon that.
 * 	In order to launch, the Driver must confirm by pressing and holding B while the
 * 	launch controller presses RB
 */
void Launcher::remoteLaunch()
{
	//launch
	if (ctrlStick->GetRawButton(xbox::btn::rb) && confirmStick->GetRawButton(xbox::btn::b))
		autoLaunch();
	//reload
	if (ctrlStick->GetRawButton(xbox::btn::lb)) 
		load();
	//operate trigger
	if (ctrlStick->GetRawButton(xbox::btn::y))
	{
		trigger->Set(DoubleSolenoid::kForward);
		triggerStatus = true;
	}
	if (ctrlStick->GetRawButton(xbox::btn::x))
	{
		trigger->Set(DoubleSolenoid::kReverse);
		triggerStatus = false;
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

#include "JoyTest.h"

JoyTest::JoyTest()
{
	GetWatchdog().SetEnabled(false);
	xBox = new Joystick(1);
}

JoyTest::~JoyTest()
{
	delete xBox;
}

void JoyTest::OperatorControl()
{
	while (IsOperatorControl())
	{
		SmartDashboard::PutNumber("A1: ", xBox -> GetRawAxis(1));
		SmartDashboard::PutNumber("A2: ", xBox -> GetRawAxis(2));
		SmartDashboard::PutNumber("A3: ", xBox -> GetRawAxis(3));
		SmartDashboard::PutNumber("A4: ", xBox -> GetRawAxis(4));
		SmartDashboard::PutNumber("A5: ", xBox -> GetRawAxis(5));
	}
}

START_ROBOT_CLASS(JoyTest);


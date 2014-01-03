#include "JoyTest.h"

JoyTest::JoyTest()
{
	GetWatchdog().SetEnabled(false);
	stick = new Joystick(1);
}

JoyTest::~JoyTest()
{
	delete stick;
}

void JoyTest::OperatorControl()
{
	while (IsOperatorControl())
	{
		SmartDashboard::PutNumber("A1: ", stick -> GetRawAxis(1));
		SmartDashboard::PutNumber("A2: ", stick -> GetRawAxis(2));
		SmartDashboard::PutNumber("A3: ", stick -> GetRawAxis(3));
		SmartDashboard::PutNumber("A4: ", stick -> GetRawAxis(4));
		SmartDashboard::PutNumber("A5: ", stick -> GetRawAxis(5));
		SmartDashboard::PutNumber("A6: ", stick -> GetRawAxis(6));
		
		SmartDashboard::PutBoolean("B 1 : ", stick -> GetRawButton(1));
		SmartDashboard::PutBoolean("B 2 : ", stick -> GetRawButton(2));
		SmartDashboard::PutBoolean("B 3 : ", stick -> GetRawButton(3));
		SmartDashboard::PutBoolean("B 4 : ", stick -> GetRawButton(4));
		SmartDashboard::PutBoolean("B 5 : ", stick -> GetRawButton(5));
		SmartDashboard::PutBoolean("B 6 : ", stick -> GetRawButton(6));
		SmartDashboard::PutBoolean("B 7 : ", stick -> GetRawButton(7));
		SmartDashboard::PutBoolean("B 8 : ", stick -> GetRawButton(8));
		SmartDashboard::PutBoolean("B 9 : ", stick -> GetRawButton(9));
		SmartDashboard::PutBoolean("B 10 : ", stick -> GetRawButton(10));
		SmartDashboard::PutBoolean("B 11 : ", stick -> GetRawButton(11));
		SmartDashboard::PutBoolean("B 12 : ", stick -> GetRawButton(12));
	}
}

START_ROBOT_CLASS(JoyTest);


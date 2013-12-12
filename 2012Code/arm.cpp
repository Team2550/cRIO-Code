#include "arm.h"
Arm::Arm()
{
	//Initialising code goes here.
	Main=new Victor(5);
	LeftJoystick = new Joystick(1);
	RightJoystick = new Joystick(2);
	float speed = 0;
}
Arm::~Arm()
{
	Main->Set(0);
	delete Main;
	delete RightJoystick;
	delete LeftJoystick;
}
void Arm::RunArm()
{
	//float speed = 0;
	if(speed==0){
		Main->Set(0.75);
		speed=1;
	}
	//printf("Arm Speed %f\n",speed);
}
void Arm::RunAutoArm()
{
	Main->Set(1);
}
//#endif

#include "Pickuper.h"
Pickuper::Pickuper() {
	//Initialising code goes here.
	motor71=new Victor(6);
	LeftJoystick = new Joystick(1);
	RightJoystick = new Joystick(2);
	float speed=0;
	bool Button=false;
	bool LegacyButton=false;
	int Timer=2;
	bool Direction=false;
	bool Togglefucker=false;
}
Pickuper::~Pickuper() {
	delete motor71;
	delete RightJoystick;
	delete LeftJoystick;
	// De initialising code goes here.	
}
void Pickuper::RunPickuper() {
	speed = 0;
	/*
	 if(RightJoystick->GetRawButton(3)==true){
	 if(LegacyButton==false){
	 Button=true;
	 LegacyButton=true;
	 Direction=1;
	 }
	 }
	 if(RightJoystick->GetRawButton(2)==true){
	 if(LegacyButton==false){
	 Button=true;
	 LegacyButton=true;
	 Direction=-1;
	 }
	 }
	 if(Button==true){
	 for(int I=0; I<3; I++){
	 speed=1*(Direction);
	 Togglefucker=!Togglefucker;
	 }
	 Button=false;
	 }
	 if(Button==false && LegacyButton==true && RightJoystick->GetRawButton(3)==false){
	 LegacyButton=false;
	 }
	 */
	if (RightJoystick->GetRawButton(2)) {
		speed = .2;
	}
	if (RightJoystick->GetRawButton(5)) {
		speed = .3;
	}
	if (LeftJoystick->GetRawButton(2)) {
		speed = .2;
	}
	if (RightJoystick->GetRawButton(5)) {
		speed = .3;
	}

	if (RightJoystick->GetRawButton(3)) {
		speed = -.2;
	}
	if (RightJoystick->GetRawButton(4)) {
		speed = -.3;
	}
	if (LeftJoystick->GetRawButton(3)) {
		speed = -.2;
	}
	if (LeftJoystick->GetRawButton(4)) {
		speed = -.3;
	}
	motor71->Set(speed);
}
//#endif

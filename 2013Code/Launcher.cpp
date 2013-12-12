#include "Launcher.h"

Launcher::Launcher(){	
	Joystick1 = new Joystick(1);
	Motor3 = new Victor(3);
	trig = 0;
	acum3 = 0;
}

Launcher::~Launcher(){
	delete Joystick1;
	delete Motor3;
}

void Launcher::RunLauncher(){
	int ButtonA=Joystick1->GetRawButton(1);
	if(ButtonA){
		Motor3->Set(0.5);
	}
	else{
		Motor3->Set(0);
	}
}
void Launcher::AutoLauncher(){
	if(acum3<150){
		Motor3->Set(-0.8);
		acum3++;
	}
	else{
		Motor3->Set(0);
	}
}

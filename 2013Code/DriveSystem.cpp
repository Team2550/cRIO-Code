#include "DriveSystem.h"
#include "Ultrasoniclistener.h"
#include "math.h"
#include <complex> // Complex is the same as including the math.h header, however it can deal with complex floating point math.
#include "WPILib.h"

int superacum = 0;

DriveSystem::DriveSystem(){ //Initialize all global variables into ram when DriveSystem object is created.	
	LeftJoystick = new Joystick(2);
	RightJoystick = new Joystick(1);
	
	motor1= new Victor(1);
	motor2= new Victor(2);
//	float slower = 0;
//	bool accumdir = false;
}

DriveSystem::~DriveSystem(){ //Delete variables and objects from r+am when Drivesystem object is deleted.
	delete motor1;
	delete motor2;
	delete LeftJoystick;
	delete RightJoystick;
}
/* I am keeping this because im really proud of it. Plus...it "could" be useful at some point.
double CLAMP( double value, double low, double high){
	return value < low ? low : (value > high ? high : value);
}
*/
void DriveSystem::RunDriveSystem(){

	// The idea behind this whole getup is that motor controllers accept a value from 1-0, so that we get up to 0.7 from the joysticks and add the last 0.3 using the boosters.
	// Initialize local variables.
	float RightJoystickY=-RightJoystick->GetRawAxis(2)*0.5;
	float LeftJoystickY=-RightJoystick->GetRawAxis(5)*0.5;
	float BoosterDir = -RightJoystick->GetThrottle();
	float Booster = 0;
	//Boosting logic. These values seem about right. Might want to multiply them by the throttle value for testing. (Make sure to output throttle value in the print statement below to avoid spam)
	if(BoosterDir>0){
		Booster = 2.0;
	}
	else if(BoosterDir<0){
		Booster = 1.5;
	}
	else{
		Booster = 1;
	}
	RightJoystickY*=Booster;//RightJoystickY = RightJoystickY * Booster
	LeftJoystickY*=Booster;
	// Initialize the global print timer. This slows down the speed of prints by 75% to prevent lag due to console spam.
	slower++;
	if(slower>75){
		slower = 0;
		//printf("RightJoystick: %f ||| LeftJoystick: %f \n", RightJoystickY, LeftJoystickY);
		//printf("%d ||| %d ||| %d ||| %d \n", input1->Get(), input2->Get(), input3->Get(), input4->Get());
		//printf("Distance: %f\n", ultrasensor->Listen());
		printf("Speed: %f\n", (RightJoystickY+LeftJoystickY)/2);
	}
	//Basic Motor controlling statements.
	if(abs(RightJoystickY)>0.1){
		motor1->Set(RightJoystickY);
	}
	else{
		//lock motors
		motor1->Set(0);
	}
	if(abs(LeftJoystickY)>0.1){
		motor2->Set(LeftJoystickY);
	}
	else{
		//lock motors]
		motor2->Set(0);
	}
}
bool DriveSystem::AutoDrive(){ //Autodrive system called by the auto mode.  This method will return true when the drive is compleated.
	float DriveSpeed = 0;
	bool Tripper = false;
	if(superacum<1600){ //2200(200in)
		superacum++;
		DriveSpeed = 0.26*2.0;
	}
	else{
		Tripper = true;
		superacum = 0;
		DriveSpeed = 0;
	}
	slower++;
	if(slower>75){
		slower = 0;
	}
	motor1->Set(DriveSpeed);
	motor2->Set(DriveSpeed);
	return Tripper;
}


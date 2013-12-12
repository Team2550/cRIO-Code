#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include "WPILib.h"

class DriveSystem
{
public:
	DriveSystem();
	void RunDrive();
	void DriveMech();
	~DriveSystem();
	void Rotate();
	void Strafe();
	void DriveAuto();
	void ForwardBackward();
	void TurnLeft();
	void TurnRight();
private:
	Joystick *LeftJoystick;
	Joystick *RightJoystick;
	Victor *motor1;
	Victor *motor2;
	Victor *motor3;
	Victor *motor4;
	float slower;
	float Mode;
	float Counter;
	DigitalOutput *ledBar;
	RobotDrive *rd;
	bool noinput;
	float power;
	float x_move;
	float y_move;
	float x_turn;
	float y_turn;
	float truex;
	float truey;
	
	float motor1a;
	float motor2a;
	float motor3a;
	float motor4a;
	float X1,X2,Y1;
	
	double lastcount;
	Timer *counter;
};


#endif


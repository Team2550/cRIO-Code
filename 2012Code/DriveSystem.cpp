#include "DriveSystem.h"
#include "math.h"
DriveSystem::DriveSystem()
{	//Joysticks are reversed. Flipping will be done here. From here down assume
	//That the joysticks are correct.
	LeftJoystick = new Joystick(2);
	RightJoystick = new Joystick(1);
	
	motor1= new Victor(1);
	motor2= new Victor(2);
	motor3= new Victor(3);
	motor4= new Victor(4);
	
	//float slower =0;
	/*
	float power=.2;
	float x_move =0;
	float y_move =0;
	float x_turn = 0;
	float y_turn = 0;
	float truex = 0;
	float truey = 0;
	float X1=0;
	float Y1=0;
	float X2=0;
	float motor1a = 0;
	float motor2a = 0;
	float motor3a=0;
	float motor4a=0;
	//rd = new RobotDrive(motor1,motor2,motor3,motor4);
	double lastcount = 0;
	*/
	counter = new Timer();
	counter->Start();
}

DriveSystem::~DriveSystem()
{
	delete motor1;
	delete motor2;
	delete motor3;
	delete motor4;
	delete RightJoystick;
	delete LeftJoystick;
	//delete rd;
	
}
void DriveSystem::DriveAuto(){
	//nothing doing
}
double CLAMP( double value, double low, double high){
	return value < low ? low : (value > high ? high : value);
}
void DriveSystem::RunDrive(){
	double lf;
	double rf;
	double lb;
	double rb;
	double rotmult = 0.2;
	double movemult = 1;
	double y = RightJoystick->GetY();
	double x = RightJoystick->GetX();
	x=-x;
	double magnitude = sqrt(y*y+x*x);
	magnitude = magnitude * sqrt(2);
	double rotation = LeftJoystick->GetX();
	double direction = atan2(x,y);
	double dirinrad = direction+45;
	double sinD = sin(dirinrad);
	double cosD= cos(dirinrad)*sqrt(2);
	if(fabs(rotation)>0.2){
		rotation*=1.5;
	}
	else{
		rotation = 0;
	}
	if(RightJoystick->GetTrigger()){
		movemult = 1.5;
	}
	if(LeftJoystick->GetTrigger()){
		rotmult = 1.2;
	}
	lf = -1*sinD*(movemult*magnitude)+(rotmult*rotation);
	rf = -1*cosD*(movemult*magnitude)-(rotmult*rotation);
	lb=  -1*cosD*(movemult*magnitude)+(rotmult*rotation);
	rb = -1*sinD*(movemult*magnitude)-(rotmult*rotation);
	if(lf<0){
		lf = lf * 1.2;
	}
	if(rf<0){
		rf = rf * 1.2;
	}
	if(lb<0){
		lb = lb * 1.2;
	}
	if(rb<0){
		rb = rb * 1.2;
	}
	
	motor1->Set(-lf*(RightJoystick->GetThrottle()+1)/2);
	motor2->Set(rf*(RightJoystick->GetThrottle()+1)/2);
	motor3->Set(-lb*(RightJoystick->GetThrottle()+1)/2);
	motor4->Set(rb*(RightJoystick->GetThrottle()+1)/2);
	/*
	X1 = LeftJoystick->GetX();
	Y1 = LeftJoystick->GetY();
	X2 = RightJoystick->GetX();
	//float Y2 = RightJoystick->GetY();
	motor1->Set(1*(Y1-X1+X2));
	motor2->Set(-1*(Y1+X1-X2));
	motor3->Set(1*(Y1+X1+X2));
	motor4->Set(-1*(Y1-X1-X2));
	if(counter->Get()-lastcount>=1){
		lastcount = counter->Get();
		printf("X1: %f \n",X1);
		printf("Y1: %f \n",Y1);
		printf("X2: %f \n",X2);
		
		printf("\n\nmotor1 speed: %f \n",Y1-X1+X2);
		printf("motor2 speed: %f \n",Y1+X1-X2);
		printf("motor3 speed: %f \n",Y1+X1+X2);
		printf("motor4 speed: %f \n\n\n",Y1-X1-X2);
	}
	//else printf("lastcount%f",(float)lastcount);
	*/
}
void DriveSystem::DriveMech(void)
{
	//rd->HolonomicDrive(RightJoystick->GetMagnitude(),RightJoystick->GetDirectionDegrees(),0);
}
void DriveSystem::TurnLeft(void)
{
	motor1->Set(0.5);
	motor2->Set(-0.5);
	motor3->Set(0.5);
	motor4->Set(-0.5);
}
void DriveSystem::TurnRight(void)
{
	motor1->Set(-0.5);
	motor2->Set(0.5);
	motor3->Set(-0.5);
	motor4->Set(0.5);
}
void DriveSystem::Rotate(void)
{
	//maccanum rotate, not enabled.
	motor1->Set(RightJoystick->GetY());
	motor2->Set(LeftJoystick->GetY());
	motor3->Set(LeftJoystick->GetY());
	motor4->Set(RightJoystick->GetY());
};
void DriveSystem::ForwardBackward(void)
{
	//direct motor controle.
	motor1->Set(RightJoystick->GetY());
	motor2->Set(LeftJoystick->GetY());
	motor3->Set(RightJoystick->GetY());
	motor4->Set(LeftJoystick->GetY());
};
void DriveSystem::Strafe(void)
{
	//maccanum strafing, not enabled.
	motor1->Set(((LeftJoystick->GetX()+RightJoystick->GetX())));
	motor2->Set(((LeftJoystick->GetX()+RightJoystick->GetX())));
	motor3->Set(-((LeftJoystick->GetX()+RightJoystick->GetX())));
	motor4->Set(-((LeftJoystick->GetX()+RightJoystick->GetX())));
};

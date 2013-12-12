#include "Ultrasoniclistener.h"
#include "math.h"
#include <complex>
#include "WPILib.h"
//NOTE: THIS WAS MADE FOR THE VEX SENSOR. DUE TO INCONSISTANCY WITH EITHER THE CONNECTION OR THE SENSOR, DATA FROM THE VEX ULTRASONIC SENSOR IS NOT RELYABLE.
//		YOU MAY STILL BE ABLE TO USE STANDARD FRC ULTRASONICS WITH THIS CLASS.
Ultrasoniclistener::Ultrasoniclistener(){	
	sensor1 = new Ultrasonic (new DigitalOutput (5), new DigitalInput(6), Ultrasonic::kInches);
	sensor1->SetAutomaticMode (true);		//Tells the sensor to emit a constant "ping".
}

Ultrasoniclistener::~Ultrasoniclistener(){
	delete sensor1;
}
double CLAMP( double value, double low, double high){
	return value < low ? low : (value > high ? high : value); //Confusing statement that compleates a basic clamp operation. This is basicly compressed logic. Try to avoid writing code like this.
}
double Ultrasoniclistener::Listen(){ //Basic attempt at normalizing the sensor data.  Returns -1 for out of max relyable range data.
	double MaxDistance = 35;
	double Distance = 0;
	//sensor1->Ping();
	if(sensor1->IsRangeValid ()){
		if(Distance>MaxDistance){
			Distance = -1;
		}
		else{
			Distance = CLAMP(sensor1->GetRangeInches(),0,35);
		}
	}
	return Distance;
}

#ifndef ULTRASONICLISTENER_H
#define ULTRASONICLISTENER_H

#include "WPILib.h"

class Ultrasoniclistener {
	public:
		Ultrasoniclistener();
		~Ultrasoniclistener();
		double Listen();
	private:
		Ultrasonic *sensor1;
};


#endif


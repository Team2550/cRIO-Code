#ifndef LIFT_H
#define LIFT_H

#include "WPILib.h"
#include "math.h"
#include "xBox.h"

class lift
{
	private:
		Joystick* stick;
		Victor* a;
		Victor* b;
		std::string status;
	public:
		lift(const int stickPort);
		~lift();
		void run();
		std::string getStatus();
};

#endif

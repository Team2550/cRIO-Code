#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "WPILib.h"

//class for controlling 2 (bidirectional) pneumatic pistons
class DoublePiston
{
	public:
		DoublePiston(const int port1, const int port2,
				const int port3, const int port4);
		~DoublePiston();
		void push();
		void pull();
		void off();
	private:
		DoubleSolenoid* a;
		DoubleSolenoid* b;
};

#endif

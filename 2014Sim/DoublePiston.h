#ifndef D_PISTON_H
#define D_PISTON_H
#include "WPILib.h"

//class for controlling 2 (bidirectional) pneumatic pistons
class DoublePiston
{
	public:
		DoublePiston(const int port1, const int port2,
				const int port3, const int port4);
		~DoublePiston();
		std::string getStatus();
		void off();
		void fwd();
		void back();
	private:
		//DoubleSolenoid* a;
		//DoubleSolenoid* b;
		std::string status;
};

#endif

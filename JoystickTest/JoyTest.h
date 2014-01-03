#include <WPILib.h>
#include <NetworkTables/NetworkTable.h>

class JoyTest : public SimpleRobot
{
	public:
		JoyTest(void);
		~JoyTest(void);
		void OperatorControl();
	private:
		Joystick *stick;
};

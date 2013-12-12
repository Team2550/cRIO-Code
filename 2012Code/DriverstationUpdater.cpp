#include "DriverstationUpdater.h"
//nobody is really sure how this works.
DriverstationUpdater::DriverstationUpdater() {
	
}

DriverstationUpdater::~DriverstationUpdater() {
	
}

void DriverstationUpdater::RunDriverstationUpdater() {
	
	Dashboard &dashHP = DriverStation::GetInstance()->GetHighPriorityDashboardPacker();
		dashHP.AddCluster(); // wire (2 elements)
		{
			dashHP.AddCluster(); // tracking data
			{
				dashHP.AddDouble(1.0); // Joystick X
				dashHP.AddDouble(135.0); // angle
				dashHP.AddDouble(3.0); // angular rate
				dashHP.AddDouble(5.0); // other X
			}
			dashHP.FinalizeCluster();
			dashHP.AddCluster(); // target Info (2 elements)
			{
				dashHP.AddCluster(); // targets
				{
					dashHP.AddDouble(100.0); // target score
					dashHP.AddCluster(); // Circle Description (5 elements)
					{
						dashHP.AddCluster(); // Position (2 elements)
						{
							dashHP.AddDouble(30.0); // X
							dashHP.AddDouble(50.0); // Y
						}
						dashHP.FinalizeCluster();
					}
					dashHP.FinalizeCluster(); // Position
					dashHP.AddDouble(45.0); // Angle
					dashHP.AddDouble(21.0); // Major Radius
					dashHP.AddDouble(15.0); // Minor Radius
					dashHP.AddDouble(324.0); // Raw score
				}
				dashHP.FinalizeCluster(); // targets
			}
			dashHP.FinalizeCluster(); // target Info
		}
		dashHP.FinalizeCluster(); // wire
		dashHP.Finalize();


	Dashboard &dash = DriverStation::GetInstance()->GetLowPriorityDashboardPacker();
		dash.AddCluster();
		{
			dash.AddCluster();
			{ //analog modules 
				dash.AddCluster();
				{
					for (int i = 1; i <= 8; i++) {
						dash.AddFloat((float) AnalogModule::GetInstance(1)->GetAverageVoltage(i));
						//				dash.AddFloat((float) i * 5.0 / 8.0);
					}
				}
				dash.FinalizeCluster();
				dash.AddCluster();
				{
					for (int i = 1; i <= 8; i++) {
						dash.AddFloat((float) AnalogModule::GetInstance(2)->GetAverageVoltage(i));
					}
				}
				dash.FinalizeCluster();
			}
			dash.FinalizeCluster();

			dash.AddCluster();
			{ //digital modules
				dash.AddCluster();
				{
					dash.AddCluster();
					{
						dash.AddBoolean(true);
						int module = 4;
						dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward()); // forwards relays
						dash.AddU8(DigitalModule::GetInstance(module)->GetRelayReverse()); //reverse relays
						dash.AddU16((short)DigitalModule::GetInstance(4)->GetDIO()); //digital I/o status
						//dash.AddU16((short) 0xAAAA);
						dash.AddU16((short)DigitalModule::GetInstance(4)->GetDIODirection()); //digital i/o direction
						//dash.AddU16((short) 0x7777);
						dash.AddCluster();
						{
							for (int i = 1; i <= 10; i++) {
							dash.AddU8((unsigned char) DigitalModule::GetInstance(module)->GetPWM(i));  //PWMs
								//dash.AddU8((unsigned char) (i-1) * 255 / 9);
							}
						}
						dash.FinalizeCluster();
					}
					dash.FinalizeCluster();
				}
				dash.FinalizeCluster();

				dash.AddCluster();
				{
					dash.AddCluster();
					{
						int module = 6;
						dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
						dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
						dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIO());
						dash.AddU16(DigitalModule::GetInstance(module)->GetDIODirection());
						dash.AddCluster();
						{
							for (int i = 1; i <= 10; i++) {
								dash.AddU8((unsigned char) DigitalModule::GetInstance(module)->GetPWM(i));
								//				dash.AddU8((unsigned char) i * 255 / 10);
							}
						}
						dash.FinalizeCluster();
					}
					dash.FinalizeCluster();
				}
				dash.FinalizeCluster();
			}
			dash.FinalizeCluster();

			// Can't read solenoids without an instance of the object
			dash.AddU8((char) 0);
		}
		dash.FinalizeCluster();
		dash.Finalize();
	
}

#include "main.h"

void InitialiseDrive()
	{
		DriveLB=80;
		DriveRB=80;
		DriveLF=-40;
		DriveRF=-40;
	}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task MotorController
{
	while(true)
	{
		motor[LDF] = DriveLF;
		motor[LDB] = DriveLB;
		motor[RDF] = DriveRF;
		motor[RDB] = DriveRB;
		
		motor[LLU] = LiftLU;
		motor[LLD] = LiftLD;
		motor[RLU] = LiftRU;
		motor[RLD] = LiftRD;
		
		wait1MSec(20);
	}
}

task autonomous()
{
	StartTask(MotorController);
	InitialiseDrive();
}
#include "main.h"

void Drive(int EncoderDistance,int SpeedLDB,int SpeedLDF,int SpeedRDB,int SpeedRDF)
{
	ClearEncoders();
	
	bool DriveLBGoalReached = false;
	bool DriveRBGoalReached = false;
	bool DriveLFGoalReached = false;
	bool DriveRFGoalReached = false;

	//Data validation
	EncoderDistance = abs(EncoderDistance);
	
	//Set Drive to Active
	DriveActive = true;

	while (((DriveLBGoalReached == false)||(DriveRBGoalReached == false)||(DriveRFGoalReached == false)||(DriveLFGoalReached == false)) && (DriveActive == true))
	{
		if ( Encoder(LDB) < EncoderDistance )
		{
		
			DriveLB = SpeedLDB;
		}
		else
		{
			DriveLB = 0;
			DriveLBGoalReached=true;
		}

		if ( Encoder(RDB) < EncoderDistance )
		{
			DriveRB = SpeedRDB;
		}
		else
		{
			DriveRB = 0;
			DriveRBGoalReached=true;
		}

		if ( Encoder(LDF) < EncoderDistance )
		{
			DriveLF = SpeedLDF;
		}
		else
		{
			DriveLF = 0;
			DriveLFGoalReached=true;
		}

		if ( Encoder(RDF) < EncoderDistance )
		{
			DriveRF = SpeedRDF;
		}
		else
		{
			DriveRF = 0;
			DriveRFGoalReached=true;
		}
	}
	
	//Set Drive to inactive
	DriveActive = false;
	
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task MotorController()
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
		
		wait1Msec(20);
	}
}

task autonomous()
{
	//Initialise Autonomous
	StartTask(MotorController);
	StartTask(AntiJam);
	InitialiseDrive();
	
	//Autonomous Routine
	DriveStraightForward(200,127)
}
#include "main.h"

//Autonomous functions
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

	while (((DriveLBGoalReached == false)||(DriveRBGoalReached == false)||(DriveRFGoalReached == false)||(DriveLFGoalReached == false)) && (DriveActive))
	{
		if ( Encoder(LDB) < EncoderDistance )
		{
		
			motor[LDB] = SpeedLDB;
		}
		else
		{
			motor[LDB] = 0;
			DriveLBGoalReached=true;
		}

		if ( Encoder(RDB) < EncoderDistance )
		{
			motor[RDB] = SpeedRDB;
		}
		else
		{
			motor[RDB] = 0;
			DriveRBGoalReached=true;
		}

		if ( Encoder(LDF) < EncoderDistance )
		{
			motor[LDF] = SpeedLDF;
		}
		else
		{
			motor[LDF] = 0;
			DriveLFGoalReached=true;
		}

		if ( Encoder(RDF) < EncoderDistance )
		{
			motor[RDF] = SpeedRDF;
		}
		else
		{
			motor[RDF] = 0;
			DriveRFGoalReached=true;
		}
		
		EndTimeSlice();
	}
	
	//Set Drive to inactive
	DriveActive = false;
	
}

void Lift(int PotLT,int PotRT,int Speed)
{
	PotLTarget = PotLT;
	PotRTarget = PotRT;
	LiftTargetSpeed = Speed;
}

void Intake(int Speed)
{
	motor[LIN] = Speed;
	motor[RIN] = Speed;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	//Initialise Autonomous
/* 	StartTask(LiftController);
	StartTask(AntiJam);
	InitialiseDrive(); */
	
	//Autonomous Routine
	SensorValue[PistonClaw]=1;
	wait1Msec(1000);
}
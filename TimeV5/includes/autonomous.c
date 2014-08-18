#include "main.h"

//Autonomous functions

void drive(int encoderDistance,int driveLBSpeed,int driveLFSpeed,int driveRBSpeed,int driveRFSpeed)
{
	clearPreviousError();
	clearEncoders();
	
	bool driveLBGoalReached = false;
	bool driveRBGoalReached = false;
	bool driveLFGoalReached = false;
	bool driveRFGoalReached = false;

	//Data validation
	driveAutonVal = abs(encoderDistance);
	
	//Set Drive to Active
	driveActive = true;

	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)||(driveRFGoalReached == false)||(driveLFGoalReached == false)) && (driveActive))
	{
		if (encoder(driveLB) < driveAutonVal)
		{
		
			motor[driveLB] = driveLBSpeed;
		}
		else
		{
			motor[driveLB] = 0;
			driveLBGoalReached=true;
		}

		if (encoder(driveRB) < driveAutonVal)
		{
			motor[driveRB] = driveRBSpeed;
		}
		else
		{
			motor[driveRB] = 0;
			driveRBGoalReached=true;
		}

		if (encoder(driveLF) < driveAutonVal)
		{
			motor[driveLF] = driveLFSpeed;
		}
		else
		{
			motor[driveLF] = 0;
			driveLFGoalReached=true;
		}

		if (encoder(driveRF) < driveAutonVal)
		{
			motor[driveRF] = driveRFSpeed;
		}
		else
		{
			motor[driveRF] = 0;
			driveRFGoalReached=true;
		}
	}
	
	//Set Drive to inactive
	driveActive = false;
	
}

void lift(int potLT,int potRT,int speed)
{
	potLTarget = potLT;
	potRTarget = potRT;
	liftTargetSpeed = speed;
}

void intake(int speed)
{
	motor[intakeL] = speed;
	motor[intakeR] = speed;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task motorController() //Assigns motor values from buffer
{
	while(true)
	{
		motor[liftLU] = lL;
		motor[liftLD] = lL;
		motor[liftRU] = lR;
		motor[liftRD] = lR;
		
		wait1Msec(20);
	}
}
	int leftSideUp[6];
	int leftSideDown[6];
task autonomous()
{
	//Initialise Autonomous
	StartTask(motorController);
	StartTask(liftController);
	StartTask(antiJam);
	initialiseDrive();

	// Autonomous Routine
	// Feel free to modify the values
	liftMove(800, 100);
	intakeOut();
	liftMove(0, 100);
	drivePointTurnRight(90, 100);
	driveStraightForward(100, 200);
	intakeIn();
	driveStraightForward(50, 200);
	drivePointTurnLeft(90, 100);
	liftMove(1300, 100);
	intakeOut();
	liftMove(0, 100);
	drivePointTurnRight(90, 100);
}
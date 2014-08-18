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
	
	//Set Drive to Active
	driveActive = true;

	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)||(driveRFGoalReached == false)||(driveLFGoalReached == false)) && (driveActive))
	{
		if (encoder(driveLB) < encoderDistance)
		{
		
			motor[driveLB] = driveLBSpeed;
		}
		else
		{
			motor[driveLB] = 0;
			driveLBGoalReached=true;
		}

		if (encoder(driveRB) < encoderDistance)
		{
			motor[driveRB] = driveRBSpeed;
		}
		else
		{
			motor[driveRB] = 0;
			driveRBGoalReached=true;
		}

		if (encoder(driveLF) < encoderDistance)
		{
			motor[driveLF] = driveLFSpeed;
		}
		else
		{
			motor[driveLF] = 0;
			driveLFGoalReached=true;
		}

		if (encoder(driveRF) < encoderDistance)
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

void liftAutonMonitor()
{
	if ((potLTarget != 0) && (potRTarget != 0))
	{
		liftActive = true;
		
		bool LLGoalReached = false;
		bool RLGoalReached = false;

		string direction;

		if (potR < potRTarget)
		{
			direction = "up";
		}
		if (potR > potRTarget)
		{
			direction = "down";
			potRTarget = potRTarget + 100;
		}

		if ((abs(potR)-30 < abs(potRTarget)) && ((abs(potR)+30 > abs(potRTarget))))
		{
			lL = 0;
			lR = 0;
			potRTarget = 0;
			potLTarget = 0;
		}

		else if ((potRTarget != 0) && (potLTarget != 0) && (liftActive))
		{
			if (direction == "down")
			{
				while ((LLGoalReached == false) || (RLGoalReached == false) && (liftActive) )
				{
					if (potR > potRTarget)
					{
						lL = -(liftTargetSpeed);
					}
					else
					{
						LLGoalReached = true;
						lL = 0;
					}
					if (potR > potRTarget)
					{
						lR = -(liftTargetSpeed);
					}
					else
					{
						RLGoalReached = true;
						lR = 0;
					}
				}



			}

			else if (direction == "up")
			{
				while ((LLGoalReached == false) || (RLGoalReached == false) && (liftActive))
				{
					if (potR < potRTarget)
					{
						lL = (liftTargetSpeed);
					}
					else
					{
						LLGoalReached = true;
						lL = 0;
					}
					if (potR < potRTarget)
					{
						lR = liftTargetSpeed;
					}
					else
					{
						RLGoalReached = true;
						lR = 0;
					}
				}
			}
		}
		
		liftActive = false;
	}
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

task liftController()
{
	
	while(true)
	{
		liftAutonMonitor();
		EndTimeSlice();
	}
}

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
	
task autonomous()
{
	//Initialise Autonomous
	StartTask(liftController);
//	StartTask(antiJam);
	StartTask(motorController);
	initialiseDrive();
	
	//Autonomous Routine
	driveStraightForward(100,50); 
}
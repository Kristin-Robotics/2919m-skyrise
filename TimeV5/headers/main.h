#ifndef MAIN_H_
#define MAIN_H_

#include "definitions.h"

#include "variables.h"

//Global Functions
// changes the speed to the set value in main.h
int reduceSpeed(int speed)
{
	float buffer = (float)speed; // to prevent truncation during multiplication
	return (int)(round(buffer * speedReductionVal)); //Better rounding using the macro
}

void clearEncoders()
{
	encoder(driveLF) = 0;
	encoder(driveRF) = 0;
	encoder(driveLB) = 0;
	encoder(driveRB) = 0;
}

void clearPreviousError()
{
	speedstepPreviousError[0] = 0;
	speedstepPreviousError[1] = 0;
	speedstepPreviousError[2] = 0;
	speedstepPreviousError[3] = 0;
}

void initialiseDrive()
{
	motor[driveLB] = 80;
	motor[driveRB] = 80;
	motor[driveLF] = -40;
	motor[driveRF] = -40;
	wait1Msec(1000);
	motor[driveLB] = 0;
	motor[driveRB] = 0;
	motor[driveLF] = 0;
	motor[driveRF] = 0;
}

//Speedstep for Drive
int speedstepDrive(int speedLimit,int sensorReading,int arrayID) //PID for Autonomous Drive
{
	float Kp = 0.7;
	float Ki = 0.12;
	float Kd = 0.1;
	
	if (speedstepDriveEnabled == true)
	{
		speedstepError = driveAutonVal - sensorReading;
		speedstepIntegral = speedstepIntegral + speedstepError;

		if (speedstepError == 0)
		{
			speedstepIntegral = 0;
		}

		if (abs(speedstepError) > 40)
		{
			speedstepIntegral = 0;
		}

		speedstepDerivitive = speedstepError - speedstepPreviousError[arrayID];
		speedstepPreviousError[arrayID] = speedstepError;
		speedstepSpeed = (int) round(Kp*speedstepError + Ki*speedstepIntegral + Kd*speedstepDerivitive);

		if (speedstepSpeed > speedLimit)
		{
			speedstepSpeed = speedLimit;
		}
		return speedstepSpeed;
	}
	else
		{
			return speedLimit;
		}
}
	
//Speedstep for Lift
int speedstepLift(int speedLimit,int sensorReading,int arrayID) //PID for Autonomous Drive
{
	float Kp = 0.7;
	float Ki = 0.12;
	float Kd = 0.1;
	
	if (speedstepDriveEnabled == true)
	{
		speedstepError = driveAutonVal - sensorReading;
		speedstepIntegral = speedstepIntegral + speedstepError;

		if (speedstepError == 0)
		{
			speedstepIntegral = 0;
		}

		if (abs(speedstepError) > 40)
		{
			speedstepIntegral = 0;
		}

		speedstepDerivitive = speedstepError - speedstepPreviousError[arrayID];
		speedstepPreviousError[arrayID] = speedstepError;
		speedstepSpeed = (int) round(Kp*speedstepError + Ki*speedstepIntegral + Kd*speedstepDerivitive);

		if (speedstepSpeed > speedLimit)
		{
			speedstepSpeed = speedLimit;
		}
		return speedstepSpeed;
	}
	else
		{
			return speedLimit;
		}
}

void liftMonitor()
{
	if (((potR-30 > potRTarget) && (potR+30 < potRTarget)) || (potR == potRTarget))
	{
		lL = 0;
		lR = 0;
		
		potRTarget = 0;
		potLTarget = 0;
	}

	else
	{
		bool liftLGoalReached = false;
		bool liftRGoalReached = false;
		
		int direction; //0 is down, 1 is up
		
		//Set lift to active
		liftActive = true;
		
		while (((liftLGoalReached == false) || (liftRGoalReached == false)) && (liftActive))
		{
			if (potR < potRTarget)
			{
				direction = 1;
			}
			if (potR > potRTarget)
			{
				direction = 0;
			}
			
			if (direction == 1)
			{
				if (potL > potLTarget)
				{
					lL = -liftTargetSpeed;
					lL = -liftTargetSpeed;
				}
				else
				{
					lL = 0;
					lL = 0;
					potLTarget = 0;
					liftLGoalReached = true;
				}
				if (potR > potRTarget)
				{
					lR = -liftTargetSpeed;
					lR = -liftTargetSpeed;
				}
				else
				{
					lR = 0;
					lR = 0;
					potRTarget = 0;
					liftRGoalReached = true;
				}
			}
			
			if (direction == 1)
			{
				if (potL > potLTarget)
				{
					lL = liftTargetSpeed;
					lL = liftTargetSpeed;
				}
				else
				{
					lL = 0;
					lL = 0;
					potLTarget = 0;
					liftLGoalReached = true;
				}
				if (potR > potRTarget)
				{
					lR = liftTargetSpeed;
					lR = liftTargetSpeed;
				}
				else
				{
					lR = 0;
					lR = 0;
					potRTarget = 0;
					liftRGoalReached = true;
				}
				EndTimeSlice();
			}
		}
			
		//Set lift to inactive
		liftActive = false;
	}
}

//Global Tasks

task antiJam()
{
	int previousEncoderDriveRF = 0;
	int previousEncoderDriveLF = 0;
	int previousPotL = 0;
	int previousPotR = 0;

	while(true)
	{
		if ((previousEncoderDriveRF == encoder(driveRF)) || (previousEncoderDriveLF == encoder(driveLF)))
		{
			if (driveActive)
			{
				driveActive = false;
				driveAutonVal = 0;
				driveAutonVal = 0;
			}
		}
		else
		{
			previousEncoderDriveRF = encoder(driveRF);
			previousEncoderDriveLF = encoder(driveLF);
		}
		
		if ((previousPotL == potL) || (previousPotR == potR))
		{
			if (liftActive)
			{
				liftActive = false;
				potLTarget = 0;
				potRTarget = 0;
			}
		}
		else
		{
			previousPotL = potL;
			previousPotR = potR;
		}
		
		wait1Msec(1000);
		EndTimeSlice(); 
	}
}

task PIDController()
{
	while(true)
	{
		if (driveActive)
		{
		
		}
		
		if (liftActive)
		{
		
		}
		
		EndTimeSlice();
	}
}

task liftController()
{
	
	while(true)
	{
		if (((potRTarget != 0) && (potLTarget != 0) && (vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0)))
		{
			liftMonitor();
		}
		else if ((liftTrimThresholdEnabled) && (liftActive == false))
		{
			if (potR < liftTrimThreshold)
			{
				motor[liftLU] = -10;
				motor[liftLD] = -10;
				motor[liftRU] = -10;
				motor[liftRD] = -10;
			}
			else if ((potR > liftTrimThreshold) && (liftActive == false))
			{
				motor[liftLU] = 10;
				motor[liftLD] = 10;
				motor[liftRU] = 10;
				motor[liftRD] = 10;
			}
		
		}
		EndTimeSlice();
	}
}

#endif /* MAIN_H_ */
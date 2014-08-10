#ifndef MAIN_H_
#define MAIN_H_

typedef enum { DOWN, UP, LEFT, RIGHT, FORWARD, BACK } direction;
const float kP = 0.7;
const float kI = 0.12;
const float kD = 0.1;

int changeSpeed(int speed)
{
	float buffer = (float)speed;
	return (int)(round(buffer * speedReductionVal));
}

void resetEncoders()
{
	encoder(dLF) = 0;
	encoder(dLB) = 0;
	encoder(dRF) = 0;
	encoder(dRB) = 0;
}

void clearPreviousErrors()
{
	for (int i = 0; i < 4; i++)
	{
		speedstepPreviousError[i] = 0;
	}
}

void initDrive()
{
	motor[dRB] = 80;
	motor[dLB] = 80;
	motor[dRF] = -40;
	motor[dLF] = -40;
	wait1Msec(1000);
	motor[dRB] = 0;
	motor[dLB] = 0;
	motor[dRF] = 0;
	motor[dLF] = 0;
}

int speedstepDrive(int speedLimit, int sensorReading, int arrayID)
{
	if (speedstepDriveEnabled)
	{
		speedstepError = driveAutonVal - sensorReading;
		speedstepIntegral += speedstepError;
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
		speedstepSpeed = (int)round(kP * speedstepError + kI * speedstepIntegral + kD * speedstepDerivitive);
		if (speedstepSpeed > speedLimit)
		{
			speedstepSpeed = speedLimit;
		}
		return speedstepSpeed;
	}
	return speedLimit;
}

int speedstepLift(int speedLimit, int sensorReading, int arrayID)
{
	if (speedstepLiftEnabled)
	{
		speedstepError = driveAutonVal - sensorReading;
		speedstepIntegral += speedstepError;
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
		speedstepSpeed = (int)round(kP * speedstepError + kI * speedstepIntegral + kD * speedstepDerivitive);
		if (speedstepSpeed > speedLimit)
		{
			speedstepSpeed = speedLimit;
		}
		return speedstepSpeed;
	}
	return speedLimit;
}

void liftMonitor()
{
	if (((potR - 30 > potRTarget) && (potR + 30 < potRTarget)) || (potR == potRTarget))
	{
		liftL = 0;
		liftR = 0;
		potRTarget = 0;
		potLTarget = 0;
	}
	else
	{
		bool liftLGoalReached = false;
		bool liftRGoalReached = false;
		int dir;
		liftActive = true;
		while (((!liftLGoalReached) || (!liftRGoalReached)) && (liftActive))
		{
			if (potR < potRTarget)
			{
				dir = UP;
			}
			if (potR > potRTarget)
			{
				dir = DOWN;
			}
			if (dir == DOWN)
			{
				if (potL > potLTarget)
				{
					liftL = -liftTargetSpeed;
				}
				else
				{
					liftL = 0;
					potLTarget = 0;
					liftLGoalReached = true;
				}
				if (potR > potRTarget)
				{
					liftR = -liftTargetSpeed;
				}
				else
				{
					liftR = 0;
					potRTarget = 0;
					liftRGoalReached = true;
				}
			}
			else if (dir == UP)
			{
				if (potL > potLTarget)
				{
					liftL = liftTargetSpeed;
				}
				else
				{
					liftL = 0;
					potLTarget = 0;
					liftLGoalReached = true;
				}
				if (potR > potRTarget)
				{
					liftR = liftTargetSpeed;
				}
				else
				{
					liftR = 0;
					potRTarget = 0;
					liftRGoalReached = true;
				}
				EndTimeSlice();
			}
		}
		liftActive = false;
	}
}

task antiJam()
{
	int previousEncoderDriveRF = 0;
	int previousEncoderDriveLF = 0;
	int previousPotL = 0;
	int previousPotR = 0;

	while (true)
	{
		if ((previousEncoderDriveRF == encoder(driveRF)) || (previousEncoderDriveLF == encoder(driveLF)))
		{
			if (driveActive)
			{
				driveActive = false;
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
			previousPotL = 0;
			previousPotR = 0;
		}
		wait1Msec(1000);
		EndTimeSlice();
	}
}

task pidController()
{
	while (true)
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
	while (true)
	{
		if (((potLTarget != 0) && (potRTarget != 0) && (vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0)))
		{
			liftMonitor();
		}
		else if ((liftTrimThresholdEnabled) && (!liftActive))
		{
			if (potR < liftTrimThreshold)
			{
				motor[liftLU] = -10;
				motor[liftLD] = -10;
				motor[liftRU] = -10;
				motor[liftRD] = -10;
			}
			else if ((potR > liftTrimThreshold) && (!liftActive))
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

#endif MAIN_H_
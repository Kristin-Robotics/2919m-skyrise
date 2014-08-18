#ifndef MAIN_H_
#define MAIN_H_

//Global Functions
// changes the speed to the set value in main.h
int reduceSpeed(int speed)
{
	float buffer = (float)speed; // to prevent truncation during multiplication
	return (int)(round(buffer * speedReductionVal)); //Better rounding using the macro
}

void clearEncoders()
{
	nMotorEncoder[driveLF] = 0;
	nMotorEncoder[driveRF] = 0;
	nMotorEncoder[driveLB] = 0;
	nMotorEncoder[driveRB] = 0;
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

#endif /* MAIN_H_ */
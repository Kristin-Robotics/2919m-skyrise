#include "main.h"

bool stepComplete[] = {false,false,false};
int step[] = {0,0,0};

void clearEncoders()
{
	nMotorEncoder[lDrive1] = 0;
	nMotorEncoder[lDrive2] = 0;
	nMotorEncoder[rDrive1] = 0;
	nMotorEncoder[rDrive2] = 0;
}

// moves the selected motors, used in the macros in definitions.h
void move(int durationMsec, int leftDriveOneSpeed, int leftDriveTwoSpeed, int rightDriveOneSpeed, int rightDriveTwoSpeed, int stepArray)
{
	while ( !(stepComplete[stepArray]) )
	{
		motor[lDrive1] = leftDriveOneSpeed;
		motor[lDrive2] = leftDriveTwoSpeed;
		motor[rDrive1] = rightDriveOneSpeed;
		motor[rDrive2] = rightDriveTwoSpeed;
	}
	step[stepArray]++;

}

void lift(int liftSpeed, int stepArray)
{
	while ( !(stepComplete[stepArray]) )
	{
		motor[rightLift1] = liftSpeed;
		motor[rightLift2] = liftSpeed;
		motor[leftLift1] = liftSpeed;
		motor[leftLift2] = liftSpeed;
	}
	step[stepArray]++;

}
void potentiometerCondition(int potValue, int stepArray)
{
	if ((potValue - SensorValue[rPot]) < 0)
	{
		while (SensorValue[rPot] > potValue)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	if ((potValue - SensorValue[rPot]) > 0)
	{
		while (SensorValue[rPot] < potValue)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
}

void ultrasonicCondition(int distance, bool LS, bool RS, int stepArray)
{
	if (LS && RS)
	{
		bool lSonicComplete = false;
		bool rSonicComplete = false;
		
		while (!lSonicComplete && !rSonicComplete)
		{
			if ((distance - SensorValue[sonicLeft]) < 0)
			{
				if (SensorValue[sonicLeft] > distance)
				{
					wait1Msec(20);
				}
				else
				{
					stepComplete[stepArray] = true;
				}
			}
		
			else
			{
				if (SensorValue[sonicLeft] < distance)
				{
					wait1Msec(20);
				}
				else
				{
					stepComplete[stepArray] = true;
				}
			}
		}
	}
	else if (LS)
	{	
		if ((distance - SensorValue[sonicLeft]) < 0)
		{
			while (SensorValue[sonicLeft] > distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}
		
		else 
		{
			while (SensorValue[sonicLeft] < distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}
	}
	
	else if (RS)
	{
		if ((distance - SensorValue[sonicRight]) < 0)
		{
			while (SensorValue[sonicRight] > distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}
		
		else
		{
			while (SensorValue[sonicRight] < distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}
	}
}

void gyroCondition(int degree, bool stepArray)
{
	degree = degree * 10;
	
	if ((degree - SensorValue[turningGyro]) < 0)
	{
		while (SensorValue[turningGyro] > degree)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	else
	{
		while (SensorValue[turningGyro] < degree)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	
	stepComplete[stepArray] = true;
}

void encoderCondition(int tickL1, int tickR1, int tickL2, int tickR2, bool stepArray)
{
	clearEncoders();

	bool driveLBGoalReached = false;
	bool driveRBGoalReached = false;
	bool driveLFGoalReached = false;
	bool driveRFGoalReached = false;
	
	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)||(driveRFGoalReached == false)||(driveLFGoalReached == false)))
	{
		if (abs(nMotorEncoder[lDrive1]) > tickL1)
		{
			driveLBGoalReached=true;
		}

		if (abs(nMotorEncoder[lDrive2]) > tickL2)
		{
			driveRBGoalReached=true;
		}

		if (abs(nMotorEncoder[rDrive1]) > tickR1)
		{
			driveLFGoalReached=true;
		}

		if (abs(nMotorEncoder[rDrive2]) > tickR2)
		{
			driveRFGoalReached=true;
		}

		wait1Msec(20);
	}	
	stepComplete[stepArray] = true;
}

// void lineCondition(bool stepArray)

// autonomous task
task autonomous()
{
	ultrasonicCondition(2000,true,false,0);
}

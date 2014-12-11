#include "main.h"

bool stepComplete[] = {false,false,false};
int step[] = {0,0,0};
int testing = 0;

void clearEncoders()
{
	nMotorEncoder[lDrive1] = 0;
	nMotorEncoder[lDrive2] = 0;
	nMotorEncoder[rDrive1] = 0;
	nMotorEncoder[rDrive2] = 0;
}

// moves the selected motors, used in the macros in definitions.h
void move(int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = 127, int rightDriveOneSpeed = 127, int rightDriveTwoSpeed = 127, int stepArray = 0)
{
	while ( !(stepComplete[stepArray]) )
	{
		motor[lDrive1] = leftDriveOneSpeed;
		motor[lDrive2] = leftDriveTwoSpeed;
		motor[rDrive1] = rightDriveOneSpeed;
		motor[rDrive2] = rightDriveTwoSpeed;
	}

	motor[lDrive1] = -leftDriveOneSpeed/12;
	motor[lDrive2] = -leftDriveTwoSpeed/12;
	motor[rDrive1] = -rightDriveOneSpeed/12;
	motor[rDrive2] = -rightDriveTwoSpeed/12;
	wait1Msec(50);
	motor[lDrive1] = 0;
	motor[lDrive2] = 0;
	motor[rDrive1] = 0;
	motor[rDrive2] = 0;

	step[stepArray]++;

}

void lift(int liftSpeed = 127, int stepArray = 0)
{
	int pSpeed;

	while ( !(stepComplete[stepArray]) )
	{
		pSpeed = (int)round(liftSpeed*proportionalSpeed);

		if (pSpeed > liftSpeed)
		{
			pSpeed = liftSpeed;
		}

		motor[rightLift1] = pSpeed;
		motor[rightLift2] = pSpeed;
		motor[leftLift1] = pSpeed;
		motor[leftLift2] = pSpeed;
	}

	motor[rightLift1] = 0;
	motor[rightLift2] = 0;
	motor[leftLift1] = 0;
	motor[leftLift2] = 0;

	step[stepArray]++;

}
void potentiometerCondition(int potValue, int stepArray = 0)
{
	if ((potValue - SensorValue[rPot]) < 0)
	{
		while (SensorValue[rPot] > potValue)
		{
			proportionalSpeed = (abs(potValue - SensorValue[rPot])-254)/254;
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	if ((potValue - SensorValue[rPot]) > 0)
	{
		while (SensorValue[rPot] < potValue)
		{
			proportionalSpeed = (abs(potValue - SensorValue[rPot])-254)/254;
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
}

void ultrasonicCondition(int distance, bool LS = true, bool RS = true, int stepArray = 0)
{
	stepComplete[stepArray] = false;

	if (LS && RS)
	{
		bool lSonicComplete = false;
		bool rSonicComplete = false;

		while (!lSonicComplete && !rSonicComplete)
		{
			if ((distance - SensorValue[sonicLeft]) < 0)
			{
				while(SensorValue[sonicLeft] > distance)
				{
					wait1Msec(20);
					testing = 1;
				}
				stepComplete[stepArray] = true;
			}

			else
			{
				while (SensorValue[sonicLeft] < distance)
				{
					wait1Msec(20);
					testing = 2;
				}
				stepComplete[stepArray] = true;
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

void gyroCondition(int degree, bool stepArray = 0)
{
	stepComplete[stepArray] = false;

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

void encoderCondition(int tickL1, int tickR1 = tickL1, int tickL2 = tickL1, int tickR2 = tickL1, bool stepArray = 0)
{
	stepComplete[stepArray] = false;
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

void lineCondition(bool stepArray = 0)
{
	stepComplete[stepArray] = false;

	while (!((SensorValue[lineInnerL] < lineSensorThreshold)  && (SensorValue[lineInnerR] < lineSensorThreshold)))
	{
		wait1Msec(20);
	}
	stepComplete[stepArray] = true;
}

task motors()
{
	move();
}

// autonomous task
task autonomous()
{
	StartTask(motors);
	//MissionImpossible();
	ultrasonicCondition(500);
}

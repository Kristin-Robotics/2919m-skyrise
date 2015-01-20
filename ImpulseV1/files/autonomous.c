#include "main.h"

//Trim code
#include "/codebits/lifttrim.c"

//Compensation for skyrise weight code
#include "/codebits/liftcompensation.c"

//sgn(-5) == -1
//sgn(5) == 1
//sgn(0) == 0

bool stepComplete[] = {false,false,false};
int step[] = {0,0,0};

void clearEncoders()
{
	nMotorEncoder[lDrive2] = 0;
	nMotorEncoder[rDrive2] = 0;
}

// moves the selected motors, used in the macros in definitions.h
void move(int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = leftDriveOneSpeed, int rightDriveOneSpeed = leftDriveOneSpeed, int rightDriveTwoSpeed = leftDriveOneSpeed, int stepArray = 0)
{
	while(stepComplete[stepArray] == true)
	{
		wait1Msec(20);
	}

	while ( !(stepComplete[stepArray]) )
	{
		motor[lDrive1] = leftDriveOneSpeed;
		motor[lDrive2] = leftDriveTwoSpeed;
		motor[rDrive1] = rightDriveOneSpeed;
		motor[rDrive2] = rightDriveTwoSpeed;
		wait1Msec(20);
	}

	motor[lDrive1] = round(-(leftDriveOneSpeed)/driveBrakeConstant);
	motor[lDrive2] = round(-(leftDriveTwoSpeed)/driveBrakeConstant);
	motor[rDrive1] = round(-(rightDriveOneSpeed)/driveBrakeConstant);
	motor[rDrive2] = round(-(rightDriveTwoSpeed)/driveBrakeConstant);
	wait1Msec(100);
	motor[lDrive1] = 0;
	motor[lDrive2] = 0;
	motor[rDrive1] = 0;
	motor[rDrive2] = 0;

	step[stepArray]++;

}

void lift(int liftSpeed = 127, int stepArray = 0)
{
	while(stepComplete[stepArray] == true)
	{
		wait1Msec(20);
	}
	
	proportionalSpeed = 1.0;
	
	while ( !(stepComplete[stepArray]) )
	{
		leftLiftSpeed = round(liftSpeed*proportionalSpeed);
		rightLiftSpeed = round(liftSpeed*proportionalSpeed);
		wait1Msec(20);
	}

	leftLiftSpeed = 0;
	rightLiftSpeed = 0;

	step[stepArray]++;

}

void piston(int value, int delay = 500, int stepArray = 0)
{
	while ( !(stepComplete[stepArray]) )
	{
		wait1Msec(20);
	}
	wait1Msec(delay);
	SensorValue[skyPiston] = value;
	
	step[stepArray]++;
}

void potentiometerCondition(int potValue, int stepArray = 0)
{
	if (SensorValue[rPot] > potValue)
	{
		while (SensorValue[rPot] > potValue)
		{
			proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling + 0.1;
			
			if (proportionalSpeed > 1)
			{
				proportionalSpeed = 1;
			}	
				
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	else if (SensorValue[rPot] < potValue)
	{
		while (SensorValue[rPot] < potValue)
		{
			proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling;
			
			if (proportionalSpeed > 1)
			{
				proportionalSpeed = 1;
			}
			
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

void encoderCondition(int tickL2, int tickR2 = tickL2, int stepArray = 0)
{
	stepComplete[stepArray] = false;
	clearEncoders();

	bool driveLBGoalReached = false;
	bool driveRBGoalReached = false;

	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)))
	{
		if (abs(nMotorEncoder[lDrive2]) > tickL2)
		{
			driveLBGoalReached=true;
		}

		if (abs(nMotorEncoder[rDrive2]) > tickR2)
		{
			driveRBGoalReached=true;
		}
	}
	stepComplete[stepArray] = true;
}

void lineCondition(int stepArray = 0)
{
	stepComplete[stepArray] = false;

	while (!((SensorValue[lineInnerL] < lineSensorThreshold)  && (SensorValue[lineInnerR] < lineSensorThreshold)))
	{
		wait1Msec(20);
	}
	stepComplete[stepArray] = true;
}

void lightCondition(int threshold = 0, bool fromDark = false, int stepArray = 0)
{
	stepComplete[stepArray] = false;
	
	if (fromDark)
	{
		while(SensorValue[skyLight] > threshold)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	else
	{
		while(SensorValue[skyLight] < threshold)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
}

task liftHandle()
{
	while(true)
	{
		liftCompensation();
		
		liftTrim();
	
		motor[rightLift1] = rightLiftSpeed;
		motor[rightLift2] = rightLiftSpeed;
		motor[leftLift1] = leftLiftSpeed;
		motor[leftLift2] = leftLiftSpeed;
		
		wait1Msec(20);
	}
}

task conditional1()
{
	lightCondition(280);
	while(step[0] == 0)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 1)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 2)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 3)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 4)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 5)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 6)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 7)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 8)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 9)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 10)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 11)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 12)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 13)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 14)
	{
	wait1Msec(20);
	}
	encoderCondition(580);
	while(step[0] == 15)
	{
	wait1Msec(20);
	}
}

task command1()
{
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	wait1Msec(200);
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;
	SensorValue[skyPiston] = 0;
	wait1Msec(200);
	SensorValue[skyPiston] = 1;
	piston(0);
	move(-60);
	move(60);
	move(-60);
	move(60);
	move(-60);
	move(60);
	move(-60);
	move(60);
	move(-60);
	move(60);
	move(-60);
	move(60);
	move(-60);
	move(60);
}

// autonomous task
task autonomous()
{
	StartTask(liftHandle);
	StartTask(conditional1);
	StartTask(command1);
	//MissionImpossible();
}

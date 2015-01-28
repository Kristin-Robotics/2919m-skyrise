#include "main.h"

//Trim code
#include "/codebits/lifttrim.c"

//Compensation for skyrise weight code
#include "/codebits/liftcompensation.c"

//Autonomous functions

void clearEncoders()
{
	nMotorEncoder[lDrive2] = 0;
	nMotorEncoder[rDrive2] = 0;
}

void move(int encoderDistance,int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = leftDriveOneSpeed, int rightDriveOneSpeed = leftDriveOneSpeed, int rightDriveTwoSpeed = leftDriveOneSpeed)
{
	clearEncoders();

	bool driveLBGoalReached = false;
	bool driveRBGoalReached = false;

	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)))
	{
		motor[lDrive1] = leftDriveOneSpeed;
		motor[lDrive2] = leftDriveTwoSpeed;
		motor[rDrive1] = rightDriveOneSpeed;
		motor[rDrive2] = rightDriveTwoSpeed;
		
		if (abs(nMotorEncoder[lDrive2]) > encoderDistance)
		{
			driveLBGoalReached=true;
		}

		if (abs(nMotorEncoder[rDrive2]) > encoderDistance)
		{
			driveRBGoalReached=true;
		}
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
}

void gyroTurn(int degrees,int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = leftDriveOneSpeed, int rightDriveOneSpeed = leftDriveOneSpeed, int rightDriveTwoSpeed = leftDriveOneSpeed)
{
	degrees = abs(degrees*10);

	while (((abs(SensorValue[turningGyro]) > degrees - 50) && (abs(SensorValue[turningGyro]) > degrees + 50)) || ((abs(SensorValue[turningGyro]) < degrees - 50) && (abs(SensorValue[turningGyro]) < degrees + 50))) //not within 100 of set angle
	{
	motor[lDrive1] = leftDriveOneSpeed;
	motor[lDrive2] = leftDriveTwoSpeed;
	motor[rDrive1] = rightDriveOneSpeed;
	motor[rDrive2] = rightDriveTwoSpeed;
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

}

void liftAutonMonitor()
{
	if ((potRTarget != 0))
	{
		bool RLGoalReached = false;

		if (SensorValue[rPot] < potRTarget)
		{
			liftDirection = "up";
		}
		if (SensorValue[rPot] > potRTarget)
		{
			liftDirection = "down";
		}

		if ((SensorValue[rPot]-30 < abs(potRTarget)) && (SensorValue[rPot]+30 > abs(potRTarget)))
		{
			leftLiftSpeed = 0;
			rightLiftSpeed = 0;
		}

		else if ((potRTarget != 0) && (potLTarget != 0))
		{
			if (liftDirection == "down")
			{
				while (RLGoalReached == false)
				{
					proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling + 0.1;

					if (proportionalSpeed > 1)
					{
						proportionalSpeed = 1;
					}
					
					if (SensorValue[rPot] > potRTarget)
					{
						leftLiftSpeed = round(liftTargetSpeed*proportionalSpeed);
						rightLiftSpeed = round(liftTargetSpeed*proportionalSpeed);
					}
					else
					{
						RLGoalReached = true;
						leftLiftSpeed = 0;
						rightLiftSpeed = 0;
					}
				}
			}

			else if (liftDirection == "up")
			{
				proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling + 0.1;

				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}
				
				if (SensorValue[rPot] < potRTarget)
				{
					leftLiftSpeed = round(liftTargetSpeed*proportionalSpeed);
					rightLiftSpeed = round(liftTargetSpeed*proportionalSpeed);
				}
				else
				{
					RLGoalReached = true;
					leftLiftSpeed = 0;
					rightLiftSpeed = 0;
				}
			}
		}
	}
}

void skyriseControl(int value, int threshold = 0, int delay = 500, bool fromDark = false)
{
	if (fromDark)
	{
		while(SensorValue[skyLight] > threshold)
		{
			wait1Msec(20);
		}
	}
	else
	{
		while(SensorValue[skyLight] < threshold)
		{
			wait1Msec(20);
		}
	}
	wait1Msec(delay);
	SensorValue[skyPiston] = value;
}

void lift(int potRT,int speed)
{
	potRTarget = potRT;
	liftTargetSpeed = speed;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task liftListener()
{

	while(true)
	{
		liftAutonMonitor();
		EndTimeSlice();
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

task autonomous()
{
	//Initialise Autonomous
	StartTask(liftListener);
	StartTask(liftHandle);
	
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	wait1Msec(500);
	leftLiftSpeed = -127;
	rightLiftSpeed = -127;
	wait1Msec(200);
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	wait1Msec(700);
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;
	
	skyriseControl(1,70);
	lift(500,127);
	
}

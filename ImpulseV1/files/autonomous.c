#include "main.h"

//Trim code
#include "/userfunctions/lifttrim.c"

//Compensation for skyrise weight code
#include "/userfunctions/liftcompensation.c"

#include "/autonfunctions/basicfunctions.c"

#include "/autonfunctions/commonfunctions.c"

//Autonomous functions

void clearEncoders()
{
	nMotorEncoder[lDrive2] = 0;
	nMotorEncoder[rDrive2] = 0;
}

void encoderMove(int encoderDistance,int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = leftDriveOneSpeed, int rightDriveOneSpeed = leftDriveOneSpeed, int rightDriveTwoSpeed = leftDriveOneSpeed)
{
	clearEncoders();

	bool driveLBGoalReached = false;
	bool driveRBGoalReached = false;

	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)))
	{
		leftTrackSpeed = leftDriveOneSpeed;
		leftTrackSpeed = leftDriveTwoSpeed;
		rightTrackSpeed = rightDriveOneSpeed;
		rightTrackSpeed = rightDriveTwoSpeed;

		if (abs(nMotorEncoder[lDrive2]) > encoderDistance)
		{
			driveLBGoalReached=true;
		}

		if (abs(nMotorEncoder[rDrive2]) > encoderDistance)
		{
			driveRBGoalReached=true;
		}
	}

	leftTrackSpeed = round(-(leftDriveOneSpeed)/driveBrakeConstant);
	leftTrackSpeed = round(-(leftDriveTwoSpeed)/driveBrakeConstant);
	rightTrackSpeed = round(-(rightDriveOneSpeed)/driveBrakeConstant);
	rightTrackSpeed = round(-(rightDriveTwoSpeed)/driveBrakeConstant);

	wait1Msec(200);

	leftTrackSpeed = 0;
	leftTrackSpeed = 0;
	rightTrackSpeed = 0;
	rightTrackSpeed = 0;
}

void gyroMove(int degrees,int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = leftDriveOneSpeed, int rightDriveOneSpeed = leftDriveOneSpeed, int rightDriveTwoSpeed = leftDriveOneSpeed)
{
	degrees = abs(degrees*10);

	while (((abs(SensorValue[turningGyro]) > degrees - 50) && (abs(SensorValue[turningGyro]) > degrees + 50)) || ((abs(SensorValue[turningGyro]) < degrees - 50) && (abs(SensorValue[turningGyro]) < degrees + 50))) //not within 100 of set angle
	{
		leftTrackSpeed = leftDriveOneSpeed;
		leftTrackSpeed = leftDriveTwoSpeed;
		rightTrackSpeed = rightDriveOneSpeed;
		rightTrackSpeed = rightDriveTwoSpeed;
	}

	leftTrackSpeed = round(-(leftDriveOneSpeed)/driveBrakeConstant);
	leftTrackSpeed = round(-(leftDriveTwoSpeed)/driveBrakeConstant);
	rightTrackSpeed = round(-(rightDriveOneSpeed)/driveBrakeConstant);
	rightTrackSpeed = round(-(rightDriveTwoSpeed)/driveBrakeConstant);

	wait1Msec(100);

	leftTrackSpeed = 0;
	leftTrackSpeed = 0;
	rightTrackSpeed = 0;
	rightTrackSpeed = 0;
}

void ultrasonicMove(int distance, int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = leftDriveOneSpeed, int rightDriveOneSpeed = leftDriveOneSpeed, int rightDriveTwoSpeed = leftDriveOneSpeed, bool LS = true, bool RS = true)
{
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
					leftTrackSpeed = leftDriveOneSpeed;
					leftTrackSpeed = leftDriveTwoSpeed;
					rightTrackSpeed = rightDriveOneSpeed;
					rightTrackSpeed = rightDriveTwoSpeed;
				}
			}

			else
			{
				while (SensorValue[sonicLeft] < distance)
				{
					leftTrackSpeed = leftDriveOneSpeed;
					leftTrackSpeed = leftDriveTwoSpeed;
					rightTrackSpeed = rightDriveOneSpeed;
					rightTrackSpeed = rightDriveTwoSpeed;
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
				leftTrackSpeed = leftDriveOneSpeed;
				leftTrackSpeed = leftDriveTwoSpeed;
				rightTrackSpeed = rightDriveOneSpeed;
				rightTrackSpeed = rightDriveTwoSpeed;
			}
		}

		else
		{
			while (SensorValue[sonicLeft] < distance)
			{
				leftTrackSpeed = leftDriveOneSpeed;
				leftTrackSpeed = leftDriveTwoSpeed;
				rightTrackSpeed = rightDriveOneSpeed;
				rightTrackSpeed = rightDriveTwoSpeed;
			}
		}
	}

	else if (RS)
	{
		if ((distance - SensorValue[sonicRight]) < 0)
		{
			while (SensorValue[sonicRight] > distance)
			{
				leftTrackSpeed = leftDriveOneSpeed;
				leftTrackSpeed = leftDriveTwoSpeed;
				rightTrackSpeed = rightDriveOneSpeed;
				rightTrackSpeed = rightDriveTwoSpeed;
			}
		}

		else
		{
			while (SensorValue[sonicRight] < distance)
			{
				leftTrackSpeed = leftDriveOneSpeed;
				leftTrackSpeed = leftDriveTwoSpeed;
				rightTrackSpeed = rightDriveOneSpeed;
				rightTrackSpeed = rightDriveTwoSpeed;
			}
		}
	}

	leftTrackSpeed = round(-(leftDriveOneSpeed)/driveBrakeConstant);
	leftTrackSpeed = round(-(leftDriveTwoSpeed)/driveBrakeConstant);
	rightTrackSpeed = round(-(rightDriveOneSpeed)/driveBrakeConstant);
	rightTrackSpeed = round(-(rightDriveTwoSpeed)/driveBrakeConstant);

	wait1Msec(100);

	leftTrackSpeed = 0;
	leftTrackSpeed = 0;
	rightTrackSpeed = 0;
	rightTrackSpeed = 0;
}

void setLift(int potRT = 280,int speed = 127)
{
	potRTarget = potRT;
	liftTargetSpeed = speed;
	liftPreset = 10;
}

void setLiftTime(int time,int speed = 127)
{
	liftTime = time;
	liftTargetSpeed = speed;
	liftPreset = 10;
}

void moveLiftAuton()
{
	if (liftPreset > -1)
	{
		bool RLGoalReached = false;
		
		liftTargetSpeed = abs(liftTargetSpeed);

		if (SensorValue[rPot] < potRTarget)
		{
			liftDirection = "up";
		}
		if (SensorValue[rPot] > potRTarget)
		{
			liftDirection = "down";
		}

		if (liftDirection == "up")
		{
			while (!(RLGoalReached) && (liftPreset > -1))
			{
				proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling +0.3;

				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}

				if (SensorValue[rPot] < potRTarget)
				{
					leftLiftSpeed = liftTargetSpeed;
					rightLiftSpeed = liftTargetSpeed;

					liftCompensation();
				}
				else
				{
					RLGoalReached = true;
				}

				wait1Msec(10);
			}
		}
		else if (liftDirection == "down")
		{
			while (!(RLGoalReached) && (liftPreset > -1))
			{
				proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling;

				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}

				if (SensorValue[rPot] > potRTarget)
				{
					leftLiftSpeed = round(liftTargetSpeed*proportionalSpeed);
					rightLiftSpeed = round(liftTargetSpeed*proportionalSpeed);

					liftCompensation();
				}
				else
				{
					RLGoalReached = true;
				}

				wait1Msec(10);
			}


		}
		leftLiftSpeed = 0;
		rightLiftSpeed = 0;

		liftPreset = -1;

	}
	
	else if (liftTime > 0)
	{
		leftLiftSpeed = liftTargetSpeed;
		rightLiftSpeed = liftTargetSpeed;
		liftCompensation();
		wait1Msec(liftTime);
		leftLiftSpeed = 0;
		rightLiftSpeed = 0;
		liftTime = 0;
	}
}

void waitForLift()
{
	while (liftPreset > -1)
	{
		wait1Msec(10);
	}
	
	while(liftTime > 0)
	{
		wait1Msec(10);
	}
}

void skyriseControl(int value, int delay, int threshold = lightSensorThreshold, bool fromDark = false)
{
	if (fromDark)
	{
		while(SensorValue[skyLight] > threshold)
		{
			wait1Msec(10);
		}
	}
	else
	{
		while(SensorValue[skyLight] < threshold)
		{
			wait1Msec(10);
		}
	}
	wait1Msec(delay);
	SensorValue[skyPiston] = value;
}

void needleControl(int value, int delay = 2000)
{
	wait1Msec(delay);
	SensorValue[needle] = value;
}

void setSkyclawState(bool state)
{
	if (state)
	{
		SensorValue[skyPiston] = 1;
		return;
	}
	SensorValue[skyPiston] = 0;
}

task autonLiftProcessing()
{
	while(true)
	{
		moveLiftAuton(); //Has a while loop
		liftTrim();
		wait1Msec(10);
	}
}

task autonMotorController()
{
	while(true)
	{
		motor[lDrive1] = leftTrackSpeed;
		motor[lDrive2] = leftTrackSpeed;
		motor[rDrive2] = rightTrackSpeed;
		motor[rDrive1] = rightTrackSpeed;

		motor[leftLift1] = leftLiftSpeed;
		motor[leftLift2] = leftLiftSpeed;
		motor[leftLift3] = leftLiftSpeed;
		motor[rightLift1] = rightLiftSpeed;
		motor[rightLift2] = rightLiftSpeed;
		motor[rightLift3] = rightLiftSpeed;

		wait1Msec(10);
	}
}

task songPlayer()
{
	surprise();
	StopTask(songPlayer);
}

task autonomous()
{
	//Initialise Autonomous
	StartTask(autonLiftProcessing);
	StartTask(autonMotorController);
	//StartTask(songPlayer);

	lightCalibrationValues[0] = SensorValue[skyLight];
	
	//Claw Deployment
	setLiftTime(200,127);
	waitForLift();
	setLiftTime(200,-127);
	if ((compensation == -1) || (compensation == 1) ) //Claw on left
	{
		//First Skyrise
		setLift(520);
		
		skyriseControl(1,700,100);
		
		lightCalibrationValues[1] = SensorValue[skyLight];
		lightSensorThreshold = (lightCalibrationValues[1] + lightCalibrationValues[0])/2;
		
		setLift(800);
		
		waitForLift();
		
		encoderMove(580,-90); //Drive back to base

		skyriseControl(0,500);
		
		setLiftTime(400,-30);
		
		waitForLift();

		encoderMove(580,90); //Drive to autoloader
	}
	else
	{
		setLift(1000);
		waitForLift();
		encoderMove(580,127);
	}
}

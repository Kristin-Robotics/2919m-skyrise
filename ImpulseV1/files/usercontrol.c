#include "main.h"

int calibratedValue = 0;

int calibrateSensors()
{
	return abs(SensorValue[lineInnerL] - SensorValue[lineInnerR]) / 2;
}

bool isValid()
{
	float left = lineSensorPID(true, calibratedValue);
	float right = lineSensorPID(false, calibratedValue);
	if (left < calibratedValue || right < calibratedValue)
	{
		return false;
	}
	return true;
}

void move(int durationMsec, int leftDriveOneSpeed, int leftDriveTwoSpeed, int rightDriveOneSpeed, int rightDriveTwoSpeed)
{
	bool goalReached = false;
	int currentTime;
	motor[lDrive1] = leftDriveOneSpeed;
	motor[lDrive2]
	= leftDriveTwoSpeed;
	motor[rDrive1] = rightDriveOneSpeed;
	motor[rDrive2] = rightDriveTwoSpeed;
	while (currentTime < durationMsec)
	{
		wait1Msec(1);
		currentTime++;
	}
	goalReached = true;
	motor[lDrive1] = 0;
	motor[lDrive2] = 0;
	motor[rDrive1] = 0;
	motor[rDrive2] = 0;
}
void correctRobot()
{
	float left = lineSensorPID(true, calibratedValue);
	float right = lineSensorPID(false, calibratedValue);
	while (left < calibratedValue || right < calibratedValue)
	{
		if (left < calibratedValue)
		{
			move(1, 50, 50, 70, 70);
		}
		else if (right < calibratedValue)
		{
			move(1, 70, 70, 50, 50);
		}
	}
}

task usercontrol()
{
	int leftTrackSpeed;
	int rightTrackSpeed;
	bool arcadeMode;
	bool toggleCooldown;
	int cooldown = 0;

	while (true)
	{
		leftTrackSpeed = 0;
		rightTrackSpeed = 0;

		// processes the toggle cooldown if it is in effect.
		if (toggleCooldown)
		{
			cooldown++;
			if (cooldown >= 1000)
			{
				toggleCooldown = false;
				cooldown = 0;
			}
		}
		if (vexRT[Btn8D] == 1 && !toggleCooldown)
		{
			arcadeMode = !arcadeMode;
			toggleCooldown = true;
		}
		if (vexRT[Btn8U] == 1 && !toggleCooldown)
		{
			calibratedValue = calibrateSensors();
			toggleCooldown = true;
		}
		if (vexRT[Btn8L] == 1 && !toggleCooldown)
		{
			toggleCooldown = true;
			drive(500, 127);
			wait1Msec(500);
			while (true)
			{
				if (isValid())
				{
					drive(1, 35);
				}
				else
				{
					correctRobot();
				}
				if (vexRT[Btn8L == 1])
				{
					toggleCooldown = true;
					break;
				}
			}
		}
		// getting values
		if (!arcadeMode)
		{
			leftTrackSpeed = vexRT[Ch3];
			rightTrackSpeed = vexRT[Ch2];
		}
		else
		{
			leftTrackSpeed = vexRT[Ch3];
			rightTrackSpeed = vexRT[Ch3];
			leftTrackSpeed = leftTrackSpeed + vexRT[Ch1];
			rightTrackSpeed = rightTrackSpeed - vexRT[Ch1];
		}

		// assigning values
		motor[lDrive1] = leftTrackSpeed;
		motor[lDrive2] = leftTrackSpeed;
		motor[rDrive2] = rightTrackSpeed;
		motor[rDrive1] = rightTrackSpeed;

		wait1Msec(1);
	}
}

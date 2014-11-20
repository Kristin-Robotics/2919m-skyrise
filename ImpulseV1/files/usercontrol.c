#include "main.h"

int motorSaftey(int input)
{
	if (exponentialControlEnabled)
	{
		int sign = input / abs(input);
		input = abs(input);
		float scalingValue = 127.0 / (exponentialScalingValue - 1);
		float percentMax = input / 127.0;
		float exponentialMod = (float)(pow(exponentialScalingValue, percentMax) - 1);
		int output = (int)round(scalingValue * exponentialMod * sign);
		return output;
	}
	return input;
}

void move(int durationMsec, int leftDriveOneSpeed, int leftDriveTwoSpeed, int rightDriveOneSpeed, int rightDriveTwoSpeed)
{
	bool goalReached = false;
	int currentTime;
	motor[lDrive1] = leftDriveOneSpeed;
	motor[lDrive2] = leftDriveTwoSpeed;
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
		leftLiftSpeed = 0;
		rightLiftSpeed = 0;

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
		// autonomous routine intergrated (for dev purposes)
		if (vexRT[Btn8L] == 1 && !toggleCooldown)
		{
			toggleCooldown = true;
			drive(500, 127);
			wait1Msec(500);
			while (true)
			{
				leftValue = SensorValue[lineInnerR];
				rightValue = SensorValue[lineInnerL];
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

		// assign to lifts
		if (vexRT[Btn5D] == 1 && vexRT[Btn5U] == 0)
		{
			leftLiftSpeed = -127;
			rightLiftSpeed = -127;
		}
		else if (vexRT[Btn5U] == 1 && vexRT[Btn5D] == 0)
		{
			leftLiftSpeed = 127;
			rightLiftSpeed = 127;
		}

		// scaling motors
		leftTrackSpeed = abs(motorSaftey(leftTrackSpeed));
		rightTrackSpeed = abs(motorSaftey(rightTrackSpeed));

		// assigning values
		motor[lDrive1] = leftTrackSpeed;
		motor[lDrive2] = leftTrackSpeed;
		motor[rDrive2] = rightTrackSpeed;
		motor[rDrive1] = rightTrackSpeed;

		// assign to lifts
		motor[leftLift1] = leftLiftSpeed;
		motor[leftLift2] = leftLiftSpeed;
		motor[rightLift1] = rightLiftSpeed;
		motor[rightLift2] = rightLiftSpeed;

		wait1Msec(1);
	}
}

#include "main.h"

// moves robot at a b c d speeds for x milliseconds
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

bool isValid()
{
	bool valid = true;
	return valid;
}

void correctRobot()
{
	
}

task autonomous()
{
	do
	{
		if (isValid())
		{
			drive(10, 127);
		}
		else
		{
			correctRobot();
		}
	}
	while (true);
}
#include "main.h"

// moves the selected motors on the robot for a set duration, used in the macros in definitions.h
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

// autonomous task
task autonomous()
{
	
}

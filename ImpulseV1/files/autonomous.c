#include "main.h"

// moves robot at a b c d speeds for x milliseconds
/*void move(int durationMsec, int leftDriveOneSpeed, int leftDriveTwoSpeed, int rightDriveOneSpeed, int rightDriveTwoSpeed)
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
	if (SensorValue[lineInnerL] < lineSensorThreshold || SensorValue[lineInnerR] < lineSensorThreshold)
	{
		return false;
	}
	return true;
}

void correctRobot()
{
	while (SensorValue[lineInnerL] < lineSensorThreshold || SensorValue[lineInnerR] < lineSensorThreshold)
	{
		if (SensorValue[lineInnerL] < lineSensorThreshold)
		{
			move(1, 100, 100, 127, 127);
		}
		else if (SensorValue[lineInnerR] < lineSensorThreshold)
		{
			move(1, 127, 127, 100, 100);
		}
	}
}
*/
typedef struct {
	int x;
	int y;
} point;

task autonomous()
{
	/*do
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
	while (true);*/
}

/*
 * This file contains all of the previous attempts code for trying to get the robot
 * to follow a line properly. This file otherwise has no other use, but only as a database. 
 */

/* Attempt #1 Start */
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
/* Attempt #1 End */
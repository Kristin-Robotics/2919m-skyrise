#include "main.h"

void calibrateSensors()
{
	float averageInner = (SensorValue[lineInnerR] + SensorValue[lineInnerL]) / 2;
	float averageOuter = (SensorValue[lineOuterR] + SensorValue[lineOuterL]) / 2;
	lineSensorThreshold = (averageOuter - averageInner) / 2;
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
			calibrateSensors();
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
					drive(10, 127);
				}
				else
				{
					correctRobot();
				}
				if (vexRT[Btn8L == 1])
				{
					break;
					toggleCooldown = true;
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
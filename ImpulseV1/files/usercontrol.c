#include "main.h"

void calibrateSensors()
{
	float averageInner = (SensorValue[lineInnerR] + SensorValue[lineInnerL]) / 2;
	float averageOuter = (SensorValue[lineOuterR] + SensorValue[lineOuterL]) / 2;
	lineSensorThreshold = (averageOuter - averageInner) / 2;
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
		if (vexRt[Btn8U] == 1 && !toggleCooldown)
		{
			calibrateSensors();
			toggleCooldown = true;
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
#include "main.h"

int expControl(int input)
{
	if (expScalingEnabled)
	{
		int sign = input / abs(input);
		input = abs(input);
		float scalingVal = 127.0 / (expScalingVal - 1);
		float percentMax = input / 127.0;
		float expMod = (float)(pow(expScalingVal, percentMax) - 1);
		int output = (int)round(scalingVal * expMod * sign);
		return output;
	}
	return input;
}

// User control task
task usercontrol()
{
	int stickPrimary;
	int stickSecondary;

	while (true)
	{
		// Limit movement
		stickPrimary = (abs(vexRT[Ch3]) > abs(vexRT[Ch4]) ? vexRT[Ch3] : vexRT[Ch4]);
		stickSecondary = (abs(vexRT[Ch3]) > abs(vexRT[Ch4]) ? vexRT[Ch3] : -vexRT[Ch4]);

		// Movement and strafing
		driveLF = driveRB = stickPrimary;
		driveLB = driveRF = stickSecondary;

		// Turning
		driveLF += vexRT[Ch1];
		driveLB += vexRT[Ch1];
		driveRF -= vexRT[Ch1];
		driveRB -= vexRT[Ch1];

		// Scaling
		driveLF = expControl(driveLF);
		driveLB = expControl(driveLB);
		driveRF = expControl(driveRF);
		driveRB = expControl(driveRB);

		// Assigning
		motor[dRF] = driveRF;
		motor[dRB] = driveRB;
		motor[dLF] = driveLF;
		motor[dLB] = driveLB;

	}
}
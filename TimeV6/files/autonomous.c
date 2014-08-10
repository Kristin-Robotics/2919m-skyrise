#include "main.h"

void drive(int encoderDistance, int driveLBSpeed, int driveLFSpeed, int driveRBSpeed, int driveRFSpeed)
{
	clearPreviousErrors();
	resetEncoders();

	bool lBGoalReached = false;
	bool lFGoalReached = false;
	bool rBGoalReached = false;
	bool rFGoalReached = false;

	driveAutonVal = abs(encoderDistance);
	driveActive = true;

	while (((!lBGoalReached) || (!lFGoalReached) || (!rBGoalReached) || (rFGoalReached)) && (driveActive))
	{
		if (encoder(driveLB) < driveAutonVal)
		{

		}
	}
}

task motorController()
{

}

task autonomous()
{
	while (true)
	{

	}
}
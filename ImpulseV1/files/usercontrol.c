#include "main.h"

int liftPreset = 0;
int potLTarget = 0;
int potRTarget = 0;
int lL, lr;
int liftTargetSpeed = 0;

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

void presetAssign()
{
	if (vexRT[Btn7U] == 1)
	{
		liftPreset = 2;
	}
	else if (vexRT[Btn7D] == 1)
	{
		liftPreset = 1;
	}
}

void assignPreset()
{
	if (liftPreset != 0)
	{
		potLTarget = lPotValues[liftPreset - 1];
		potRTarget = rPotValues[liftPreset - 1];
		liftTargetSpeed = 127;
		presetMonitor();
	}
}

void presetMonitor()
{
	if ((potLTarget != 0) && (potRTarget != 0))
	{
		int potR = SensorValue[rPot];
		int potL = SensorValue[lPot];
		bool LLGoalReached = false;
		bool RLGoalReached = false;

		string direction;

		if (potR < potRTarget)
		{
			direction = "up";
		}
		if (potR > potRTarget)
		{
			direction = "down";
		}

		if ((abs(potR) - 30 < abs(potRTarget)) && ((abs(potR) + 30 > abs(potRTarget))))
		{
			lL = 0;
			lR = 0;
			potRTarget = 0;
			liftPreset = 0;
		}

		else if ((potRTarget != 0) && potLTarget != 0)
		{
			if (direction == "down")
			{
				if ((LLGoalReached == false) || (RLGoalReached == false))
				{
					if (potL > potLTarget)
					{
						lL = -(liftTargetSpeed);
					}
					else
					{
						LLGoalReached = true;
						lL = 0;
					}
					if (potR > potRTarget)
					{
						lR = -(liftTargetSpeed);
					}
					else
					{
						RLGoalReached = true;
						lR = 0;
					}
				}



			}

			else if (direction == "up")
			{
				if ((LLGoalReached == false) || (RLGoalReached == false))
				{
					if (potL < potLTarget)
					{
						lL = (liftTargetSpeed);
					}
					else
					{
						LLGoalReached = true;
						lL = 0;
					}
					if (potR < potRTarget)
					{
						lR = liftTargetSpeed;
					}
					else
					{
						RLGoalReached = true;
						lR = 0;
					}
				}
			}
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
			//calibratedValue = calibrateSensors();
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
				///leftValue = SensorValue[lineInnerR];
				//rightValue = SensorValue[lineInnerL];
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

		presetAssign();

		//Lift
		//Get Controller Values
		lL = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
		lR = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;

		if ((abs(lL) > 0) || (abs(lR) > 0))
		{
			liftPreset = 0;
		}
		else
		{
			//Lift Preset Actions
			if (liftPreset != 0)
			{
				assignPreset();
			}
		// scaling motors
		//leftTrackSpeed = abs(motorSaftey(leftTrackSpeed));
		//rightTrackSpeed = abs(motorSaftey(rightTrackSpeed));

		// assigning values
		motor[lDrive1] = leftTrackSpeed;
		motor[lDrive2] = leftTrackSpeed;
		motor[rDrive2] = rightTrackSpeed;
		motor[rDrive1] = rightTrackSpeed;

		// assign to lifts
		motor[leftLift1] = lL;
		motor[leftLift2] = lL;
		motor[rightLift1] = lR;
		motor[rightLift2] = lR;

		wait1Msec(1);
	}
}

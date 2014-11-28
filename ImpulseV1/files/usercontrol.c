#include "main.h"

int liftPreset = 0;
int potLTarget = 0;
int potRTarget = 0;
int leftLiftSpeed, rightLiftSpeed;
int liftTargetSpeed = 0;

//Code for finer driving control
int fineControl(int input) //input from value, mod is set to driver preferences
{
	if (fineControlEnabled)
	{
		int sign = input / abs(input);

		input = abs(input);

		float scalingValue = 127.0 / (fineControlValue - 1);
		float percentMax = input / 127.0;
		float modifier = (float)(pow(fineControlValue, percentMax) - 1);
		int output = (int)round(scalingValue * modifier * sign);
		return(output);
	}
	else
	{
		return(input);
	}
}

// assign presets if the corresponding button is pressed
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

// assign preset values from the stored array in variables.h
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

// execute the preset action
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
			leftLiftSpeed = 0;
			rightLiftSpeed = 0;
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
						leftLiftSpeed = -(liftTargetSpeed);
					}
					else
					{
						LLGoalReached = true;
						leftLiftSpeed = 0;
					}
					if (potR > potRTarget)
					{
						rightLiftSpeed = -(liftTargetSpeed);
					}
					else
					{
						RLGoalReached = true;
						rightLiftSpeed = 0;
					}
				}



			}

			else if (direction == "up")
			{
				if ((LLGoalReached == false) || (RLGoalReached == false))
				{
					if (potL < potLTarget)
					{
						leftLiftSpeed = (liftTargetSpeed);
					}
					else
					{
						LLGoalReached = true;
						leftLiftSpeed = 0;
					}
					if (potR < potRTarget)
					{
						rightLiftSpeed = liftTargetSpeed;
					}
					else
					{
						RLGoalReached = true;
						rightLiftSpeed = 0;
					}
				}
			}
		}

	}
}

// usercontrol task
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
		// switch to arcade mode for steering
		if (vexRT[Btn8D] == 1 && !toggleCooldown)
		{
			arcadeMode = !arcadeMode;
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

		// check what preset button is pressed
		presetAssign();

		// get lift values
		leftLiftSpeed = (vexRT[Btn5D] - vexRT[Btn5U]) * 127;
		rightLiftSpeed = (vexRT[Btn5D] - vexRT[Btn5U]) * 127;

		// if the buttons are used, then we do not need presets
		if ((abs(leftLiftSpeed) > 0) || (abs(rightLiftSpeed) > 0))
		{
			liftPreset = 0;
		}
		else
		{
			// otherwise execute preset actions
			if (liftPreset != 0)
			{
				assignPreset();
			}
			else
			{
				if ((SensorValue[rPot] < liftTrimThreshold))
				{
					leftLiftSpeed = leftLiftSpeed - 10;
					rightLiftSpeed = rightLiftSpeed - 10;
				}
				else if ((SensorValue[rPot] > liftTrimThreshold))
				{
					leftLiftSpeed = leftLiftSpeed + 10;
					rightLiftSpeed = rightLiftSpeed + 10;
				}
			}
		}

		// scaling motors [broken as of now]
		//leftTrackSpeed = abs(motorSaftey(leftTrackSpeed));
		//rightTrackSpeed = abs(motorSaftey(rightTrackSpeed));

		// assigning values to motors
		motor[lDrive1] = leftTrackSpeed;
		motor[lDrive2] = leftTrackSpeed;
		motor[rDrive2] = rightTrackSpeed;
		motor[rDrive1] = rightTrackSpeed;

		// assign values to lifts
		motor[leftLift1] = leftLiftSpeed;
		motor[leftLift2] = leftLiftSpeed;
		motor[rightLift1] = rightLiftSpeed;
		motor[rightLift2] = rightLiftSpeed;

		wait1Msec(20);
	}
}

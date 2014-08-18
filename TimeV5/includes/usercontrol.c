#include "main.h"

int liftPreset = 0;

bool intakeUpPressed = false;
bool xmtr2Connected = false;
bool intakeStarted = false;

//User functions
int expCtrl(int input) //input from value, mod is set to driver preferences
{
	if (expCtrlEnabled)
	{
		int sign = input / abs(input);

		input = abs(input);

		float scalingVal = 127.0 / (expScalingVal - 1);
		float percentMax = input / 127.0;
		float expMod = (float)(pow(expScalingVal, percentMax) - 1);
		int output = (int)round(scalingVal * expMod * sign);
		return(output);
	}
	else
	{
		return(input);
	}
}

void presetButtons()
{
	if (liftPresetsEnabled)
	{
		if (vexRT[Btn8U] == 1) // Btn8 for Goal Heights, High goal
		{
			liftPreset = 6;
		}
		if (vexRT[Btn8L] == 1) // Medium-High Goal
		{
			liftPreset = 5;
		}
		if (vexRT[Btn8R] == 1) // Medium-Low Goal
		{
			liftPreset = 4;
		}
		if (vexRT[Btn8D] == 1)  //Low Goal
		{
			liftPreset = 3;
		}
		if (vexRT[Btn7U] == 1)	//Maximum
		{
			liftPreset = 2;
		}
		if (vexRT[Btn7D] == 1)	//Minimum
		{
			liftPreset = 1;
		}
		if (vexRT[Btn7L] == 1)
		{
			if (xmtr2Connected == false)
			{
				intakeSkyrise=0;
			}
		}
		if (vexRT[Btn7R] == 1)
		{
			if (xmtr2Connected == false)
			{
				intakeSkyrise=1;
			}
		}
		if (xmtr2Connected)
		{
			if (vexRT[Btn7LXmtr2] == 1)
			{
				intakeSkyrise = 0; //Closed
			}
			if (vexRT[Btn7RXmtr2] == 1)
			{
				intakeSkyrise = 1; //Open
			}
		}
	}
}

void liftPresetMonitor()
{
	if ((potLTarget != 0) && (potRTarget != 0))
	{
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

		if ((abs(potR)-30 < abs(potRTarget)) && ((abs(potR)+30 > abs(potRTarget))))
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
					if (potR > potRTarget)
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
					if (potR < potRTarget)
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

void presetAssign()
{
	potLTarget = liftLVal[liftPreset - 1];
	potRTarget = liftRVal[liftPreset - 1];
	liftTargetSpeed = 127;
	liftPresetMonitor()
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	//Initialise user control
	int stickPrimary;
	int stickSecondary;
	
	potRTarget = 0;
	potLTarget = 0;
	liftActive = false;
	driveActive = false;
	
	while (true)
	{	
		//Limit movement to one direction
		if (abs(vexRT[Ch3]) < abs(vexRT[Ch4]))
		{
			stickPrimary = vexRT[Ch4];
			stickSecondary = -vexRT[Ch4];
		}
		else 
		{
			stickPrimary = vexRT[Ch3];
			stickSecondary = vexRT[Ch3];
		}

		// Moving and strafing actions
		dLF = stickPrimary;
		dLB = stickSecondary;
		dRF = stickSecondary;
		dRB = stickPrimary;

		// Turning actions
		dLF = dLF + vexRT[Ch1];
		dLB = dLB + vexRT[Ch1];
		dRF = dRF - vexRT[Ch1];
		dRB = dRB - vexRT[Ch1];

		// Scaling
		dLF = expCtrl(dLF);
		dLB = expCtrl(dLB);
		dRF = expCtrl(dRF);
		dRB = expCtrl(dRB);

		// Assigning
		motor[driveLB] = dLB;
		motor[driveLF] = dLF;
		motor[driveRB] = dRB;
		motor[driveRF] = dRF;


		//Button control
		presetButtons();
		
		//Lift
			//Get Controller Values
				lL=(vexRT[Btn5U]-vexRT[Btn5D])*127;
				lR=(vexRT[Btn5U]-vexRT[Btn5D])*127;

				if ((abs(lL) > 0)||(abs(lR) > 0))
				{
					liftPreset = 0;
				}
				else
				{
					//Lift Preset Actions
					if (liftPreset != 0)
					{
						presetAssign();
					}
					else
					//Trim if idle
					{
						if ((potR < liftTrimThreshold))
						{
							lL = lL - 10;
							lR = lR - 10;
						}
						else if ((potR > liftTrimThreshold))
						{
							lL = lL + 10;
							lR = lR + 10;
						}
					}

				}
		
		//Assigning lift
		motor[liftLD] = lL;
		motor[liftLU] = lL;
		motor[liftRD] = lR;
		motor[liftRU] = lR;
		
		//Get controller values
		iL = (vexRT[Btn6U]*100-vexRT[Btn6D]*80)+10;
		iR = (vexRT[Btn6U]*100-vexRT[Btn6D]*80)+10;
		
		//Intake Assign
		motor[intakeL] = iL;
		motor[intakeR] = iR;

		wait1Msec(20);
	}
}
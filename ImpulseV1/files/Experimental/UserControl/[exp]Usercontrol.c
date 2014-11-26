#include "main.h"

//Variable Storage
#include "/codebits/uservariables.c"

//Fine Control for Driver
#include "/codebits/finecontrol.c"

//Buttons
#include "/codebits/buttons.c"

//Recieve values from controller
task usercontrol()
{
	getButtonInput();
	leftLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
	rightLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
}

//Processing for Lift
task liftProcessing()
{
	while(true)
	{
		if (liftPreset > -1)
		{
			potR = SensorValue[rPot];
			potL = SensorValue[lPot];
			
			LLGoalReached = false;
			RLGoalReached = false;

			if (potR < rPotValues[liftPreset])
			{
				direction = "up";
			}
			if (potR > rPotValues[liftPreset])
			{
				direction = "down";
			}
			
			switch (direction)
			{
				case "up":
				{
					while (!(LLGoalReached && RLGoalReached) && liftPreset > -1))
					{
						if (potL < lPotValues[liftPreset])
						{
							leftLiftSpeed = ;
						}
						else
						{
							LLGoalReached = true;
						}
						
						if (potR < rPotValues[liftPreset])
						{
							rightLiftSpeed = ;
						}
						else
						{
							RLGoalReached = true;
						}
					}
				
					liftPreset = -1;
					break;
				}
				case "down":
				{
					while (!(LLGoalReached && RLGoalReached) && liftPreset > -1))
					{
						if (potL > lPotValues[liftPreset])
						{
							leftLiftSpeed = ;
						}
						else
						{
							LLGoalReached = true;
						}
						
						if (potR > rPotValues[liftPreset])
						{
							rightLiftSpeed = ;
						}
						else
						{
							RLGoalReached = true;
						}
					}
				
					liftPreset = -1;
					break;
				}
				default:
					break;
			}

		}
	}
}

//Controller for all motors
task motorController()
{
	motor[leftLift1] = leftLiftSpeed;
	motor[leftLift2] = leftLiftSpeed;
	motor[rightLift1] = rightLiftSpeed;
	motor[rightLift2] = rightLiftSpeed;
}

//Arcade or Tank Switch

//Ramping

//CONCEPT Controller input --> Processing --> Output for ALL actions
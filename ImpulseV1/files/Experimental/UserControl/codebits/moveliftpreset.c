void moveLiftPreset()
{
	if (liftPreset > -1)
	{		
		LLGoalReached = false;
		RLGoalReached = false;

		if (SensorValue[rPot] < potRTarget)
		{
			direction = "up";
		}
		if (SensorValue[rPot] > potRTarget)
		{
			direction = "down";
		}
		
		if (direction == "up")
		{
			while (!(LLGoalReached && RLGoalReached) && liftPreset > -1))
			{
				if (SensorValue[lPot] < potLTarget)
				{
					leftLiftSpeed = 127;
				}
				else
				{
					LLGoalReached = true;
				}
				
				if (SensorValue[rPot] < potRTarget)
				{
					rightLiftSpeed = 127;
				}
				else
				{
					RLGoalReached = true;
				}
				sleep(20);
			}
			
			liftPreset = -1;
			}
		else if (direction == "down")
		{
			while (!(LLGoalReached && RLGoalReached) && liftPreset > -1))
			{
				if (SensorValue[lPot] > potLTarget)
				{
					leftLiftSpeed = -127;
				}
				else
				{
					LLGoalReached = true;
				}
				
				if (SensorValue[rPot] > potRTarget)
				{
					rightLiftSpeed = -127;
				}
				else
				{
					RLGoalReached = true;
				}
				sleep(20);
			}
		
			liftPreset = -1;
		}

	}
}
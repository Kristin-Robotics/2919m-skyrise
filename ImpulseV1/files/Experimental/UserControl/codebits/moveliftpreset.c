void moveLiftPreset()
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
		
		if (direction == "up")
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
				wait1MSec(20);
			}
			
			liftPreset = -1;
			}
		else if (direction == "down")
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
				wait1MSec(20);
			}
		
			liftPreset = -1;
		}

	}
}
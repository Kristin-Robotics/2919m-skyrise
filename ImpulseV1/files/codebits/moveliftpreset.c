void moveLiftPreset()
{
	if (liftPreset > -1)
	{		
		LLGoalReached = true;
		RLGoalReached = true;

		if (SensorValue[rPot] < potRTarget)
		{
			liftDirection = "up";
		}
		if (SensorValue[rPot] > potRTarget)
		{
			liftDirection = "down";
		}
		
		if (liftDirection == "up")
		{
			LLGoalReached = false;
			RLGoalReached = false;
			while (!(LLGoalReached && RLGoalReached) && (liftPreset > -1))
			{
				proportionalSpeed = 1; //abs(abs(potRTarget) - abs(SensorValue[rPot]))/285;
				
				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}
				
				if (SensorValue[rPot] < potRTarget)
				{
					leftLiftSpeed = 127 * proportionalSpeed;
				}
				else
				{
					LLGoalReached = true;
				}
				
				if (SensorValue[rPot] < potRTarget)
				{
					rightLiftSpeed = 127 * proportionalSpeed;
				}
				else
				{
					RLGoalReached = true;
				}
				wait1Msec(20);
			}
			
			liftPreset = -1;
			}
		else if (liftDirection == "down")
		{
			LLGoalReached = false;
			RLGoalReached = false;
			while (!(LLGoalReached && RLGoalReached) && (liftPreset > -1))
			{
			
				proportionalSpeed = 1;//abs(abs(potRTarget) - abs(SensorValue[rPot]))/285;
				
				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}			

				if (SensorValue[rPot] > potRTarget)
				{
					leftLiftSpeed = -127 * proportionalSpeed;
				}
				else
				{
					LLGoalReached = true;
				}
				
				if (SensorValue[rPot] > potRTarget)
				{
					rightLiftSpeed = -127 * proportionalSpeed;
				}
				else
				{
					RLGoalReached = true;
				}
				wait1Msec(20);
			}
		
			liftPreset = -1;
		}

	}
}
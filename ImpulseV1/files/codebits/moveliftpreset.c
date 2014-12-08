void moveLiftPreset()
{
	if (liftPreset > -1)
	{		
		LLGoalReached = false;
		RLGoalReached = false;

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
			while (!(LLGoalReached && RLGoalReached) && liftPreset > -1)
			{
				proportionalSpeed = (abs(potRTarget - SensorValue[rPot])-254)/254
				
				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}
				
				if (SensorValue[rPot] < potRTarget)
				{
					leftLiftSpeed = round(127*proportionalSpeed);
				}
				else
				{
					LLGoalReached = true;
				}
				
				if (SensorValue[rPot] < potRTarget)
				{
					rightLiftSpeed = round(127*proportionalSpeed);
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
			while (!(LLGoalReached && RLGoalReached) && liftPreset > -1)
			{
			
				proportionalSpeed = (abs(potRTarget - SensorValue[rPot])-254)/254
				
				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}			

				if (SensorValue[rPot] > potRTarget)
				{
					leftLiftSpeed = round(-127*proportionalSpeed);
				}
				else
				{
					LLGoalReached = true;
				}
				
				if (SensorValue[rPot] > potRTarget)
				{
					rightLiftSpeed = round(-127*proportionalSpeed);
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
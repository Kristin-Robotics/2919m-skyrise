
void moveLiftPreset()
{
	if (liftPreset > -1)
	{		
		bool RLGoalReached = false;

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
			while (!(RLGoalReached) && (liftPreset > -1))
			{
				proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling +0.3;
				
				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}
				
				if (SensorValue[rPot] < potRTarget)
				{
					leftLiftSpeed = liftTargetSpeed;
					rightLiftSpeed = liftTargetSpeed;
					liftCompensation();
				}
				else
				{
					RLGoalReached = true;
				}
				
				wait1Msec(20);
			}
			
			leftLiftSpeed = 0;
			rightLiftSpeed = 0;
			
			liftPreset = -1;
			}
		else if (liftDirection == "down")
		{
			while (!(RLGoalReached) && (liftPreset > -1))
			{
				proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling;
				
				if (proportionalSpeed > 1)
				{
					proportionalSpeed = 1;
				}
				
				if (SensorValue[rPot] > potRTarget)
				{
					leftLiftSpeed = round(-127 * proportionalSpeed);
					rightLiftSpeed = round(-127 * proportionalSpeed);
					liftCompensation();
				}
				else
				{
					RLGoalReached = true;
				}
				
				wait1Msec(20);
			}
		
			leftLiftSpeed = 0;
			rightLiftSpeed = 0;
			
			liftPreset = -1;
		}

	}
}
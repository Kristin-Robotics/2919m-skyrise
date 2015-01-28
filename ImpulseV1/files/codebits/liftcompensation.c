void liftCompensation()
{
	if (compensation == 1)
	{
		if (leftLiftSpeed > 0)
		{
			leftLiftSpeed = round(leftLiftSpeed*compensationFactor);
		}
		else
		{
			rightLiftSpeed = round(rightLiftSpeed*compensationFactor);
		}
	}
	else if (compensation == -1)
	{
		if (leftLiftSpeed > 0)
		{		
			rightLiftSpeed = round(rightLiftSpeed*compensationFactor);
		}
		else
		{
			leftLiftSpeed = round(leftLiftSpeed*compensationFactor);
		}
	
		
	}
}
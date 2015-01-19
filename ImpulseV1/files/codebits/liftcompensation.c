void liftCompensation()
{
	if (compensation == -1)
	{
		leftLiftSpeed = round(leftLiftSpeed*compensationFactor);
	}
	else if (compensation == 1)
	{
		rightLiftSpeed = round(rightLiftSpeed*compensationFactor);
	}
}
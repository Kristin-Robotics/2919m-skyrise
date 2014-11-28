void liftTrim()
{
	if ((leftLiftSpeed == 0) && (rightLiftSpeed == 0))
	{
		if (SensorValue[rPot] < liftTrimThreshold)
		{
			leftLiftSpeed = leftLiftSpeed - 10;
			rightLiftSpeed = rightLiftSpeed - 10;
		}
		else if (SensorValue[rPot] > liftTrimThreshold)
		{
			leftLiftSpeed = leftLiftSpeed + 10;
			rightLiftSpeed = rightLiftSpeed + 10;
		}
	}
}
void liftTrim()
{
	if ((leftLiftSpeed == 0) && (rightLiftSpeed == 0) && (liftPreset == -1))
	{
		if (SensorValue[rPot] < liftTrimThreshold)
		{
			leftLiftSpeed = leftLiftSpeed - 20;
			rightLiftSpeed = rightLiftSpeed - 20;
		}
		else if (SensorValue[rPot] > liftTrimThreshold)
		{
			leftLiftSpeed = leftLiftSpeed + 10;
			rightLiftSpeed = rightLiftSpeed + 10;
		}
	}
}

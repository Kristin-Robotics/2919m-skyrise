void liftTrim()
{
	if ((leftLiftSpeed == 0) && (rightLiftSpeed == 0) && (liftPreset == -1))
	{
		leftLiftSpeed = leftLiftSpeed + 10;
		rightLiftSpeed = rightLiftSpeed + 10;
	}
}

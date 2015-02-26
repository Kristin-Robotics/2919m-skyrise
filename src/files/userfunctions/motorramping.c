int slopeLimiter(int oldValue, int newValue, int maxStepSize)
{
	int delta = newValue - oldValue;
	if (delta > maxStepSize)
	{
		delta = maxStepSize;
	}
	if (delta < 0 - maxStepSize)
	{
		delta = 0 - maxStepSize;
	}
	if (newValue == 0)
	{
		delta = 0;
	}
	return delta;
}

//Code for finer driving control
int fineControl(int input) //input from value, mod is set to driver preferences
{
	if (fineControlEnabled)
	{
		int sign = input / abs(input);

		input = abs(input);

		float scalingValue = 127.0 / (fineControlValue - 1);
		float percentMax = input / 127.0;
		float modifier = (float)(pow(fineControlValue, percentMax) - 1);
		int output = (int)round(scalingValue * modifier * sign);
		return(output);
	}
	else
	{
		return(input);
	}
}
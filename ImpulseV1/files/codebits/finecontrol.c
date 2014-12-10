//Code for finer driving control
int fineControl(int input) //input from value, mod is set to driver preferences
{
	if (fineControlEnabled)
	{
		int sign = input / abs(input);

		input = abs(input);
		
		float percentage = (input/127.0); //Find relative speed to max speed
		float fineMod = (pow(fineControlValue,percentage)-1); //find the modifier value to multiply by
		float scalingValue = (127.0/(fineControlValue-1)); //value to multiply back by after modification
		
		int output = (int)(round(scalingValue*sign*fineMod));
		
		return(output);
	}
	else
	{
		return(input);
	}
}
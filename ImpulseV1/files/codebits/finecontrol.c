float percentage;
float fineMod;
float scalingValue;

//Code for finer driving control
int fineControl(int input) //input from value, mod is set to driver preferences
{
		int sign = input / abs(input);

		input = abs(input);

		percentage = (input/127.0); //Find relative speed to max speed
		fineMod = (pow(fineControlValue,percentage)-1); //find the modifier value to multiply by
		scalingValue = (127.0/(fineControlValue-1)); //value to multiply back by after modification

		int output = (int)(round(scalingValue*sign*fineMod));

		return(output);
}

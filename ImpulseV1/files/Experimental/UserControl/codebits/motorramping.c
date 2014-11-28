int motorRamping(int input, int selectedMotor, int timer)
{
	int newSpeed;
	
	if (selectedMotor < input) && (time1[0] > 100)
	{
		newSpeed = selectedMotor + 10;
		ClearTimer(time1[timer]);
		
		if (newSpeed > input)
		{
			newSpeed = input;
		}
		
		return(newSpeed);
	}
}
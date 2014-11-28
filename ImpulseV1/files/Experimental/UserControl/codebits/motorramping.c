int motorRamping(int input, int selectedMotor, int timer)
{
	if (selectedMotor < input) && (time1[0] > 100)
	{
		selectedMotor = selectedMotor + 10;
		ClearTimer(time1[timer]);
		return(selectedMotor);
	}
}
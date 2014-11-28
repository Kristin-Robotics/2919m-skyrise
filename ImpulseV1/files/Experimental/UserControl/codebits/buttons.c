void getButtonInput()
{
	if (vexRT[Btn7U] == 1)
	{
		liftPreset = 1;
	}
	if (vexRT[Btn7D] == 1)
	{
		liftPreset = 0;
	}
	if (vexRT[Btn8D] == 1)
	{
		driveModeButton == true;
	}
}
void assignLiftPreset()
{
	if (liftPreset > -1)
	{
		potLTarget = lPotValues[liftPreset];
		potRTarget = rPotValues[liftPreset];
	}
}
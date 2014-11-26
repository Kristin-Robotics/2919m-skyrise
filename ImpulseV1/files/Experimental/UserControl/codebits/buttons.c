void getButtonInput()
{
	if (vexRT[Btn7U] == 1)
	{
		liftPreset = 1;
	}
	else if (vexRT[Btn7D] == 1)
	{
		liftPreset = 0;
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
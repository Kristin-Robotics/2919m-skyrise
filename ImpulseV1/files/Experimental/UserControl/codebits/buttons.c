void getButtonInput()
{
	if (vexRT[Btn7U] == 1)
	{
		potLTarget = lPotValues[1];
		potRTarget = rPotValues[1];
		liftPreset = 1;
	}
	if (vexRT[Btn7D] == 1)
	{
		potLTarget = lPotValues[0];
		potRTarget = rPotValues[0];
		liftPreset = 0;
	}
	if (vexRT[Btn8D] == 1)
	{
		driveModeButton == true;
	}
}
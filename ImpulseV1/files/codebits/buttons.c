void getButtonInput()
{
	if (vexRT[Btn8U] == 1)
	{
		potLTarget = lPotValues[1];
		potRTarget = rPotValues[1];
		liftPreset = 1;
	}
	if (vexRT[Btn8D] == 1)
	{
		potLTarget = lPotValues[0];
		potRTarget = rPotValues[0];
		liftPreset = 0;
	}
	if (vexRT[Btn7D] == 1)
	{
		driveModeButton = true;
	}
	if  (vexRT[Btn7L] == 1)
	{
		SensorValue[skyPiston] = 0;
	}
	if  (vexRT[Btn7R] == 1)
	{
		SensorValue[skyPiston] = 1;
	}
}
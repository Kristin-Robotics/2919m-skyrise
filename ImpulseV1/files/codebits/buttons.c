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
	
	if  (vexRT[Btn6U] == 1)
	{
		skyClawButton = true;
	}
	
	if  (vexRT[Btn6D] == 1)
	{
		needleButton = true;
	}
	
	if ((vexRT[Btn5U] == 1)||(vexRT[Btn5D] == 1))
	{
		liftPreset = -1;
		firstRun = false;
	}
}

void buttonResponse()
{
	if (driveModeButton)
	{
		if (vexRT[Btn7D] == 0)
		{
			if (arcadeDriveMode)
			{
				arcadeDriveMode = false;
				driveModeButton = false;
			}
			else
			{
				arcadeDriveMode = true;
				driveModeButton = false;
			}

		}
	}
	
	if (skyClawButton)
	{
		if (vexRT[Btn6U] == 0)
		{
			if (skyClawState == 0)
			{
				skyClawState = 1;
				SensorValue[skyPiston] = 1;
				skyClawButton = false;
			}
			else
			{
				skyClawState = 0;
				SensorValue[skyPiston] = 0;
				skyClawButton = false;
			}

		}
	}	
	
	if (needleButton)
	{
		if (vexRT[Btn6D] == 0)
		{
			if (needleState == 0)
			{
				needleState = 1;
				SensorValue[needle] = 1;
				needleButton = false;
			}
			else
			{
				needleState = 0;
				SensorValue[needle] = 0;
				needleButton = false;
			}

		}
	}	
}
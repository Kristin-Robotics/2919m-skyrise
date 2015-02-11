void getButtonInput()
{
	//Controller 1
	
	if (vexRT[Btn8U] == 1)
	{
		potRTarget = rPotValues[1];
		liftPreset = 1;
		liftTargetSpeed = 127;
	}
	if (vexRT[Btn8D] == 1)
	{
		potRTarget = rPotValues[0];
		liftPreset = 0;
		liftTargetSpeed = 127;
	}
	if (vexRT[Btn8R] == 1)
	{
		potRTarget = rPotValues[2];
		liftPreset = 2;
		liftTargetSpeed = 127;
	}
	
	if (vexRT[Btn8L] == 1)
	{
		skyriseLiftButton = true;
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
		ClearTimer(T1);
		needleCtrlButton = true;
		
		if (needleState = 0)
		{
			needleState = 1;
			SensorValue[needle] = 1;
		}
	}

	if ((vexRT[Btn5U] == 1)||(vexRT[Btn5D] == 1))
	{
		liftPreset = -1;
		firstRun = false;
	}

	if (SensorValue[needleSwitch] == 0)
	{
		needleButton = true;
	}
	
	
	//Controller 2
	if  ((vexRT[Btn7LXmtr2] == 1) || (vexRT[Btn7RXmtr2] == 1) || (vexRT[Btn7UXmtr2] == 1) || (vexRT[Btn7DXmtr2] == 1) || (vexRT[Btn8LXmtr2] == 1) || (vexRT[Btn8RXmtr2] == 1) || (vexRT[Btn8UXmtr2] == 1 || vexRT[Btn8DXmtr2] == 1))
	{
		autonUser = true;
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
		if ((SensorValue[needleSwitch] == 1) && (needleCtrlButton == false))
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

	if (needleCtrlButton)
	{
		if ((vexRT[Btn6D] == 0) && (needleButton == false) && (needleState == 1) && (time1[T1] > 300))
		{
			needleState = 0;
			SensorValue[needle] = 0;
			needleCtrlButton = false;
		}
	}
	
	if (skyriseLiftButton)
	{
		if (vexRT[Btn8L] == 0)
		{
			skyriseCounter++;
			
			if (skyriseCounter > 5)
			{
				skyriseCounter = 1;
			}
			
			potRTarget = 510 + 250 * skyriseCounter;
			liftPreset = 90;
			liftTargetSpeed = 127;
			skyriseLiftButton = false;
		}
	}
}

/*
void getButtonInputXmitter2()
{
//Controller 1
	if  ((vexRT[Btn7L] == 1) || (vexRT[Btn7R] == 1) || (vexRT[Btn7U] == 1) || (vexRT[Btn7D] == 1) || (vexRT[Btn8L] == 1) || (vexRT[Btn8R] == 1) || (vexRT[Btn8U] == 1) || (vexRT[Btn8D] == 1) || (vexRT[Btn5U] == 1) || (vexRT[Btn5D] == 1) || (vexRT[Btn6U] == 1) || (vexRT[Btn6D] == 1) || (abs(vexRT[Ch1]) > 10) || (abs(vexRT[Ch2]) > 10) || (abs(vexRT[Ch3]) > 10) || (abs(vexRT[Ch4]) > 10))
	{
		StopTask(driveProcessing);
		autonUser = false;
		autonUserStep = -1;
	}
	else
	{
	//Controller 2
		if (vexRT[Btn7LXmtr2] == 1)
		{
			autonUserStep = 0;
			StartTask(driveProcessing);
		}
		if (vexRT[Btn7UXmtr2] == 1)
		{
			autonUserStep = 1;
			StartTask(driveProcessing);
		}
	}
}

void buttonResponseXmitter2()
{
	//First Skyrise
	while(autonUserStep == 0)
	{
		setSkyclawState(true); //Grab Skyrise
		setLift(550); //Lift skyrise out of autoloader
		encoderMove(620,-90); //Drive back to base
		waitForLift();
		setLift(300,5); //Lower Skyrise into base
		waitForLift();
		setSkyclawState(false); //Drop Skyrise
		setLift(500); //Lift above autoloader height
		encoderMove(560,100) //Drive to autoloader
		waitForLift();
	}
	autonUserStep = -1;
	StopTask(driveProcessing);
}
*/

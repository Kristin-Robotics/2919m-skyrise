task command1()
{
	if ((compensation == -1) || (compensation == 1) ) //Claw on left
	{
		//Step 0
		autoSetLiftComp(0,127);
		
		autoSetSkyrise(0,1,700);
		
		autoSetLiftComp(0,127);
		
		autoSetDriveFull(0,-90);
		
		wait1Msec(500);
		
		autoSetLiftComp(0,-30);
		
		autoSetSkyrise(0,0,0);
		
		//Step 6
		
		setStep(0,0);
	
		if (autonUser == false)
		{
			StartTask(command2)
			StartTask(condition2)
			StartTask(command2_1)
			StartTask(condition2_1)
		}
	}
	
	else
	{
		autoSetLiftComp(0,127);
		autoSetDriveFull(0,90);
	}
	
	//End
	StopTask(command1);
	


}

task condition1()
{
	if ((compensation == -1) || (compensation == 1) ) //Claw on left
	{
	//1	
	autoPotentiometerCondition(0,520);
	
	autoLightCondition(0);
	
	autoPotentiometerCondition(0,800);
	
	autoEncoderCondition(0,580);
	
	wait1Msec(500);
	
	autoTimeCondition(0,600);

	autoLightCondition(0);
	
	autoPotentiometerCondition(0,520);
	}
	else
	{
		autoPotentiometerCondition(0,1000);
		autoEncoderCondition(0,580);
	}
	
	StopTask(condition1);
}
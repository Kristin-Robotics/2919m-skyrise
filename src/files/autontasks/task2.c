task command2()
{
	//Step 0
	autoSetLiftComp(0,127);
	
	autoSetDriveFull(0,90);
	
	autoSetSkyrise(0,1,700);
	
	autoSetLiftComp(0,127);
	
	autoSetDriveFull(0,-90);
	
	wait1Msec(500);
	
	autoSetLiftComp(0,-30);
	
	autoSetSkyrise(0,0,0);
	
	autoSetLiftComp(0,127);
	
	//Step 8
	
	if (autonUser == false)
	{
		// StartTask(command3);
		// StartTask(condition3);
		// StartTask(command3_1);
		// StartTask(condition3_1);
	}
	
	StopTask(command2);
}

task condition2()
{
	autoEncoderCondition(0,580);
	
	autoLightCondition(0);
	
	autoPotentiometerCondition(0,800);
	
	autoEncoderCondition(0,580);
	
	wait1Msec(500);
	
	autoTimeCondition(0,400);

	autoLightCondition(0);
	
	autoPotentiometerCondition(0,520);
	
	StopTask(condition2);
}

task command2_1()
{
}

task condition2_1()
{
}
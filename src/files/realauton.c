short const AUTOLOADER_HEIGHT = 520, BOTTOM_HEIGHT = 350;
short auton;

void skyriseScore() {
	driveEncoder(50, -50);
	
	SensorValue[skyPiston] = 1;
	
	wait1Msec(500);
	
	manualLift = true;
	
	mots[LIF] = 127;
	wait1Msec(200);
	mots[LIF] = 0;
	
	resetArmVal();
	wait1Msec(300);
	
	driveEncoder(400, -60);
	
	armVal = BOTTOM_HEIGHT;
	wait1Msec(1500);
	
	SensorValue[skyPiston] = 0;
	
	armVal = AUTOLOADER_HEIGHT;
	waitForArmVal();
	
	
}

task autonomous()
{
	// Deploy lift
	StartTask(secondaryControl);
	mots[LIF] = 100;
	wait1Msec(550);
	mots[LIF] = 0;
	
	wait1Msec(500);
	
	// For movement of the arm do either
	// manualLift = true;
	// mots[LIF] = 100; <- That's the motor power
	// or
	// armVal = 100; <- That's the potentiometer value
	// waitForArmVal();
	
	// For the movmeent of the wheels do either
	// driveTime(miliseconds, leftPower, rightPower (optional))
	// or
	// driveEncoder(distance, leftPower, rightPower (optional))
	
	if (compensation == 0)
	{
		// The "not skyrise" auton
	}
	else
	{
		// For getting those skyrises
		armVal = AUTOLOADER_HEIGHT;
		waitForArmVal();
		
		skyriseScore();
		driveEncoder(450, 60);
		
		//If the second deployment is iffy, delete these two lines below
		wait1Msec(2000);
		skyriseScore();
	}
}

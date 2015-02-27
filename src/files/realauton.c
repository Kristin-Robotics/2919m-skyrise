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
	auton = SensorValue[compensationMonitor] / 682;
	
	StartTask(secondaryControl);
	mots[LIF] = 100;
	wait1Msec(550);
	mots[LIF] = 0;
	
	wait1Msec(500);
	
	armVal = AUTOLOADER_HEIGHT;
	waitForArmVal();
	
	skyriseScore();
	driveEncoder(450, 60);
	wait1Msec(2000);
	skyriseScore();
	
	while (true) { };
}
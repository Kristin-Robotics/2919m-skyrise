#include "main.h"

#include "/autonfunctions/basicfunctions.c"

#include "/autonfunctions/commonfunctions.c"

task command1()
{
	//auto for automatic code
	autoSetLiftFull(1,127);
	
	autoSetLiftFull(1,-127);
	
	autoSetLiftFull(1,127);
	
	autoSetSkyrise(1,1);
	
	autoSetLiftComp(1,127);
	
	//manual code block with 2 actions for one condition
	setLiftComp(-1);
	setDrive(-90);
	waitForStepStatus(1,true);
	setLiftTrim();
	softBrake(-90);
	nextStep(1);
	waitForStepStatus(1,false);
	
	setSkyrise(0);
	
	autoSetLiftComp(1,127);

}

task command2()
{
	waitForStep(1,6);
	autoSetDrive(2,90);
}

task conditions1()
{
	autoTimeCondition(1,200);
	
	autoTimeCondition(1,200);
	
	autoTimeCondition(1,270);
	
	autoTimeCondition(1,500);
	
	autoTimeCondition(1,200);
	
	autoPotentiometerCondition(1,280);
	
	autoEncoderCondition(1,583);
	
	autoTimeCondition(1,220);
}

task conditions2()
{
	waitForStep(1,6);
	autoEncoderCondition(2,585);
}

task autonomous()
{
	//Initialise Autonomous
	StartTask(command1);
	StartTask(command2);
	StartTask(conditions1);
	StartTask(conditions2);
	wait1Msec(90000);
	
	lightCalibrationValues[0] = SensorValue[skyLight];
	/*
	//Claw Deployment
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	wait1Msec(200);
	leftLiftSpeed = -127;
	rightLiftSpeed = -127;
	wait1Msec(200);
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;

	Autonomous Selector
	if (compensation == -1) //Claw on left
	{
	}
	else if (compensation == 1) //claw on right
	{
	}
	else //Got nothing
	{
	}
	Most of this selection code is in pre-auton, look there

	//Rubberband Deployment + Autoloader Height
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	wait1Msec(270);
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;

	//First Skyrise
	wait1Msec(500);
	SensorValue[skyPiston] = 1; //Grab Skyrise
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	lightCalibrationValues[1] = SensorValue[skyLight];
	lightSensorThreshold = (lightCalibrationValues[1] + lightCalibrationValues[0])/2;
	wait1Msec(200);
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;
	setLift(280,1);
	//setLift(550); //Lift skyrise out of autoloader
	encoderMove(583,-90); //Drive back to base
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;
	SensorValue[skyPiston] = 0; //Drop Skyrise
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	wait1Msec(220);
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;
	//setLift(300); //Lift above autoloader height
	encoderMove(585,100); //Drive to autoloader
	waitForLift();
	*/
}
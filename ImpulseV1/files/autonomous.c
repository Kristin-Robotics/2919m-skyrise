#include "main.h"

#include "/autonfunctions/basicfunctions.c"

#include "/autonfunctions/commonfunctions.c"

task command1()
{
	if ((compensation == -1) || (compensation == 1) ) //Claw on left
	{
	//auto for automatic code
	//1.1 - 0
	autoSetLiftComp(0,127);
	
	autoSetSkyrise(0,1,700);
	
	autoSetLiftComp(0,127);
	
	autoSetDriveFull(0,-90);
	
	wait1Msec(500);
	
	autoSetLiftComp(0,-30);
	
	autoSetSkyrise(0,0,0);
	
	//1.2 - 6
	autoSetDriveFull(0,90);
	
	waitForStep(1,1);
	
	autoSetSkyrise(0,1,700);
	
	autoSetDriveFull(0,-90);
	
	waitForStep(1,2);
	
	wait1Msec(500);
	
	autoSetLiftComp(0,-30);
	
	autoSetSkyrise(0,0,0);
	}
	else
	{
		autoSetLiftComp(0,127);
	}
	//End
	StopTask(command1);

}

task command2()
{
	if ((compensation == -1) || (compensation == 1) ) //Claw on left
	{
	//2.2 - 0
	waitForStep(0,6);
		
	autoSetLiftComp(0,127);
	
	//2.2 - 1	
	waitForStep(0,8);
	
	autoSetLiftComp(0,127);

	}
	
	StopTask(command2);
	
}

task conditions1()
{
	if ((compensation == -1) || (compensation == 1) ) //Claw on left
	{
	//1	
	autoPotentiometerCondition(0,510);
	
	autoLightCondition(0);
	
	autoPotentiometerCondition(0,700);
	
	autoEncoderCondition(0,580);
	
	wait1Msec(500);
	
	autoTimeCondition(0,600);

	autoLightCondition(0);
	
	//2
	autoEncoderCondition(0,580);
	
	waitForStep(1,1);
	
	autoLightCondition(0);
	
	autoEncoderCondition(0,580);
	
	waitForStep(1,2);
	
	wait1Msec(500);
	
	autoTimeCondition(0,300);

	autoLightCondition(0);
	}
	else
	{
		autoPotentiometerCondition(0,1000);
	}
	
	StopTask(conditions1);
}

task conditions2()
{
	if ((compensation == -1) || (compensation == 1) ) //Claw on left
	{
	//2
	waitForStep(0,6);
	
	autoPotentiometerCondition(1,450);
	
	waitForStep(0,8);
	
	autoPotentiometerCondition(1,700);
	}
	
	StopTask(conditions2);
}

task songPlayer()
{
	MissionImpossible();
	StopTask(songPlayer);
}

task autonomous()
{
	//Deployment
	setLift(127,127,127,127,127,127);
	wait1Msec(150);
	setLift(-127,-127,-127,-127,-127,-127);
	wait1Msec(150);
	setLiftTrim();
	
	//Initialise Autonomous
	StartTask(command1);
	StartTask(command2);
	StartTask(conditions1);
	StartTask(conditions2);
	StartTask(songPlayer);
	wait1Msec(90000);
}
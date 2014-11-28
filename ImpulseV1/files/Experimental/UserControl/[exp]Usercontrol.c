#include "main.h"

//Variable Storage
#include "/codebits/uservariables.c"

//Fine Control for Driver
#include "/codebits/finecontrol.c"

//Buttons
#include "/codebits/buttons.c"

//Move the lift automatically
#include "/codebits/moveliftpreset.c"

//Slowly increase speed over speed/100 seconds
#include "/codebits/motorramping.c"

//Controller interaction
task usercontrol()
{
	StartTask(liftProcessing);
	StartTask(tankDrive);
	StartTask(motorController);
	
	while(true)
	{
		getButtonInput();
		
		if (driveModeButton)
		{
			if (vexRT[Btn8D] == 0)
			{
				switch(driveMode)
				{
					case "tank":
					stopTask(tankDrive);
					startTask(arcadeDrive);
					driveMode = "arcade"
					driveModeButton = false;
					break;
					
					case "arcade":
					stopTask(arcadeDrive);
					startTask(tankDrive);
					driveMode = "tank"
					driveModeButton = false;
					break;
					
					default:
					driveModeButton = false;
					break;
				}
					
			}
		}
		
		if ((vexRT[Btn5U] == 1)||(vexRT[Btn5D] == 1))
		{
			liftPreset = -1;
		}
		
		leftLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
		rightLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
		
		sleep(20);
	}
}

//Processing for Lift
task liftProcessing()
{
	while(true)
	{
		moveLiftPreset(); //Has a while loop
		sleep(20);
	}
}

task arcadeDrive()
{
	while(true)
	{
		leftTrackSpeed = fineControl(vexRT[Ch3] + vexRT[Ch1]);
		rightTrackSpeed = fineControl(vexRT[Ch3] - vexRT[Ch1]);
		
		sleep(20);
	}

}

task tankDrive()
{
	while(true)
	{
		leftTrackSpeed = fineControl(vexRT[Ch3]);
		rightTrackSpeed = fineControl(vexRT[Ch2]);
		
		sleep(20);
	}
}

//Controller for all motors
task motorController()
{
	
	motor[lDrive1] = motorRamping(leftTrackSpeed,motor[lDrive1],0);
	motor[lDrive2] = motorRamping(leftTrackSpeed,motor[lDrive2],1);
	motor[rDrive2] = motorRamping(rightTrackSpeed,motor[rDrive1],2);
	motor[rDrive1] = motorRamping(rightTrackSpeed,motor[rDrive2],3);

	motor[leftLift1] = leftLiftSpeed;
	motor[leftLift2] = leftLiftSpeed;
	motor[rightLift1] = rightLiftSpeed;
	motor[rightLift2] = rightLiftSpeed;

	sleep(20);
}
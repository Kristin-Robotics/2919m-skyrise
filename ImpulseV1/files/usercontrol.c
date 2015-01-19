#include "main.h"

//Fine Control for Driver
#include "/codebits/finecontrol.c"

//Buttons
#include "/codebits/buttons.c"

//Move the lift automatically
#include "/codebits/moveliftpreset.c"

//Slowly increase speed over speed/100 seconds
#include "/codebits/motorramping.c"

//Trim code
#include "/codebits/lifttrim.c"

//Compensation for skyrise weight code
#include "/codebits/liftcompensation.c"

//Processing for Lift
task liftProcessing()
{
	while(true)
	{
		moveLiftPreset(); //Has a while loop
		wait1Msec(50);
	}
}

task arcadeDrive()
{
	while(true)
	{
		leftTrackSpeed =(vexRT[Ch3] + vexRT[Ch1]); 
		//leftTrackSpeed = fineControl(vexRT[Ch3] + vexRT[Ch1]);
		rightTrackSpeed =(vexRT[Ch3] - vexRT[Ch1]); 
		//rightTrackSpeed = fineControl(vexRT[Ch3] - vexRT[Ch1]);

		wait1Msec(20);
	}

}

task tankDrive()
{
	while(true)
	{
		leftTrackSpeed =(vexRT[Ch3]); 
		//leftTrackSpeed = fineControl(vexRT[Ch3]);
		rightTrackSpeed =(vexRT[Ch2]); 
		//rightTrackSpeed = fineControl(vexRT[Ch2]);

		wait1Msec(20);
	}
}

//Controller for all motors
task motorController()
{
	while(true)
	{
			motor[lDrive1] += slopeLimiter(motor[lDrive1],leftTrackSpeed,20);
			motor[lDrive2] += slopeLimiter(motor[lDrive2],leftTrackSpeed,20);
			motor[rDrive2] += slopeLimiter(motor[rDrive2],rightTrackSpeed,20);
			motor[rDrive1] += slopeLimiter(motor[rDrive1],rightTrackSpeed,20);
			wait1Msec(RAMPDELAYMS);
	}
}


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
			if (vexRT[Btn7D] == 0)
			{
				if (driveMode == "tank")
				{
					StopTask(tankDrive);
					StartTask(arcadeDrive);
					driveMode = "arcade";
					driveModeButton = false;
				}
				else
				{
					StopTask(arcadeDrive);
					StartTask(tankDrive);
					driveMode = "tank";
					driveModeButton = false;
				}

			}
		}

		if ((vexRT[Btn5U] == 1)||(vexRT[Btn5D] == 1))
		{
			liftPreset = -1;
		}

		if (liftPreset == -1)
		{
			leftLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
			rightLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
			if (SensorValue[rPot] > 1800)
			{
				if ((leftLiftSpeed > 0) || (rightLiftSpeed > 0))
				{
					leftLiftSpeed = 0;
					rightLiftSpeed = 0;
				}
			}
		}
		
		liftCompensation();

		liftTrim();

		motor[leftLift1] = leftLiftSpeed;
		motor[leftLift2] = leftLiftSpeed;
		motor[leftLift3] = leftLiftSpeed;
		motor[rightLift1] = rightLiftSpeed;
		motor[rightLift2] = rightLiftSpeed;
		motor[rightLift3] = rightLiftSpeed;

		wait1Msec(20);
	}
}
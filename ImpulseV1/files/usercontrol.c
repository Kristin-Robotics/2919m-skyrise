#include "main.h"

//Drive modes for Driver
#include "/codebits/drivemodes.c"

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
		moveLiftAuton(); //Has a while loop
		wait1Msec(50);
	}
}

/* task driveProcessing()
{
	while(true)
	{
		buttonResponseXmitter2(); //Has a while loop
		wait1Msec(50);
	}
}

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
//Controller for all motors
task motorController()
{
	while(true)
	{
		motor[lDrive1] += slopeLimiter(motor[lDrive1],leftTrackSpeed,20);
		motor[lDrive2] += slopeLimiter(motor[lDrive2],leftTrackSpeed,20);
		motor[rDrive2] += slopeLimiter(motor[rDrive2],rightTrackSpeed,20);
		motor[rDrive1] += slopeLimiter(motor[rDrive1],rightTrackSpeed,20);

		motor[leftLift1] = leftLiftSpeed;
		motor[leftLift2] = leftLiftSpeed;
		motor[leftLift3] = leftLiftSpeed;
		motor[rightLift1] = rightLiftSpeed;
		motor[rightLift2] = rightLiftSpeed;
		motor[rightLift3] = rightLiftSpeed;

		wait1Msec(RAMPDELAYMS);
	}
}

//Controller interaction
task usercontrol()
{
	StartTask(liftProcessing);
	StartTask(motorController);

	while(true)
	{
		if (autonUser)
		{
			//getButtonInputXmitter2();
		}
		else
		{
			getButtonInput();

			buttonResponse();

			if (arcadeDriveMode)
			{
				arcadeDrive();
			}
			else
			{
				tankDrive();
			}

			if (liftPreset == -1)
			{
				leftLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
				rightLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
				setCompensation();

				if (SensorValue[rPot] > 1800)
				{
					if ((leftLiftSpeed > 0) || (rightLiftSpeed > 0))
					{
						leftLiftSpeed = 0;
						rightLiftSpeed = 0;
					}
				}
			}

			liftTrim();

			wait1Msec(20);
		}
	}
}

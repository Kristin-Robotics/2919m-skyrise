#include "main.h"

//Trim code
#include "/userfunctions/lifttrim.c"

//Compensation for skyrise weight code
#include "/userfunctions/liftcompensation.c"

//Drive modes for Driver
#include "/userfunctions/drivemodes.c"

//Fine Control for Driver
#include "/userfunctions/finecontrol.c"

//Buttons
#include "/userfunctions/buttons.c"

//Move the lift automatically
#include "/userfunctions/moveliftpreset.c"

//Slowly increase speed over speed/100 seconds
#include "/userfunctions/motorramping.c"

//Processing for Lift
task liftProcessing()
{
	while(true)
	{
		moveLiftPreset(); //Has a while loop
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
				if (firstrun)
				{
					leftLiftSpeed = (vexRT[Btn5U]*127) - (vexRT[Btn5D]*20);
					rightLiftSpeed = (vexRT[Btn5U]*127) - (vexRT[Btn5D]*20);
					setCompensation();
				}
				else
				{
					leftLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
					rightLiftSpeed = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
					setCompensation();
				}
				
				if (SensorValue[rPot] > rPotValues[1])
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

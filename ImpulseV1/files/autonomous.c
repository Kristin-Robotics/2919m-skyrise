#include "main.h"

//Trim code
#include "/codebits/lifttrim.c"

//Compensation for skyrise weight code
#include "/codebits/liftcompensation.c"

//sgn(-5) == -1
//sgn(5) == 1
//sgn(0) == 0

bool stepComplete[] = {false,false,false};
int step[] = {0,0,0};

void clearEncoders()
{
	nMotorEncoder[lDrive2] = 0;
	nMotorEncoder[rDrive2] = 0;
}

// moves the selected motors, used in the macros in definitions.h 
void move(int leftDriveOneSpeed = 127, int leftDriveTwoSpeed = leftDriveOneSpeed, int rightDriveOneSpeed = leftDriveOneSpeed, int rightDriveTwoSpeed = leftDriveOneSpeed, int stepArray = 0)
{
	while(stepComplete[stepArray] == true)
	{
		wait1Msec(20);
	}

	while ( !(stepComplete[stepArray]) )
	{
		motor[lDrive1] = leftDriveOneSpeed;
		motor[lDrive2] = leftDriveTwoSpeed;
		motor[rDrive1] = rightDriveOneSpeed;
		motor[rDrive2] = rightDriveTwoSpeed;
		wait1Msec(20);
	}

	motor[lDrive1] = round(-(leftDriveOneSpeed)/driveBrakeConstant);
	motor[lDrive2] = round(-(leftDriveTwoSpeed)/driveBrakeConstant);
	motor[rDrive1] = round(-(rightDriveOneSpeed)/driveBrakeConstant);
	motor[rDrive2] = round(-(rightDriveTwoSpeed)/driveBrakeConstant);
	wait1Msec(100);
	motor[lDrive1] = 0;
	motor[lDrive2] = 0;
	motor[rDrive1] = 0;
	motor[rDrive2] = 0;

	step[stepArray]++;

}

void lift(int liftSpeed = 127, int stepArray = 0)
{
	while(stepComplete[stepArray] == true)
	{
		wait1Msec(20);
	}
	
	proportionalSpeed = 1.0;
	
	while ( !(stepComplete[stepArray]) )
	{
		leftLiftSpeed = round(liftSpeed*proportionalSpeed);
		rightLiftSpeed = round(liftSpeed*proportionalSpeed);
		wait1Msec(20);
	}

	leftLiftSpeed = 0;
	rightLiftSpeed = 0;

	step[stepArray]++;

}

void skyrise(int value, int delay = 500, int stepArray = 0)
{
	while(stepComplete[stepArray] == true)
	{
		wait1Msec(20);
	}
	
	while ( !(stepComplete[stepArray]) )
	{
		wait1Msec(20);
	}
	wait1Msec(delay);
	SensorValue[skyPiston] = value;
	
	step[stepArray]++;
}

void intake(int value, int delay = 500, int stepArray = 0)
{
	while(stepComplete[stepArray] == true)
	{
		wait1Msec(20);
	}
	
	while ( !(stepComplete[stepArray]) )
	{
		wait1Msec(20);
	}
	wait1Msec(delay);
	SensorValue[needle] = value;
	
	step[stepArray]++;
}

void potentiometerCondition(int potValue, int stepArray = 0)
{
	int currentStep = step[stepArray];
	
	stepComplete[stepArray] = false;
	
	if (SensorValue[rPot] > potValue)
	{
		liftDirection = "up";
		while (SensorValue[rPot] > potValue)
		{
			proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling + 0.1;
			
			if (proportionalSpeed > 1)
			{
				proportionalSpeed = 1;
			}	
				
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	else if (SensorValue[rPot] < potValue)
	{
		liftDirection = "down";
		while (SensorValue[rPot] < potValue)
		{
			proportionalSpeed = abs(potRTarget - SensorValue[rPot])/proportionalSpeedScaling;
			
			if (proportionalSpeed > 1)
			{
				proportionalSpeed = 1;
			}
			
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	
	while (currentStep == step[stepArray])
	{
		wait1Msec(20);
	}
}

void ultrasonicCondition(int distance, bool LS = true, bool RS = true, int stepArray = 0)
{
	int currentStep = step[stepArray];
	stepComplete[stepArray] = false;

	if (LS && RS)
	{
		bool lSonicComplete = false;
		bool rSonicComplete = false;

		while (!lSonicComplete && !rSonicComplete)
		{
			if ((distance - SensorValue[sonicLeft]) < 0)
			{
				while(SensorValue[sonicLeft] > distance)
				{
					wait1Msec(20);
				}
				stepComplete[stepArray] = true;
			}

			else
			{
				while (SensorValue[sonicLeft] < distance)
				{
					wait1Msec(20);
				}
				stepComplete[stepArray] = true;
			}
		}
	}
	else if (LS)
	{
		if ((distance - SensorValue[sonicLeft]) < 0)
		{
			while (SensorValue[sonicLeft] > distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}

		else
		{
			while (SensorValue[sonicLeft] < distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}
	}

	else if (RS)
	{
		if ((distance - SensorValue[sonicRight]) < 0)
		{
			while (SensorValue[sonicRight] > distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}

		else
		{
			while (SensorValue[sonicRight] < distance)
			{
				wait1Msec(20);
			}
			stepComplete[stepArray] = true;
		}
	}
	while (currentStep == step[stepArray])
	{
		wait1Msec(20);
	}
}

void gyroCondition(int degree, bool stepArray = 0)
{
	int currentStep = step[stepArray];
	stepComplete[stepArray] = false;

	degree = degree * 10;

	if ((degree - SensorValue[turningGyro]) < 0)
	{
		while (SensorValue[turningGyro] > degree)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	else
	{
		while (SensorValue[turningGyro] < degree)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	
	while (currentStep == step[stepArray])
	{
		wait1Msec(20);
	}
}

void encoderCondition(int tickL2, int tickR2 = tickL2, int stepArray = 0)
{
	int currentStep = step[stepArray];
	stepComplete[stepArray] = false;
	clearEncoders();

	bool driveLBGoalReached = false;
	bool driveRBGoalReached = false;

	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)))
	{
		if (abs(nMotorEncoder[lDrive2]) > tickL2)
		{
			driveLBGoalReached=true;
		}

		if (abs(nMotorEncoder[rDrive2]) > tickR2)
		{
			driveRBGoalReached=true;
		}
	}
	stepComplete[stepArray] = true;
	while (currentStep == step[stepArray])
	{
		wait1Msec(20);
	}
}

void lineCondition(int stepArray = 0)
{
	int currentStep = step[stepArray];
	stepComplete[stepArray] = false;

	while (!((SensorValue[lineInnerL] < lineSensorThreshold)  && (SensorValue[lineInnerR] < lineSensorThreshold)))
	{
		wait1Msec(20);
	}
	stepComplete[stepArray] = true;
	while (currentStep == step[stepArray])
	{
		wait1Msec(20);
	}
}

void lightCondition(int threshold = 0, bool fromDark = false, int stepArray = 0)
{
	int currentStep = step[stepArray];
	stepComplete[stepArray] = false;
	
	if (fromDark)
	{
		while(SensorValue[skyLight] > threshold)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	else
	{
		while(SensorValue[skyLight] < threshold)
		{
			wait1Msec(20);
		}
		stepComplete[stepArray] = true;
	}
	while (currentStep == step[stepArray])
	{
		wait1Msec(20);
	}
}

void timeCondition (int delay, int stepArray = 0)
{
	int currentStep = step[stepArray];
	stepComplete[stepArray] = false;
	
	wait1Msec(delay);
	
	while (currentStep == step[stepArray])
	{
		wait1Msec(20);
	}
}

task liftHandle()
{
	while(true)
	{
		liftCompensation();
		
		liftTrim();
	
		motor[rightLift1] = rightLiftSpeed;
		motor[rightLift2] = rightLiftSpeed;
		motor[leftLift1] = leftLiftSpeed;
		motor[leftLift2] = leftLiftSpeed;
		
		wait1Msec(20);
	}
}

task conditional2()
{
	while(step[0] < 7)
	{
		wait1Msec(100);
	}
	potentiometerCondition(280,1);
	StopTask(conditional2);
}

task command2()
{
	while(step[0] < 7)
	{
		wait1Msec(100);
	}
	lift(-70,1);
	StopTask(command2);
}

task conditional1()
{
	gyroCondition(-45); //0
	
	lightCondition(230); //1
	potentiometerCondition(500); //2
	encoderCondition(600); //3
	potentiometerCondition(280); //4
	lightCondition(230); //5
	potentiometerCondition(500);//6
	encoderCondition(500); 
	//potentiometerCondition(280);
	lightCondition(230);
	
	potentiometerCondition(500);
	encoderCondition(600);
	potentiometerCondition(350);
	lightCondition(230);
}

task command1()
{
	move(-60,-60,60,60);
	
	leftLiftSpeed = 127;
	rightLiftSpeed = 127;
	wait1Msec(350);
	leftLiftSpeed = 0;
	rightLiftSpeed = 0;
	
	skyrise(0); //1
	lift(127); //2
	move(-60); //3
	lift(-70); //4
	skyrise(1); //5
	lift(127);
	move(60);
	//lift(-70);
	skyrise(0,2000);
	
	lift(127);
	move(-60);
	lift(-70);
	skyrise(1);
}

// autonomous task
task autonomous()
{
	firstRun = false;
	StartTask(liftHandle);
	StartTask(conditional1);
	StartTask(command1);
	StartTask(conditional2);
	StartTask(command2);
	//MissionImpossible();
}

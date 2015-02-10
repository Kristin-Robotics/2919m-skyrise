//motors
void setDrive(int LD1 = 127, int RD1 = LD1, int LD2 = LD1, int RD2 = RD1)
{
	motor[lDrive1] = LD1;
	motor[rDrive1] = RD1;
	motor[lDrive2] = LD2;
	motor[rDrive2] = RD2;
}

void setLift(int LL1 = 10, int RL1 = 10, int LL2 = LL1, int RL2 = RL1, int LL3 = LL1, int RL3 = RL1)
{
	motor[leftLift1] = LL1;
	motor[leftLift2] = LL2;
	motor[leftLift3] = LL3;
	motor[rightLift1] = RL1;
	motor[rightLift2] = RL2;
	motor[rightLift3] = RL3;
}

//Sensor Commands
void setEncoders(int encoderL = 0, int encoderR = encoderL)
{
	nMotorEncoder[lDrive2] = encoderL;
	nMotorEncoder[rDrive2] = encoderR;
}

void setSkyrise(int value)
{
	SensorValue[skyPiston] = value;
}

void setNeedle(int value)
{
	SensorValue[needle] = value;
}

//Sensor Conditionals
void potentiometerCondition(int value)
{
	value = abs(value);
	
	if (SensorValue[rPot] > value)
	{
		liftDirection = "up";
		while (SensorValue[rPot] > value)
		{
			wait1Msec(10);
		}
	}
	else if (SensorValue[rPot] < value)
	{
		liftDirection = "down";
		while (SensorValue[rPot] < value)
		{
			wait1Msec(10);
		}
	}
}
void encoderCondition(int encoderL, int encoderR = encoderL)
{
	encoderL = abs(encoderL);
	encoderR = abs(encoderR);
	
	setEncoders();

	bool driveLBGoalReached = false;
	bool driveRBGoalReached = false;

	while (((driveLBGoalReached == false)||(driveRBGoalReached == false)))
	{
		if (abs(nMotorEncoder[lDrive2]) > encoderL)
		{
			driveLBGoalReached=true;
		}

		if (abs(nMotorEncoder[rDrive2]) > encoderR)
		{
			driveRBGoalReached=true;
		}
		
		wait1Msec(10);
	}
}

void gyroCondition(int value)
{
	value = abs(value);
	
	while ((abs(SensorValue[turningGyro]) < value - 50) || (abs(SensorValue[turningGyro]) > value + 50))
	{
		wait1Msec(10);
	}
}

void ultrasonicCondition(int leftValue, int rightValue = leftValue)
{
	leftValue = abs(leftValue);
	rightValue = abs(rightValue);
	
	bool lSonicComplete = false;
	bool rSonicComplete = false;
}	
	
void lightCondition(int threshold = lightSensorThreshold, bool fromDark = false)
{
	if (fromDark)
	{
		while(SensorValue[skyLight] > threshold)
		{
			wait1Msec(10);
		}
	}
	else
	{
		while(SensorValue[skyLight] < threshold)
		{
			wait1Msec(10);
		}
	}
}

void timeCondition(int value)
{
	wait1Msec(value);
}
	
//Task Schedulers

void setStepStatus(int stepArray, bool stepStatus)
{
	stepComplete[stepArray] = stepStatus;
}

void setStep(int stepArray, int value = step[stepArray]++)
{
	step[stepArray] = value;
}

void waitForStepStatus(int stepArray, bool stepStatus)
{
	while(stepComplete[stepArray] == false)
	{
		wait1Msec(10);
	}
}

void waitForStep(int stepArray, int value = step[stepArray]++)
{
	while(step[stepArray] < value)
	{
		wait1Msec(10);
	}
}
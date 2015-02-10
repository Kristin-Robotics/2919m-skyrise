void setLiftComp(int LL1 = 10, int RL1 = 10, int LL2 = LL1, int RL2 = RL1, int LL3 = LL1, int RL3 = RL1)
{
	if (compensation == 1)
	{
		if (LL1 > 0)
		{
			LL1 = round(LL1*compensationFactor);
		}
		else
		{
			RL1 = round(RL1*compensationFactor);
		}
		if (LL2 > 0)
		{
			LL2 = round(LL2*compensationFactor);
		}
		else
		{
			RL2 = round(RL2*compensationFactor);
		}
		if (LL3 > 0)
		{
			LL3 = round(LL3*compensationFactor);
		}
		else
		{
			RL3 = round(RL3*compensationFactor);
		}
	}
	else if (compensation == -1)
	{
		if (LL1 > 0)
		{		
			RL1 = round(RL1*compensationFactor);
		}
		else
		{
			LL1 = round(LL1*compensationFactor);
		}
		if (LL2 > 0)
		{		
			RL2 = round(RL2*compensationFactor);
		}
		else
		{
			LL2 = round(LL2*compensationFactor);
		}
		if (LL3 > 0)
		{		
			RL3 = round(RL3*compensationFactor);
		}
		else
		{
			LL3 = round(LL3*compensationFactor);
		}
	}
	
	setLift(LL1,RL1,LL2,RL2,LL3,RL3);
}

void hardBrake(int LD1 = 127, int RD1 = LD1, int LD2 = LD1, int RD2 = RD1)
{
	setDrive(LD1/driveBrakeConstant, RD1/driveBrakeConstant, LD2/driveBrakeConstant, RD2/driveBrakeConstant);

	wait1Msec(100);

	setDrive(0);
}

void softBrake(int LD1 = 127, int RD1 = LD1, int LD2 = LD1, int RD2 = RD1)
{
	setDrive(LD1/(driveBrakeConstant*2), RD1/(driveBrakeConstant*2), LD2/(driveBrakeConstant*2), RD2/(driveBrakeConstant*2));

	wait1Msec(20);

	setDrive(0);
	
	wait1Msec(20);
	
	setDrive(LD1/(driveBrakeConstant*2), RD1/(driveBrakeConstant*2), LD2/(driveBrakeConstant*2), RD2/(driveBrakeConstant*2));
	
	wait1Msec(20);
	
	setDrive(0);
}

void setLiftTrim()
{
	setLift();
}

void nextStep(int stepArray)
{
	int value = step[stepArray]++;
	
	step[stepArray] = value;
}

void autoSetLiftFull(int stepArray, int value)
{
	setLift(value);
	waitForStepStatus(stepArray,true);
	setLiftTrim();
	nextStep(stepArray);
	waitForStepStatus(stepArray,false);
}

void autoSetLiftComp(int stepArray, int value)
{
	setLiftComp(value);
	waitForStepStatus(stepArray,true);
	setLiftTrim();
	nextStep(stepArray);
	waitForStepStatus(stepArray,false);
}

void autoSetDrive(int stepArray, int value)
{
	setDrive(value);
	waitForStepStatus(stepArray,true);
	softBrake(value);
	nextStep(stepArray);
	waitForStepStatus(stepArray,false);
}

void autoSetSkyrise(int stepArray, int value)
{
	waitForStepStatus(stepArray,true);
	setSkyrise(value);
	nextStep(stepArray);
	waitForStepStatus(stepArray,false);
}

void autoTimeCondition(int stepArray, int value)
{
	setStepStatus(stepArray,false);
	timeCondition(value);
	setStepStatus(stepArray,true);
	waitForStep(stepArray);
}

void autoPotentiometerCondition(int stepArray, int value)
{
	setStepStatus(stepArray,false);
	potentiometerCondition(value);
	setStepStatus(stepArray,true);
	waitForStep(stepArray);
}

void autoEncoderCondition(int stepArray, int encoderL, int encoderR = encoderL)
{
	setStepStatus(stepArray,false);
	encoderCondition(encoderL,encoderR);
	setStepStatus(stepArray,true);
	waitForStep(stepArray);
}
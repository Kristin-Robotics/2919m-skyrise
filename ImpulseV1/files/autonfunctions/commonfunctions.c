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
	LD1 = round(-(LD1)/(driveBrakeConstant*2));
	LD2 = round(-(LD2)/(driveBrakeConstant*2));
	RD1 = round(-(RD1)/(driveBrakeConstant*2));
	RD2 = round(-(RD2)/(driveBrakeConstant*2));
	
	setDrive(LD1,RD1,LD2,RD2);

	wait1Msec(200);

	setDrive(0,0,0,0);
	
	// wait1Msec(50);
	
	// setDrive(LD1,RD1,LD2,RD2);
	
	// wait1Msec(50);
	
	// setDrive(0);
}

void setLiftTrim()
{
	setLift();
}

void nextStep(int stepArray)
{
	int value = step[stepArray] + 1;
	
	step[stepArray] = value;
}

void autoSetLiftFull(int stepArray, int value)
{
	setLift(value,value,value,value,value,value);
	waitForStepStatus(stepArray,true);
	setLiftTrim();
	nextStep(stepArray);
	setStepStatus(stepArray,false);
}

void autoSetLiftComp(int stepArray, int value)
{
	setLiftComp(value,value,value,value,value,value);
	waitForStepStatus(stepArray,true);
	setLiftTrim();
	nextStep(stepArray);
	setStepStatus(stepArray,false);
}

void autoSetDriveFull(int stepArray, int value)
{
	setDrive(value,value,value,value);
	waitForStepStatus(stepArray,true);
	softBrake(value,value,value,value);
	nextStep(stepArray);
	setStepStatus(stepArray,false);
}

void autoSetSkyrise(int stepArray, int value, int delay = 0)
{
	waitForStepStatus(stepArray,true);
	wait1Msec(delay);
	setSkyrise(value);
	nextStep(stepArray);
	setStepStatus(stepArray,false);
}

void autoTimeCondition(int stepArray, int value)
{
	timeCondition(value);
	setStepStatus(stepArray,true);
	waitForStepStatus(stepArray,false);
}

void autoLightCondition(int stepArray)
{
	lightCondition();
	setStepStatus(stepArray,true);
	waitForStepStatus(stepArray,false);
}

void autoPotentiometerCondition(int stepArray, int value)
{
	potentiometerCondition(value);
	setStepStatus(stepArray,true);
	waitForStepStatus(stepArray,false);
}

void autoEncoderCondition(int stepArray, int encoderL, int encoderR = encoderL)
{
	encoderCondition(encoderL,encoderR);
	setStepStatus(stepArray,true);
	waitForStepStatus(stepArray,false);
}
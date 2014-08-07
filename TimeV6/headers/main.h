#ifndef MAIN_H_
#define MAIN_H_

typedef enum { DOWN, UP, LEFT, RIGHT, FORWARD, BACK } direction;

int changeSpeed(int speed)
{
	float buffer = (float)speed;
	return (int)(round(buffer * speedReductionVal));
}

void resetEncoders()
{
	encoder(dLF) = 0;
	encoder(dLB) = 0;
	encoder(dRF) = 0;
	encoder(dRB) = 0;
}

void clearPreviousErrors()
{
	for (int i = 0; i < 4; i++)
	{
		speedstepPreviousError[i] = 0;
	}
}

void initDrive()
{
	motor[dRB] = 80;
	motor[dLB] = 80;
	motor[dRF] = -40;
	motor[dLF] = -40;
	wait1Msec(1000);
	motor[dRB] = 0;
	motor[dLB] = 0;
	motor[dRF] = 0;
	motor[dLF] = 0;
}

#endif MAIN_H_
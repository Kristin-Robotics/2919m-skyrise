#include "main.h"

void initGyro()
{
	SensorType[turningGyro] = sensorNone;
	wait1Msec(500);
	SensorType[turningGyro] = sensorGyro;
	wait1Msec(2000);
	SensorScale[turningGyro] = 260;
	SensorFullCount[turningGyro] = 3600;
}

// Pre-autonomous function
void pre_auton()
{
	bStopTasksBetweenModes = true;
	initGyro();
	resetEncoders();
}
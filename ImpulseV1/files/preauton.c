#include "main.h"

void initialiseGyro()
{
	SensorType[turningGyro] = sensorNone;
	wait1Msec(500);
	SensorType[turningGyro] = sensorGyro;
	wait1Msec(2000);
	SensorScale[turningGyro] = 133;
  	SensorFullCount[turningGyro] = 3600;
}

// preauton task
void pre_auton()
{
	bStopTasksBetweenModes = true;
	initialiseGyro();
}
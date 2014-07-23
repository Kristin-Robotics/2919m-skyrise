#ifndef MAIN_H_
#define MAIN_H_

#include "definitions.h"

//Global Variables
const int ExponentialScalingValue = 5;
const int LiftStandardHeights[] = {1,1550,680,1140,1400,1500};
const int PotentiometerLimit = 1460;
const int TrimSwitch = 150;

bool SpeedstepDriveEnabled = false;
bool SpeedstepLiftEnabled = false;
bool ExponentialControlEnabled = true;
bool LiftPresetEnabled = true;
bool DriveActive = false;
bool LiftActive = false;

int DriveLF;
int DriveLB;
int DriveRF;
int DriveRB;

int LiftRU;
int LiftRD;
int LiftLU;
int LiftLD;

//Global Functions

void ClearEncoders()
{
	Encoder(LDF) = 0;
	Encoder(RDF) = 0;
	Encoder(LDB) = 0;
	nMotorEncoder[RDB] = 0;
}

void InitialiseDrive()
{
	DriveLB=80;
	DriveRB=80;
	DriveLF=-40;
	DriveRF=-40;
}

//Global Tasks

task AntiJam()
{
	if (DriveActive == true)
	{
	
	}
	
	if (LiftActive == true)
	{
	
	}
}

task PIDController()
{
	if (DriveActive == true)
	{
	
	}
	
	if (LiftActive == true)
	{
	
	}
}

#endif /* MAIN_H_ */
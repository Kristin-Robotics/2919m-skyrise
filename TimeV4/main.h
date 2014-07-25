#ifndef MAIN_H_
#define MAIN_H_

#include "definitions.h"

//Global Variables
const int ExponentialScalingValue = 5;
const int LiftLVal[] = {1,1550,680,1140,1400,1500};
const int LiftRVal[] = {1,1550,680,1140,1400,1500};
const int PotentiometerLimit = 1460;
const int TrimSwitch = 150;

bool SpeedstepDriveEnabled = false;
bool SpeedstepLiftEnabled = false;
bool ExponentialControlEnabled = true;
bool LiftPresetEnabled = true;
bool DriveActive = false;
bool LiftActive = false;

int LiftTargetValue[] = {0,0,0}; 

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
	motor[LDB]=80;
	motor[RDB]=80;
	motor[LDF]=-40;
	motor[RDF]=-40;
}

void LiftMonitor()
{
	if ((PotRTarget != 0) && (PotLTarget != 0))
	{
		if ((PotR-30 < PotRTarget) && (PotR+30 > PotRTarget))
		{
			motor[LLU] = 0;
			motor[LLD] = 0;
			motor[RLU] = 0;
			motor[RLD] = 0;
			
			PotRTarget = 0;
			PotLTarget = 0;
		}

		else
		{
			bool LLGoalReached = false;
			bool RLGoalReached = false;
			
			int Direction; //0 is down, 1 is up
			
			//Set lift to active
			LiftActive = true;
			
			while (((LLGoalReached == false) || (RLGoalReached == false)) && (LiftActive))
			{
				if (PotR < PotRTarget)
				{
					Direction = 1;
				}
				if (PotR > PotRTarget)
				{
					Direction = 0;
				}
				
				if (Direction == 1)
				{
					if (PotL > PotLTarget)
					{
						motor[LLU] = -LiftTargetSpeed;
						motor[LLD] = -LiftTargetSpeed;
					}
					else
					{
						motor[LLU] = 0;
						motor[LLD] = 0;
						PotLTarget = 0;
						LLGoalReached = true;
					}
					if (PotR > PotRTarget)
					{
						motor[RLU] = -LiftTargetSpeed;
						motor[RLD] = -LiftTargetSpeed;
					}
					else
					{
						motor[RLU] = 0;
						motor[RLD] = 0;
						PotRTarget = 0;
						RLGoalReached = true;
					}
				}
				
				if (Direction == 1)
				{
					if (PotL > PotLTarget)
					{
						motor[LLU] = LiftTargetSpeed;
						motor[LLD] = LiftTargetSpeed;
					}
					else
					{
						motor[LLU] = 0;
						motor[LLD] = 0;
						PotLTarget = 0;
						LLGoalReached = true;
					}
					if (PotR > PotRTarget)
					{
						motor[RLU] = LiftTargetSpeed;
						motor[RLD] = LiftTargetSpeed;
					}
					else
					{
						motor[RLU] = 0;
						motor[RLD] = 0;
						PotRTarget = 0;
						RLGoalReached = true;
					}
					
					EndTimeSlice();
				}
			}
				
			//Set lift to inactive
			LiftActive = false;
		}
	}
}

//Global Tasks

task AntiJam()
{
	int PreviousEncoderRDF;
	int PreviousEncoderLDF;
	int PreviousPotL;
	int PreviousPotR;

	while(true)
	{
		if (DriveActive == true)
		{
			
		}
		
		if (LiftActive == true)
		{
		
		}
		
		EndTimeSlice();
	}
}

task PIDController()
{
	while(true)
	{
		if (DriveActive == true)
		{
		
		}
		
		if (LiftActive == true)
		{
		
		}
		
		EndTimeSlice();
	}
}

task LiftController()
{
	while(true)
	{
		//Idle Actions
		if (PotLTarget == 0 && PotRTarget == 0)
		{
			if (PotR < TrimSwitch)
			{
				motor[LLU] = -30;
				motor[LLD] = -30;
				motor[RLU] = -30;
				motor[RLD] = -30;
			}
			else if (PotR > TrimSwitch)
			{
				motor[LLU] = 20;
				motor[LLD] = 20;
				motor[RLU] = 20;
				motor[RLD] = 20;
			}
		}
		//Non-Idle Actions
		else
		{
			LiftMonitor();
		}
		
		EndTimeSlice();
	}
}

#endif /* MAIN_H_ */
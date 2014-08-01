#ifndef MAIN_H_
#define MAIN_H_

#include "definitions.h"

//Global Variables
const int ExponentialScalingValue = 5;
const float speedReductionValue = 1.0; // normal speed as of now
const int LiftLVal[] = {1,1590,680,1140,1400,1500};
const int LiftRVal[] = {1,1724,680,1140,1400,1500};
const int PotentiometerLimit = 1460;
const int liftTrimSwitch = 150;
const int liftTrimSwitchEnabled = true;

bool SpeedstepDriveEnabled = false;
bool SpeedstepLiftEnabled = false;
bool ExponentialControlEnabled = true;
bool LiftPresetEnabled = true;
bool DriveActive = false;
bool LiftActive = false;

int LiftTargetValue[] = {0,0,0}; 

//Global Functions

// changes the speed to the set value in main.h
int reduceSpeed(int speed)
{
	float buffer = (float)speed; // to prevent truncation during multiplication
	return (int)(round(buffer * speedReductionValue)); //Better rounding using the macro
}

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
	int PreviousEncoderRDF = 0;
	int PreviousEncoderLDF = 0;
	int PreviousPotL = 0;
	int PreviousPotR = 0;

	while(true)
	{
		if ( (PreviousEncoderRDF == Encoder(RDF)) || (PreviousEncoderLDF == Encoder(LDF)) )
		{
			if (DriveActive)
			{
				DriveActive = false;
			}
		}
		else
		{
			PreviousEncoderRDF = Encoder(RDF);
			PreviousEncoderLDF = Encoder(LDF);
		}
		
		if ( (PreviousPotL == PotL) || (PreviousPotR == PotR) )
		{
			if (LiftActive)
			{
				LiftActive = false;
			}
		}
		else
		{
			PreviousPotL = PotL;
			PreviousPotR = PotR;
		}
		
		wait1Msec(1000);
		EndTimeSlice(); 
	}
}

task PIDController()
{
	while(true)
	{
		if (DriveActive)
		{
		
		}
		
		if (LiftActive)
		{
		
		}
		
		EndTimeSlice();
	}
}

task LiftController()
{
	while(true)
	{
		if (((LiftActive == false) && (liftTrimSwitchEnabled)) && (vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0) )
		{
			if ( (PotR < liftTrimSwitch) )
			{
				motor[LLU] = -10;
				motor[LLD] = -10;
				motor[RLU] = -10;
				motor[RLD] = -10;
			}
			else if ( (PotR > liftTrimSwitch) )
			{
				motor[LLU] = 10;
				motor[LLD] = 10;
				motor[RLU] = 10;
				motor[RLD] = 10;
			}
		
		}
		//Idle Actions
/* 		if ( (PotLTarget == 0 && PotRTarget == 0) && (liftTrimSwitchEnabled) )
		{

		} */
		//Non-Idle Actions
		if ( (PotLTarget != 0 && PotRTarget != 0) && (!liftTrimSwitchEnabled) )
		{
			LiftMonitor();
		}
		
		EndTimeSlice();
	}
}

#endif /* MAIN_H_ */
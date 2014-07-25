#include "main.h"

//User variables
int DriveLF;
int DriveLB;
int DriveRF;
int DriveRB;

int LiftL;
int LiftR;

int IntakeL;
int IntakeR;

int LiftPreset = 0;

//User functions
int ExponentialControl(int Input) //input from value, mod is set to driver preferences
{
	if (ExponentialControlEnabled == true)
	{
		int Sign = Input/abs(Input);

		Input = abs(Input);

		float ScalingValue = 127.0/(ExponentialScalingValue-1);
		float PercentMax = Input/127.0;
		float ExpModifier = (float)(pow(ExponentialScalingValue,PercentMax)-1);
		int Output = (int)round(ScalingValue*ExpModifier*Sign);
		return(Output);
	}
	else
	{
		return(Input);
	}
}

void PresetButtons()
{
	if (LiftPresetEnabled)
	{
		if (vexRT[Btn8U] == 1)
		{
			LiftPreset = 6;
		}
		if (vexRT[Btn8L] == 1)
		{
			LiftPreset = 5;
		}
		if (vexRT[Btn8R] == 1)
		{
			LiftPreset= 4;
		}
		if (vexRT[Btn8D] == 1)
		{
			LiftPreset= 3;
		}
		if (vexRT[Btn7U] == 1)
		{
			LiftPreset= 2;
		}
		if (vexRT[Btn7D] == 1)
		{
			LiftPreset= 1;
		}
		if (vexRT[Btn7L] == 1)
		{
		}
		if (vexRT[Btn7R] == 1)
		{
		}
	}
}
void PresetAssign()
{
	switch (LiftPreset)
	{
		case 1:
			if (PotR != LiftRVal[0])
			{
				PotLTarget = LiftLVal[0];
				PotRTarget = LiftRVal[0];
				LiftMonitor();
			}
			else
			{
				LiftPreset = 0;
				LiftActive = false;
			}
			break;
		case 2:
			if (PotR != LiftRVal[1])
			{
				PotLTarget = LiftLVal[1];
				PotRTarget = LiftRVal[1];
				LiftMonitor();
			}
			else
			{
				LiftPreset = 0;
				LiftActive = false;
			}
			break;
		case 3:
			if (PotR != LiftRVal[2])
			{
				PotLTarget = LiftLVal[2];
				PotRTarget = LiftRVal[2];
				LiftMonitor();
			}
			else
			{
				LiftPreset = 0;
				LiftActive = false;
			}
			break;
		case 4:
			if (PotR != LiftRVal[3])
			{
				PotLTarget = LiftLVal[3];
				PotRTarget = LiftRVal[3];
				LiftMonitor();
			}
			else
			{
				LiftPreset = 0;
				LiftActive = false;
			}
			break;
		case 5:
			if (PotR != LiftRVal[4])
			{
				PotLTarget = LiftLVal[4];
				PotRTarget = LiftRVal[4];
				LiftMonitor();
			}
			else
			{
				LiftPreset = 0;
				LiftActive = false;
			}
			break;
		case 6:
			if (PotR != LiftRVal[5])
			{
				PotLTarget = LiftLVal[5];
				PotRTarget = LiftRVal[5];
				LiftMonitor();
			}
			else
			{
				LiftPreset = 0;
				LiftActive = false;
			}
			break;
		default:
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	//Initialise user control
	StartTask(LiftController);
	StartTask(PIDController);
	PotRTarget = 0;
	PotLTarget = 0;
	
	while (true)
	{
	
	//Just need drive control here
	
		//Lift actions and assigning
		if ((abs(LiftL) > 0)||(abs(LiftR) > 0))
		{
			LiftPreset = 0;
			PotLTarget = 0;
			PotRTarget = 0;
			LiftActive = false;

			motor[LLD] = LiftL;
			motor[LLU] = LiftL;
			motor[RLD] = LiftR;
			motor[RLU] = LiftR;
		}
		else
		{
			if (LiftPreset != 0)
			{
				PresetAssign();
			}
		}
		
		wait1Msec(20);
	}
}
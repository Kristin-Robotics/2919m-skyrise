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

bool intakeUpPressed = false;
bool xmtr2Connected = false;

//User functions
int ExponentialControl(int Input) //input from value, mod is set to driver preferences
{
	if (ExponentialControlEnabled == true)
	{
		int Sign = Input / abs(Input);

		Input = abs(Input);

		float ScalingValue = 127.0 / (ExponentialScalingValue - 1);
		float PercentMax = Input / 127.0;
		float ExpModifier = (float)(pow(ExponentialScalingValue, PercentMax) - 1);
		int Output = (int)round(ScalingValue * ExpModifier * Sign);
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
		if (vexRT[Btn8U] == 1) // Btn8 for Goal Heights, High goal
		{
			LiftPreset = 6;
		}
		if (vexRT[Btn8L] == 1) // Medium-High Goal
		{
			LiftPreset = 5;
		}
		if (vexRT[Btn8R] == 1) // Medium-Low Goal
		{
			LiftPreset = 4;
		}
		if (vexRT[Btn8D] == 1)  //Low Goal
		{
			LiftPreset = 3;
		}
		if (vexRT[Btn7U] == 1)	//Maximum
		{
			LiftPreset = 2;
		}
		if (vexRT[Btn7D] == 1)	//Minimum
		{
			LiftPreset = 1;
		}
		if (vexRT[Btn7L] == 1)
		{
			if (xmtr2Connected == false)
			{
				SkyriseIntake = 0;//Closed
			}
		}
		if (vexRT[Btn7R] == 1)
		{
			if (xmtr2Connected == false)
			{
				SkyriseIntake = 1; //Open
			}
		}
		if (xmtr2Connected)
		{
			if (vexRT[Btn7LXmtr2] == 1)
			{
				SkyriseIntake = 0; //Closed
			}
			if (vexRT[Btn7RXmtr2] == 1)
			{
				SkyriseIntake = 1; //Open
			}
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
	PotRTarget = 0;
	PotLTarget = 0;
	LiftActive = false;
	
	while (true)
	{	
		// Moving and strafing actions
		DriveLF = vexRT[Ch3] + vexRT[Ch4];
		DriveLB = vexRT[Ch3] - vexRT[Ch4];
		DriveRF = vexRT[Ch3] - vexRT[Ch4];
		DriveRB = vexRT[Ch3] + vexRT[Ch4];

		// Turning actions
		DriveLF = DriveLF + vexRT[Ch1];
		DriveLB = DriveLB + vexRT[Ch1];
		DriveRF = DriveRF - vexRT[Ch1];
		DriveRB = DriveRB - vexRT[Ch1];

		// Scaling
		DriveLF = ExponentialControl(DriveLF);
		DriveLB = ExponentialControl(DriveLB);
		DriveRF = ExponentialControl(DriveRF);
		DriveRB = ExponentialControl(DriveRB);

		// Assigning
		motor[LDB] = DriveLB;
		motor[LDF] = DriveLF;
		motor[RDB] = DriveRB;
		motor[RDF] = DriveRF;

		//Lift Variable
		LiftL = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
		LiftR = (vexRT[Btn5U] - vexRT[Btn5D]) * 127;
		
		//Stuff to do with buttons
		//PresetButtons();
		if ((abs(LiftL) > 0)||(abs(LiftR) > 0))
		{
			LiftPreset = 0;
			PotLTarget = 0;
			PotRTarget = 0;
			LiftActive = false;
		}
		else
		{
			if (LiftPreset != 0)
			{
				//PresetAssign();
			}
		}
		
		if (LiftActive == false)
		{
			motor[LLD] = LiftL;
			motor[LLU] = LiftL;
			motor[RLD] = LiftR;
			motor[RLU] = LiftR;
		}
		
		// Roller Intake actions
		// up = 100, down = -80, both, -127
		// If up is pressed, power 15;
		if (vexRT[Btn6U] == 1 && vexRT[Btn6D] == 0)
		{
			IntakeL = 100;
			IntakeR = 100;
			intakeUpPressed = true;
		}
		else if (vexRT[Btn6U] == 0 && vexRT[Btn6D] == 1)
		{
			IntakeL = -80;
			IntakeR = -80;
			intakeUpPressed = true;
		}
		else if (vexRT[Btn6U] == 1 && vexRT[Btn6D] == 1)
		{
			IntakeL = -127;
			IntakeR = -127;
			intakeUpPressed = false;
		}
		else
		{
			if (intakeUpPressed)
			{
				IntakeL = 10;
				IntakeR = 10;
			}
		} 
		
		//Intake Assign
		motor[LIN] = IntakeL;
		motor[RIN] = IntakeR;

		wait1Msec(20);
	}
}
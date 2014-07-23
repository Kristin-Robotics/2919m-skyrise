#ifndef MAIN_H_
#define MAIN_H_

//Global Variables
bool SpeedstepDriveEnabled = false;
bool SpeedstepLiftEnabled = false;
bool ExponentialControlEnabled = true;
bool LiftPresetEnabled = true;
bool Interrupt = false;
const int ExponentialScalingValue = 5;
const int LiftStandardHeights[] = {1,1550,680,1140,1400,1500};
const int PotentiometerLimit = 1460;
const int TrimSwitch = 150;

int DriveLF;
int DriveLB;
int DriveRF;
int DriveRB;

int LiftRU;
int LiftRD;
int LiftLU;
int LiftLD;

//Global Functions


#endif /* MAIN_H_ */
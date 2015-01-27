#ifndef VARIABLES_H
#define VARIABLES_H

// configuration constants
bool firstRun = true;
const int driveBrakeConstant = 6; //auton drive
const int fineControlValue = 5;
const int proportionalSpeedScaling = 200;
const float compensationFactor = 0.8;
int lineSensorThreshold = (2220 - 150) / 2;
int liftTrimThreshold = 300;
float proportionalSpeed = 1.0; //for lift
int compensation = 0; //-1 left, 0 off, 1 right

// preset values
// structure: min, max
const int rPotValues[] = {285, 1600};
const int lPotValues[] = {502, 2352};

#define MAXRAMPSTEP 2
#define RAMPDELAYMS 10

int liftPreset = -1;
int potLTarget = 0;
int potRTarget = 0;
int skyClawState = 0;
int needleState = 0;
int leftTrackSpeed, rightTrackSpeed;
int leftLiftSpeed, rightLiftSpeed;
int tick[] = {0,0,0,0};

string liftDirection;

bool RLGoalReached, LLGoalReached;
bool driveModeButton = false;
bool arcadeDriveMode = false;
bool skyClawButton = false;
bool needleButton = false;

#endif VARIABLES_H
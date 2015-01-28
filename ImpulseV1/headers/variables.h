#ifndef VARIABLES_H
#define VARIABLES_H

// configuration constants
bool firstRun = true;
bool arcadeDriveMode = true;
const int driveBrakeConstant = 6; //auton drive
const int fineControlValue = 5;
const int proportionalSpeedScaling = 200;
const float compensationFactor = 0.95;
int lineSensorThreshold = (2220 - 150) / 2;
int liftTrimThreshold = 300;
float proportionalSpeed = 1.0; //for lift
int compensation = 0; //-1 left, 0 off, 1 right

// preset values
// structure: min, max
const int rPotValues[] = {285, 1600};
int lightSensorThreshold = 100;
int lightCalibrationValues[] = {0,0}

int liftPreset = -1;
int potLTarget = 0;
int potRTarget = 0;
int skyClawState = 0;
int needleState = 0;
bool RLGoalReached, LLGoalReached;
int leftTrackSpeed, rightTrackSpeed;
int leftLiftSpeed, rightLiftSpeed;
int liftTargetSpeed = 0;

string liftDirection;

bool driveModeButton = false;
bool skyClawButton = false;
bool needleButton = false;
bool calibrateLightButton = false;
int calibrateLightButtonCount = 0;

#endif VARIABLES_H
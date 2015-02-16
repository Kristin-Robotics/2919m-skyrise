#ifndef VARIABLES_H
#define VARIABLES_H

// configuration constants
bool firstRun = true;
bool arcadeDriveMode = true;
const int driveBrakeConstant = 4; //auton drive
const int fineControlValue = 5;
const int proportionalSpeedScaling = 200;
const float compensationFactor = 0.55;
int liftTrimThreshold = 300;
float proportionalSpeed = 1.0; //for lift
int compensation = 0; //-1 left, 0 off, 1 right

//Auton Task Schedulers
bool stepComplete[] = {false,false,false};
int step[] = {0,0,0};

// preset values
// structure: min, max , autoloader
const int rPotValues[] = {400, 2200, 500};

int lightSensorThreshold = 250;
int lightCalibrationValues[] = {0,0};

int liftPreset = -1;
int skyriseCounter = 0;
int potRTarget = 0;
int skyClawState = 0;
int needleState = 0;
int leftTrackSpeed, rightTrackSpeed;
int leftLiftSpeed, rightLiftSpeed;
int liftTargetSpeed = 0;

string liftDirection;

bool driveModeButton = false;
bool skyClawButton = false;
bool needleButton = false;
bool needleCtrlButton = false;
bool calibrateLightButton = false;
bool skyriseLiftButton = false;
int calibrateLightButtonCount = 0;

bool autonUser = false;
int autonUserStep = -1;

#endif VARIABLES_H
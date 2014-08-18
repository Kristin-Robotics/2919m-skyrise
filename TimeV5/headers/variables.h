#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "variables.h"

//Global Variables
const int expScalingVal = 5; //Change on driver request
const float speedReductionVal = 1.0; // normal speed as of now
const int liftLVal[] = {1,1530,1,777,1210,1520}; //Preset values for left lift

const int liftRVal[] = {1,1710,680,548,1025,1340}; //Preset values for right lift
const int liftTrimThreshold = 50; //Point where lift trim switches directions

int liftAutonVal[] = {0,0,0}; //Values for auton lift controllers to read [PotL,PotR,Speed]

bool liftTrimThresholdEnabled = true; //Switch for lift trim
bool speedstepDriveEnabled = false; //Switch for drive PID
bool speedstepLiftEnabled = false; //Switch for lift PID
bool expCtrlEnabled = true; //Switch for log drive
bool liftPresetsEnabled = true; //Switch for presets
bool driveActive = false; //Switch for auton drive
bool liftActive = false; //Switch for auton lift

//Initialise speedstep (PID) variables
int speedstepSpeed = 0;
int speedstepError = 0;
int speedstepIntegral = 0;
int speedstepDerivitive = 0;
int speedstepPreviousError[] = {0,0,0,0};

//User variables
int dLF;
int dLB;
int dRF;
int dRB;

int lL;
int lR;

int iL;
int iR;

#endif /* VARIABLES_H_ */
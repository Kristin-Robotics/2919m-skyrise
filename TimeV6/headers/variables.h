#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "variables.h"

// Constants
const int expScalingVal = 5;
const float speedReductionVal = 1.0; // normal as of now
const int liftLVal[] = { 1, 1530, 1, 777, 1210, 1520 }; //Preset values for left lift
const int liftRVal[] = { 1, 1710, 680, 548, 1025, 1340 }; // Preset values for right lift
const int liftTrimThreshold = 150;

int liftAutonVal[] = { 0, 0, 0 };
volatile int driveAutonVal = 0;

// Booleans
bool expScalingEnabled = true;
bool liftPresetsEnabled = true;
bool specialEffectsEnabled = true;
volatile bool driveActive = false;
volatile bool liftActive = false;
bool speedstepDriveEnabled = false;
bool speedstepLiftEnabled = false;
bool liftTrimThresholdEnabled = true;

// Speedstep
int speedstepSpeed = 0;
int speedstepError = 0;
int speedstepIntegral = 0;
int speedstepDerivitive = 0;
int speedstepPreviousError[] = { 0, 0, 0, 0 };

// Control variables
volatile int driveLF;
volatile int driveLB;
volatile int driveRF;
volatile int driveRB;

volatile int liftL;
volatile int liftR;

int intakeL;
int intakeR;

#endif VARIABLES_H_
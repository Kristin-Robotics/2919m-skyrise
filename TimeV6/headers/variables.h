#ifndef VARIABLES_H
#define VARIABLES_H

#include "variables.h"

// Constants
const int expScalingVal = 5;
const float speedReductionVal = 1.0; // normal as of now
const int liftLVal[] = { 1, 1530, 1, 777, 1210, 1520 }; //Preset values for left lift
const int liftRVal[] = { 1, 1710, 680, 548, 1025, 1340 }; // Preset values for right list

// Booleans
bool expScalingEnabled = true;
bool liftPresetEnabled = true;
bool driveActive = false;
bool liftActive = false;

// Control variables
int driveLF;
int driveLB;
int driveRF;
int driveRB;

int liftL;
int liftR;

int intakeL;
int intakeR;

#endif VARIABLES_H
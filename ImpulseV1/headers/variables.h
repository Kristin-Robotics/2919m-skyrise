#ifndef VARIABLES_H
#define VARIABLES_H

// configuration constants
const int fineControlValue = 5;
int lineSensorThreshold = (2220 - 150) / 2;
int liftTrimThreshold = 400;
float proportionalSpeed = 1.0; //for lift
const bool fineControlEnabled = true;

// preset values
// structure: min, max
const int rPotValues[] = {285, 1600};
const int lPotValues[] = {502, 2352};

#endif VARIABLES_H
#ifndef VARIABLES_H
#define VARIABLES_H

// configuration constants
const int fineControlValue = 5;
int lineSensorThreshold = (2220 - 150) / 2;
<<<<<<< HEAD
const bool exponentialControlEnabled = true;
const int liftTrimThreshold = 75;
=======
const bool fineControlEnabled = true;
>>>>>>> origin/ImpulseV1

// preset values
// structure: min, max
const int rPotValues[] = {645, 2322};
const int lPotValues[] = {502, 2352};

#endif VARIABLES_H
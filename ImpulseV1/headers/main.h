#ifndef MAIN_H
#define MAIN_H

// for representing directions later
typedef enum {NORTH, SOUTH, EAST, WEST, UP, DOWN} direction;
const ubyte kDelay = 25;
const float kP = 1.0;
const float kI = 0.5;
const float kD = 0.5;
const float kL = 50.0;

float error = 0.0;
float prevError = 0.0;
float p = 0.0;
float i = 0.0;
float d = 0.0;

/*
 * Method for returning the true value of the line sensors (hopefully).
 * This method is based off Harrison Freni's code (2150D robotics team)
 * For further inquries about the source of this code, talk to Marco.
 */
float lineSensorPID(bool innerLineMark)
{
	float lineSensorSpeed = 0;
	error = 200 - SensorValue[innerLineMark ? lineInnerL : lineInnerR];
	p = error;
	i = abs(i + error) < kL ? i + error : kL;
	d = error - prevError;
	lineSensorSpeed = p * kP + i * kI + d * kD;
	prevError = error;
	wait1Msec(kDelay);
	return lineSensorSpeed;
}

#endif MAIN_H
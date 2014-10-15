#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// maths functions
#define round(x) ((int)x)
#define abs(x) (x < 0 ? -x : x)

// movement macros
#define drive(x, y) (move(x, abs(y), abs(y), abs(y), abs(y)))
#define driveBack(x, y) (move(x, -abs(y), -abs(y), -abs(y), -abs(y)))
#define turnLeft(x, y) (move(x, -abs(y), -abs(y), abs(y), abs(y))
#define turnRight(x, y) (move(x, abs(y), abs(y), -abs(y), -abs(y)))

#endif DEFINITIONS_H
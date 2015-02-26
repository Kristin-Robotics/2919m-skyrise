#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// maths functions
#define round(x) ((int)((x)>=0?(long)((x)+0.5):(long)((x)-0.5)))

// movement macros
// #define drive(x, y) (move(x, abs(y), abs(y), abs(y), abs(y)))
// #define driveBack(x, y) (move(x, -abs(y), -abs(y), -abs(y), -abs(y)))
// #define turnLeft(x, y) (move(x, -abs(y), -abs(y), abs(y), abs(y))
// #define turnRight(x, y) (move(x, abs(y), abs(y), -abs(y), -abs(y)))
//lift macros
// #define liftUp(x) (lift(127, x))
// #define liftDown(x) (lift(-127, x))

//Motor Ramping
#define MAXRAMPSTEP 2
#define RAMPDELAYMS 10

#endif DEFINITIONS_H
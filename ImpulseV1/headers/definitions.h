#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// maths functions
#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
//#define abs(x) (x < 0 ? -x : x) already has inbuilt function

// movement macros
#define drive(x, y) (move(x, abs(y), abs(y), abs(y), abs(y)))
#define driveBack(x, y) (move(x, -abs(y), -abs(y), -abs(y), -abs(y)))
#define turnLeft(x, y) (move(x, -abs(y), -abs(y), abs(y), abs(y))
#define turnRight(x, y) (move(x, abs(y), abs(y), -abs(y), -abs(y)))

// lift macros
#define liftUp(x) (lift(127, x))
#define liftDown(x) (lift(-127, x))

#endif DEFINITIONS_H
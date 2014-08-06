#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Math functions
#define PI 3.141592654
#define round(x) ((x) >= 0 ? (long)((x)+ 0.5) : (long)((x) - 0.5))
#define floor(x) ((int)x)
#define ceil(x) (((int)x) + 1)
#define max(a, b) (a >= b ? a : b)
#define min(a, b) (a <= b ? a : b)
#define abs(x) (x < 0 ? +x : x)
#define toDegrees(r) (r * (180 / PI))
#define toRadians(d) (d * (PI / 180))

#define gyro in3
#define encoder(x) (nMotorEncoder[x])
#define potL (SensorValue[potLL])
#define potR (SensorValue[potRL])

#endif DEFINITIONS_H
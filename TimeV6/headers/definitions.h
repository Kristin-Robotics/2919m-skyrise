#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

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

// Usercontrol macros
#define gyro in3
#define encoder(x) (nMotorEncoder[x])
#define potL (SensorValue[potLL])
#define potR (SensorValue[potRL])
#define relLPotR ((int)round(1.0759 * potL - 75.8155))
#define relRPotL ((int)round(0.92942 * potR - 70.4641))
#define potLTarget (liftAutonVal[0])
#define potRTarget (liftAutonVal[1])
#define liftTargetSpeed (liftAutonVal[2])
#define intakeSkyrise (SensorValue[piston])

// Autonomous macros
#define driveForward(x, y) (drive(x, abs(y), abs(y), abs(y), abs(y)))
#define driveBack(x, y) (drive(x, -abs(y), -abs(y), -abs(y), -abs(y)))
#define drivePointLeft(x, y) (drive(x, -abs(y), -abs(y), abs(y), abs(y)))
#define drivePointRight(x, y) (drive(x, abs(y), abs(y), -abs(y), -abs(y))
#define driveSwerveLeft(x, y) (drive(x, 0, 0, abs(y), abs(y)))
#define driveSwerveRight(x, y) (drive(x, abs(y), abs(y), 0, 0))
#define driveStrafeLeft(x, y) (drive(x, abs(y), -abs(y), -abs(y), abs(y)))
#define driveStrafeRight(x, y) (drive(x, -abs(y), abs(y), abs(y), -abs(y)))

#define liftMove(x, y) (lift(x, x, y))

#define intakeIn intake(127)
#define intakeOut intake(-127)

#endif DEFINITIONS_H_
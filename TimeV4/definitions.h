#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#define Gyro in3
#define Encoder(x) (nMotorEncoder[x])

#define DriveStraightForward(x,y) Drive(x,abs(y),abs(y),abs(y),abs(y))
#define DriveStraightBack(x,y) Drive(x,-abs(y),-abs(y),-abs(y),-abs(y))
#define DrivePointTurnLeft(x,y) Drive(x,-abs(y),-abs(y),abs(y),abs(y))
#define DrivePointTurnRight(x,y) Drive(x,abs(y),abs(y),-abs(y),-abs(y))
#define DriveSwerveTurnLeft(x,y) Drive(x,0,0,abs(y),abs(y))
#define DriveSwerveTurnRight(x,y) Drive(x,abs(y),abs(y),0,0)

#endif /* DEFINITIONS_H_ */
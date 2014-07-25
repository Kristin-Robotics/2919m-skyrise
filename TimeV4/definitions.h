#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#define Gyro in3
#define Encoder(x) (nMotorEncoder[x])
#define PotL (SensorValue[PotentiometerLL])
#define PotR (SensorValue[PotentiometerRL])
#define PotLTarget (LiftTargetValue[0])
#define PotRTarget (LiftTargetValue[1])
#define LiftTargetSpeed (LiftTargetValue[2])

#define DriveStraightForward(x,y) Drive(x,abs(y),abs(y),abs(y),abs(y))
#define DriveStraightBack(x,y) Drive(x,-abs(y),-abs(y),-abs(y),-abs(y))
#define DrivePointTurnLeft(x,y) Drive(x,-abs(y),-abs(y),abs(y),abs(y))
#define DrivePointTurnRight(x,y) Drive(x,abs(y),abs(y),-abs(y),-abs(y))
#define DriveSwerveTurnLeft(x,y) Drive(x,0,0,abs(y),abs(y))
#define DriveSwerveTurnRight(x,y) Drive(x,abs(y),abs(y),0,0)
#define DriveStrafeLeft(x,y) Drive(x,abs(y),-abs(y),-abs(y),abs(y))
#define DriveStrafeRight(x,y) Drive(x,-abs(y),abs(y),abs(y),-abs(y))

#define LiftMove(x,y) Lift(x,x,y)

#define IntakeIn Intake(127)
#define IntakeOut Intake(-127)



#endif /* DEFINITIONS_H_ */
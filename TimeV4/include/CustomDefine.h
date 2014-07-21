/*
 * CustomDefine.h
 *
 *  Created on: 22 Jul 2014
 *      Author: lich
 */

#ifndef CUSTOMDEFINE_H_
#define CUSTOMDEFINE_H_

//Motor reversals and shorthand done here
#define SetMotorRDF(x) (motorSet(1,x))
#define SetMotorRDB(x) (motorSet(2,x))
#define SetMotorLLU(x) (motorSet(3,x))
#define SetMotorLLD(x) (motorSet(4,x))
#define SetMotorRLU(x) (motorSet(5,x))
#define SetMotorRLD(x) (motorSet(6,x))
#define SetMotorRIN(x) (motorSet(7,x))
#define SetMotorLIN(x) (motorSet(8,x))
#define SetMotorLDB(x) (motorSet(9,x))
#define SetMotorLDF(x) (motorSet(10,x))

//Encoder shorthands
#define EncoderRDB 0
#define EncoderRDF 1
#define EncoderLDF 2
#define EncoderLDB 3

//Analog port shorthands
#define PotentiometerLL 1
#define PotentiometerRL 2

//Rounding
#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#endif /* CUSTOMDEFINE_H_ */

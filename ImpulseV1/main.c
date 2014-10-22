#pragma config(Sensor, in1,	rPot,		sensorPotentiometer)
#pragma config(Sensor, in2, lPot,		sensorPotentiometer)
#pragma config(Sensor, in3, lineInnerL, sensorLineFollower)
#pragma config(Sensor, in4, lineInnerR, sensorLineFollower)
#pragma config(Sensor, in5, lineOuterL, sensorLineFollower)
#pragma config(Sensor, in6, lineOuterR, sensorLineFollower)
#pragma config(Motor, port1,	,		tmotorVex393, openLoop)
#pragma config(Motor, port2,	lDrive1,	tmotorVex393HighSpeed, openLoop)
#pragma config(Motor, port3,	lDrive2,	tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port6,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port7,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port8,           rDrive2,       tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port9,           rDrive1,       tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port10,           ,             tmotorVex393, openLoop)

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

// Include headers
#include "/headers/definitions.h"

#include "/headers/main.h"

#include "/headers/variables.h"

// Include files
#include "Vex_Competition_Includes.c" // Do not modify

#include "/files/usercontrol.c"

#include "/files/autonomous.c"

#include "/files/preauton.c"

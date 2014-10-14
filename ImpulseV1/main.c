#pragma config(Sensor, in1,	rPot,		sensorPotentiometer)
#pragma config(Sensor, in2, lPot,		sensorPotentiometer)
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
#include 'definitions.h'

#include 'main.h'

#include 'variables.h'

// Include files
#include "Vex_Competition_Includes.c" // Do not modify

#include "usercontrol.c"

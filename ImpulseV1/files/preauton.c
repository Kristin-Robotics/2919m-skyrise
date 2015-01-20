#include "main.h"

void initialiseGyro()
{
	SensorType[turningGyro] = sensorNone;
	wait1Msec(500);
	SensorType[turningGyro] = sensorGyro;
	wait1Msec(2000);
	SensorScale[turningGyro] = 133;
  	SensorFullCount[turningGyro] = 3600;
}

void initialiseCompensationMonitor()
{
	if ((SensorValue[compensationMonitor] > 0) && (SensorValue[compensationMonitor] <= 1500))
	{
		compensation = 0;
	}
	else if ((SensorValue[compensationMonitor] > 1500) && (SensorValue[compensationMonitor] <= 3000))
	{
		compensation = 0;
	}
	else
	{
		compensation = 0;
	}	
}

void MissionImpossible()
{
  //        100 = Tempo
  //          6 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  988,    7); wait1Msec(  75);  // Note(E, Duration(32th))
  PlayTone( 1047,    7); wait1Msec(  75);  // Note(F, Duration(32th))
  PlayTone( 1109,    7); wait1Msec(  75);  // Note(F#, Duration(32th))
  PlayTone( 1175,    7); wait1Msec(  75);  // Note(G, Duration(32th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  880,  108); wait1Msec(1200);  // Note(D, Duration(Half))
  PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  831,  108); wait1Msec(1200);  // Note(C#, Duration(Half))
  PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  784,  108); wait1Msec(1200);  // Note(C, Duration(Half))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  932,   14); wait1Msec( 150);  // Note(A#5, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  return;
}

// preauton task
void pre_auton()
{
	bStopTasksBetweenModes = true;
	initialiseGyro();
	initialiseCompensationMonitor();
}

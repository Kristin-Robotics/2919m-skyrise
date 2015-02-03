#include "main.h"

void initialiseGyro()
{
	SensorType[turningGyro] = sensorNone;
	wait1Msec(500);
	SensorType[turningGyro] = sensorGyro;
	wait1Msec(1000);
	SensorScale[turningGyro] = 133;
  	SensorFullCount[turningGyro] = 3600;
}

void setCompensation()
{
	if ((SensorValue[compensationMonitor] > 0) && (SensorValue[compensationMonitor] <= 920))
	{
		compensation = -1;
	}
	else if ((SensorValue[compensationMonitor] > 1190) && (SensorValue[compensationMonitor] <= 2580))
	{
		compensation = 0;
	}
	else
	{
		compensation = 1;
	}
}

void calibrateLightSensor()
{
	if ((SensorValue[calibrateLight] == 0) && (calibrateLightButton == false))
	{
		calibrateLightButton = true;
		calibrateLightButtonCount++;
	}
	else
	{
		if (calibrateLightButton)
		{
			calibrateLightButton = false;

			if (calibrateLightButtonCount == 1)
			{
				PlayTone( 1175,   14); wait1Msec( 300);  // Calibration Mode
				PlayTone( 1175,   14); wait1Msec( 300);  // Calibration Mode

				lightCalibrationValues[0] = SensorValue[skyLight];
			}
			else if (calibrateLightButtonCount == 2)
			{
				PlayTone( 1175,   14); wait1Msec( 300);  // Calibration Mode
				PlayTone( 1175,   14); wait1Msec( 300);  // Calibration Mode
				PlayTone( 1175,   14); wait1Msec( 300);  // Calibration Mode

				lightCalibrationValues[1] = SensorValue[skyLight];

				lightSensorThreshold = (lightCalibrationValues[1] + lightCalibrationValues[0])/2;

				calibrateLightButtonCount = 0;

				PlayTone(  784,   14); wait1Msec( 300);  // Exit Calibration
			}
		}
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

void surprise()
{
  //        200 = Tempo
  //          5 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //
  PlayTone(  783,   27); wait1Msec( 300);  // Note(G)
  PlayTone(  880,   27); wait1Msec( 300);  // Note(A)
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C6, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  988,   27); wait1Msec( 300);  // Note(E6)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  988,   27); wait1Msec( 300);  // Note(E6)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  880,   41); wait1Msec( 450);  // Note(D6, Duration(Quarter .))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  783,   14); wait1Msec( 150);  // Note(G, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C6, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  880,   27); wait1Msec( 300);  // Note(D6)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  880,   27); wait1Msec( 300);  // Note(D6)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  784,   27); wait1Msec( 300);  // Note(C6)
  PlayTone(  987,   14); wait1Msec( 150);  // Note(B, Duration(Eighth))
  PlayTone(  880,   41); wait1Msec( 450);  // Note(A, Duration(Quarter .))
  PlayTone(  783,   14); wait1Msec( 150);  // Note(G, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C6, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  784,   54); wait1Msec( 600);  // Note(C6, Duration(Half))
  PlayTone(  880,   27); wait1Msec( 300);  // Note(D6)
  PlayTone(  987,   27); wait1Msec( 300);  // Note(B)
  PlayTone(  880,   27); wait1Msec( 300);  // Note(A)
  PlayTone(  783,   41); wait1Msec( 450);  // Note(G, Duration(Quarter .))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  783,   27); wait1Msec( 300);  // Note(G)
  PlayTone(  880,   54); wait1Msec( 600);  // Note(D6, Duration(Half))
  PlayTone(  784,   81); wait1Msec( 900);  // Note(C6, Duration(Half .))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest)
  PlayTone(  783,   14); wait1Msec( 150);  // Note(G, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C6, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  988,   27); wait1Msec( 300);  // Note(E6)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  988,   27); wait1Msec( 300);  // Note(E6)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  880,   41); wait1Msec( 450);  // Note(D6, Duration(Quarter .))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest)
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  783,   14); wait1Msec( 150);  // Note(G, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C6, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone( 1175,   54); wait1Msec( 600);  // Note(G6, Duration(Half))
  PlayTone(  987,   27); wait1Msec( 300);  // Note(B)
  PlayTone(  784,   41); wait1Msec( 450);  // Note(C6, Duration(Quarter .))
  PlayTone(  987,   14); wait1Msec( 150);  // Note(B, Duration(Eighth))
  PlayTone(  880,   27); wait1Msec( 300);  // Note(A)
  PlayTone(  783,   14); wait1Msec( 150);  // Note(G, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C6, Duration(Eighth))
  PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(Eighth))
  PlayTone(  784,   54); wait1Msec( 600);  // Note(C6, Duration(Half))
  PlayTone(  880,   27); wait1Msec( 300);  // Note(D6)
  PlayTone(  987,   27); wait1Msec( 300);  // Note(B)
  PlayTone(  880,   27); wait1Msec( 300);  // Note(A)
  PlayTone(  783,   41); wait1Msec( 450);  // Note(G, Duration(Quarter .))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(Eighth))
  PlayTone(  783,   27); wait1Msec( 300);  // Note(G)
  PlayTone(  880,   54); wait1Msec( 600);  // Note(D6, Duration(Half))
  PlayTone(  784,   54); wait1Msec( 600);  // Note(C6, Duration(Half))
  return;
}



// preauton task
void pre_auton()
{
	bStopTasksBetweenModes = true;

	//initialisation
	initialiseGyro();

	PlayTone( 1175,   14); wait1Msec( 300);  // Initialisation Complete

	// while(true)
	// {
		setCompensation();
		calibrateLightSensor();
	// }
}

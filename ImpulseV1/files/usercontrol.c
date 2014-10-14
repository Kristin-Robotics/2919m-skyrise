#include "main.h"

task usercontrol()
{
	int leftTrackSpeed;
	int rightTrackSpeed;

	while (true)
	{
		// getting values
		leftTrackSpeed = vexRT[Ch3];
		rightTrackSpeed = vexRT[Ch2];

		// assigning values
		motor[lDrive1] = leftTrackSpeed;
		motor[lDrive2] = leftTrackSpeed;
		motor[rDrive2] = rightTrackSpeed;
		motor[rDrive1] = rightTrackSpeed;
	}
}
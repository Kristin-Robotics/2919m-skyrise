void arcadeDrive()
{
	leftTrackSpeed =(vexRT[Ch3] + vexRT[Ch1]); 
	rightTrackSpeed =(vexRT[Ch3] - vexRT[Ch1]); 
}

void tankDrive()
{
	leftTrackSpeed =(vexRT[Ch3]); 
	rightTrackSpeed =(vexRT[Ch2]);
}
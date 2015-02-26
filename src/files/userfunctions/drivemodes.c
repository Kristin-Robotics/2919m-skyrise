void arcadeDrive()
{
	if (firstrun)
	{
		leftTrackSpeed =round((vexRT[Ch3] + vexRT[Ch1])*0.7); 
		rightTrackSpeed =round((vexRT[Ch3] - vexRT[Ch1])*0.7); 
	}
	else
	{
		leftTrackSpeed =(vexRT[Ch3] + vexRT[Ch1]); 
		rightTrackSpeed =(vexRT[Ch3] - vexRT[Ch1]); 
	}	
}

void tankDrive()
{
	leftTrackSpeed =(vexRT[Ch3]); 
	rightTrackSpeed =(vexRT[Ch2]);
}
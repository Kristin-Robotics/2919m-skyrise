short const LDR = 0, RDR = 1, LIF = 2;
short mots[3] = {0, 0, 0};
bool manualLift = true;
short armVal = SensorValue[rPot];

task secondaryControl() {
	short lift = 0;
	while (true) {
		motor[lDrive1] = mots[LDR];
		motor[lDrive2] = mots[LDR];
		
		motor[rDrive1] = mots[RDR];
		motor[rDrive2] = mots[RDR];
		
		if (manualLift) {
			lift = mots[LIF];
		} else {
			lift = (armVal - SensorValue[rPot]) + 20;
		}
		
		motor[leftLift1] = lift;
		motor[leftLift2] = lift;
		motor[leftLift3] = lift;
		motor[rightLift1] = lift;
		motor[rightLift2] = lift;
		motor[rightLift3] = lift;
		
		wait1Msec(2);
	}
}

void resetArmVal() {
	armVal = SensorValue[rPot];
	manualLift = false;
}

void waitForArmVal() {
	manualLift = false;
	while(abs(armVal - SensorValue[rPot]) > 30) { }
	
	wait1Msec(700);
}

void driveTime(short time, short left = 100, short right = left) {
	mots[LDR] = left;
	mots[RDR] = right;
	wait1Msec(time);
	mots[LDR] = 0;
	mots[RDR] = 0;
	wait1Msec(300);
}

void driveEncoder(short distance, short left = 100, short right = left) {
	mots[LDR] = left;
	mots[RDR] = right;
	
	nMotorEncoder[lDrive2] = 0;
	
	while(abs(nMotorEncoder[lDrive2]) < abs(distance)) { }
	
	mots[LDR] = 0;
	mots[RDR] = 0;
	wait1Msec(300);
}
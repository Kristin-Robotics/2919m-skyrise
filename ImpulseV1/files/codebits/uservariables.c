#define MAXRAMPSTEP 2
#define RAMPDELAYMS 10

int liftPreset = -1;
int potLTarget = 0;
int potRTarget = 0;
int leftLiftSpeed, rightLiftSpeed;
int leftTrackSpeed, rightTrackSpeed;
int tick[] = {0,0,0,0};
string driveMode = "tank";
string liftDirection;
bool driveModeButton = false;
bool RLGoalReached, LLGoalReached;

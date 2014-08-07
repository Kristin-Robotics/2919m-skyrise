#include "main.h"

typedef struct {
	int frequency;
	int duration;
} sound;

// Its the final countdown sound array. DO NOT TOUCH!!!
const sound finalCountdown[72] = { 
	{ 220, 100 }, { 0, 50 }, { 523, 25 }, { 493, 25 }, {440, 100},
	{ 261, 100 }, { 174, 100 }, { 0, 50 }, { 587, 25 }, {523, 25},
	{ 587, 50 }, { 523, 50 }, { 493, 100 }, { 293, 100 }, {0, 50},
	{ 587, 25 }, { 523, 25 }, { 493, 100 }, { 293, 100 }, { 196, 100 }, 
	{ 0, 50 }, { 493, 25 }, { 440, 25 }, { 493, 50 }, { 440, 50 }, 
	{ 392, 50 }, { 440, 50 }, { 220, 100 }, { 0, 50 }, { 523, 25 }, 
	{ 493, 25 }, { 440, 100 }, { 261, 100 }, { 174, 100 }, { 0, 50 }, 
	{ 587, 25 }, { 523, 25 }, { 587, 50 }, { 523, 50 }, { 493, 100 }, 
	{ 293, 100 }, { 0, 50 }, { 587, 25 }, { 523, 25 }, { 493, 100 },
	{ 293, 100 }, { 196, 100 },	{ 0, 50 }, { 493, 25 }, { 440, 25 },
	{ 493, 50 }, { 440, 50 }, { 392, 50 }, { 440, 50 }, {349, 100},
	{ 392, 25 }, { 440, 25 }, { 493, 100 }, { 440, 25 }, {493, 25},
	{ 523, 50 }, { 493, 50 }, { 440, 50 }, { 392, 50 }, {349, 100},
	{ 440, 100 }, { 392, 200 }, { 523, 50 }, { 587, 50 }, {523, 50},
	{ 493, 50 }, {392, 400}
};

task playMusic()
{
	if (specialEffectsEnabled)
	{
		int index = 0;
		while (true)
		{
			if (finalCountdown[index].frequency != 0)
			{
				PlayTone(finalCountdown[index].frequency, finalCountdown[index].duration);
			}
			else
			{
				wait1Msec(finalCountdown[index].duration * 10);
			}
			index++;
			if (index > 72)
			{
				index = 0;
			}
		}
	}
}
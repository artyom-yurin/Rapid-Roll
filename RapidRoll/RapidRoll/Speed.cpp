#include "stdafx.h"
#include "Player.h"
#include "Speed.h"

float MAX_SPEED = 0.3;
float MIN_SPEED = 0.1;
int COEFFICIENT = 10000;

float GetNewSpeed(float score, bool isBig)
{
	float newSpeed = MIN_SPEED + score / COEFFICIENT;
	if (isBig)
	{
		newSpeed *= 1.5;
	}
	newSpeed = std::min(MAX_SPEED, newSpeed);
	return newSpeed;
}

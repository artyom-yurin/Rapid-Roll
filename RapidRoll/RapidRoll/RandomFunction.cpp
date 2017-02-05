#include "stdafx.h"
#include "RandomFunction.h"

int GetRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> uniform_dist(min, max);
	return uniform_dist(engine);
}
#include "plane.h"

void Plane::CalculateP()
{
	P = (float)(std::rand() % 10) / 10;
}

bool Plane::getShooot(float p1)
{
	float chance = 1 - pow(1 - (1 - p1) * P, 2);
	if (chance >= 0.8) isShotDown = true;
	return isShotDown;
}

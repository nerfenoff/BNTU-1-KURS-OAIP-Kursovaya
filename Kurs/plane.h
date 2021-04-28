#pragma once

#include <iostream>

class Plane
{
	float P;
public:
	bool isShotDown;
	Plane() { P = 0.0f; isShotDown = false; };
	~Plane() {};

	/// <summary>
	/// Calculates P for the aircraft
	/// </summary>
	void CalculateP();
	/// <summary>
	/// Calculates the probability of hitting the aircraft
	/// </summary>
	/// <param name="p1">- The probability of hitting an enemy aircraft</param>
	/// <returns>Returns the current state of the aircraft</returns>
	bool getShooot(float p1);
	float GetP() { return P; }
};


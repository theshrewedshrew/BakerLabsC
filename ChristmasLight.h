/*
Programmer:			Michael Schmoyer
Date Completed:		11/30/03
Project:			Programming Assignment 10
					Fall 2003
					CSI 1430
*/

#ifndef CHRISTMASLIGHT_H
#define CHRISTMASLIGHT_H

#include <string>
#include <cmath>

using namespace std;

class ChristmasLight
{
private:

	string color;
	float wattage;
	float maxTime;
	float timeUsed;
	bool burnedOut;		//true if timeUsed > maxTime

public:

	//Constructor
	ChristmasLight();	

	//Public Set Functions
	void SetColor(string);
	void SetWattage(float);
	void SetMaxTime(float);
	void SetTimeUsed(float);

	//Public Get Functions
	float GetTemperature();		//Set to 70.0 if burnedOut = true
	bool IsBurnedOut();
	string GetColor();
	string PrintStatus();
};

#endif

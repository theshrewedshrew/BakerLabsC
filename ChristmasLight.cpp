/*
Programmer:			Michael Schmoyer
Date Completed:		11/30/03
Project:			Programming Assignment 10
					Fall 2003
					CSI 1430
*/

#include "ChristmasLight.h"

ChristmasLight::ChristmasLight()
{
	//Constructor: Initilize all christmas light variables
	color =			"red";
	wattage =		0;
	maxTime =		100;
	timeUsed =		0;
	burnedOut =		false;
}

//Public Set Functions
void ChristmasLight::SetColor	(string newColor)	{	color = newColor;}
void ChristmasLight::SetWattage	(float newWattage)	{	wattage = newWattage;}
void ChristmasLight::SetMaxTime	(float newMaxTime)	{	maxTime = newMaxTime;}
void ChristmasLight::SetTimeUsed(float newTimeUsed)	
{
	timeUsed = newTimeUsed;

	//burn out lights that have expired
	if(timeUsed > maxTime)
		burnedOut = true;
}

//Public Get Functions
float ChristmasLight::GetTemperature()	
{
	if(burnedOut == true)
		return 70.0;
	else
    	return 70.0 + 4.0 * sqrt(wattage);
}
bool ChristmasLight::IsBurnedOut()	{	return burnedOut;}
string ChristmasLight::GetColor()	{	return color;}
string ChristmasLight::PrintStatus()
{
	if(burnedOut == 0)
		return "Good";
	else
		return "Burned Out";
};


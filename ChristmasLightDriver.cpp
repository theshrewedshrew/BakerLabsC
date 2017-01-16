/*
Programmer:			Michael Schmoyer
Date Completed:		11/30/03
Project:			Programming Assignment 10
					Fall 2003
					CSI 1430
Assumptions:	
	1.) There are as many time values as there are
		lights in the set.
	2.)	There is at least one light in the set
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

#include "ChristmasLight.h"

int main()
{
	//Our "string" of christmas lights 100 lights large
	ChristmasLight Lights[100];

	//A temp light used for swapping
	ChristmasLight tempLight;

	//counter variable i, size of the string inputted, and the three stats to keep
	int setSize = 0, numBurnedOut = 0, numRedLights = 0, numRedAndBurnedOut = 0;

	//parameters of a light inputted from the file
	string color;
	float wattage = 0, maxTime = 0, timeUsed = 0;

	//file containing the christmas light info
	ifstream lightFile;

	//file containing random time used numbers
	ifstream timeFile;

	//have we swapped this round?
	bool swap;



	lightFile.open("final.dat");
	timeFile.open("time.dat");

	lightFile >> color >> wattage >> maxTime;
	timeFile >> timeUsed;

	//If either file is not found, raise error and exit
	if(!lightFile || !timeFile)
	{
		cout << "Error: File not found";
		exit(1);
	}
	
	while(lightFile)
	{		
		//Set this light's parameters to those inputted from file
		Lights[setSize].SetColor(color);
		Lights[setSize].SetWattage(wattage);
		Lights[setSize].SetMaxTime(maxTime);
		Lights[setSize].SetTimeUsed(timeUsed);

		//Record the three statistics told to keep
		if(Lights[setSize].IsBurnedOut() == true)
			numBurnedOut++;
		if(Lights[setSize].GetColor() == "red")
			numRedLights++;
		if(Lights[setSize].GetColor() == "red" && Lights[setSize].IsBurnedOut() == true)
			numRedAndBurnedOut++;

		lightFile >> color >> wattage >> maxTime;
		timeFile >> timeUsed;	
		setSize++;
	};

	cout << left;
	cout << numBurnedOut << " of the " << setSize << " Christmas Lights are burned out." << endl << endl;
	cout << numRedLights << " of the " << setSize << " Christmas Lights are red." << endl << endl;
	cout << numRedAndBurnedOut << " of the " << setSize << " Christmas Lights are burned out and red." << endl;
	
	//Swapping routine
	do
	{
		swap = false;	//default: no swap has occured
		for(int i = 0;i <= setSize - 1;i++)
		{
			if(Lights[i].GetTemperature() > Lights[i + 1].GetTemperature())
			{
				//do swap
				tempLight = Lights[i];
				Lights[i] = Lights[i + 1];
				Lights[i + 1] = tempLight;
				swap = true;	//have swapped
			}	
		}
	}while(swap == true);

	//Display all lights and their parameters in a table
	for(int f = 0;f <= setSize;f++)
	{
		cout << setw(2) << f + 1 << setw(3) << ".)" << setw(15) << Lights[f].GetColor() << setw(15) << Lights[f].GetTemperature() << setw(15) << Lights[f].PrintStatus() << endl;
	}


	return 0;
}

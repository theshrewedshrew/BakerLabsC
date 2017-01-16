#ifndef _RECTANG_H //If not already in the Symble Table add
#define _RECTANG_H
class rectangle
{
	public:
	 // constructors
	 rectangle(); 										 // rectangle r1;
	 rectangle(double l, double w);            // rectangle r2(4,5);

	 // destuctors
	 ~rectangle();

	 // accessors
	 double Length();         // Eample Call - cout << r1.length();
	 double Width();
	 double Area();
	 double Perimeter();

	 // mutators
	 void GetLength();
	 void GetWidth();
	 void Calc_Stats();



	private:
	 double myLength, myWidth;
	 double myArea, myPerimeter;

};

#include "rectang.cpp" // Must be done when no project file is used
#endif
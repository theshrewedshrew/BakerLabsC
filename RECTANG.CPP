#include <utility.inc>
#include "rectang.h"


	 // constructors
	 rectangle::rectangle()
		:myLength(0), myWidth(0)   // set values to 0 for INIT
	 {
		Title("Default Constructor");
	 }
	 rectangle::rectangle(double l, double w)
		:myLength(l), myWidth(w)
	 {
		Title("Second Constructor");
		Calc_Stats();
	 }


	 // destuctors
	 rectangle::~rectangle()
	 {
		Title("Default Destructor");
		Continue();
	 }

	 // accessors
	 double rectangle::Length()
	 {
		return myLength;
	 }
	 double rectangle::Width()
	 {
		return myWidth;
	 }
	 double rectangle::Area()
	 {
		return myArea;
	 }
	 double rectangle::Perimeter()
	 {
		return myPerimeter;
	 }

	 // mutators
	 void rectangle::GetLength()
	 {
		cout << "Enter the length ==> ";
		cin >> myLength;
		ClearBuffer(cin);
	 }
	 void rectangle::GetWidth()
	 {
		cout << "Enter the width ==> ";
		cin >> myWidth;
		ClearBuffer(cin);
	 }
	 void rectangle::Calc_Stats()
	 {
		myPerimeter = 2*(myLength + myWidth);
		myArea = myLength * myWidth;
	 }

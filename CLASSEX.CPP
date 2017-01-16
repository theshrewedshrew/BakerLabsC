#include "rectang.h"


void main()
{
	clrscr();
	rectangle r1,r2(5,10);
	cout << "Length of r2 = "<< r2.Length() <<endl;
	cout << "Width of r2 = " << r2.Width() <<endl;
	cout << "Area of r2 = " << r2.Area() << endl;
	cout << "Perimeter of r2 = " << r2.Perimeter()<< endl<<endl;
	Skip(4,cout);
	r1.GetLength();
	r1.GetWidth();
	r1.Calc_Stats();
	Skip(4,cout);
	cout << "Length of r1 = "<< r1.Length() <<endl;
	cout << "Width of r1 = " << r1.Width() <<endl;
	cout << "Area of r1 = " << r1.Area() << endl;
	cout << "Perimeter of r1 = " << r1.Perimeter()<< endl;
	Skip(4,cout);
	Continue();


}
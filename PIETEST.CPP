// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
//#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>


//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
//Proto Section
	void gr_start( int &, int &, int &);
	void pieslice2(int , int, int, int, int);

void main()
{ clrscr();
	gr_start(grdriver, grmode, errorcode);

	//getch();

};
void gr_start(int & grdriver, int & grmode, int & errorcode)
{ grdriver = VGA;
	grmode= VGAHI;
	initgraph(&grdriver, &grmode, "C:\\TC\\BGI");
	errorcode=graphresult();
	if (errorcode!=grOk)
		{ clrscr();
			cout<<"Error:"<<errorcode<<endl;
			cout<<"Press Return to Continue.";
			getch();
			exit(1);
		}
};

void pieslice2(int X, int Y, int Sa, int Ea, int R)
{
	arc (X,Y,Sa,Ea,R);
	line (X,Y,

}
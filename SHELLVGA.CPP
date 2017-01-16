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
#include <svga.h>


//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
//Proto Section
void outtextxy(int, int, apstring);
#define W	0.836601f
#define H 8

/*void box(int x, int y, float w, float h, BYTE r, BYTE g, BYTE b)
{
	//setfillstyle(SOLID_FILL, r, g, b);

	bar((float)x*w, (float)y*h, (float)x*w+w-1, (float)y*h+h-1);
};*/

void main()
{ clrscr();
	gr_init(SVGATC, 6, "c:/tc/bin/svga");
	grdriver =SVGATC;
	grmode = 6;
	//initgraph(&grdriver,&grmode,"c:/tc/bin/svga");
	cout<<"Test this is just a test";
	line(0,0,300,300);

	//gr_start(grdriver, grmode, errorcode);

	//box(50,50,100,100,50,50,50);
	getch();

};

void outtextxy(int,int,apstring Test)
{
Test="test";
}
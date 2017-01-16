

#include <iomanip.h>
#include <apstring.h>
#include <string.h>
#include <apvector.h>
#include <iostream.h>
#include <apstring.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <gmouse.c>
void rectangle();
void line();
void circle2();
void pixel();

void main()
{ int grdriver=VGA;
	int grmode=VGAHI,errorcode;
	initgraph (&grdriver,&grmode,"C:\\Tc\\BGI");
	errorcode=graphresult();
	if (errorcode!=grOk)
		{	clrscr();
			cout <<"error";
			getch();
			exit(1);
		}
//SetScreenMode(VGA256);
	cleardevice();
	line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
	line(getmaxx()/2,getmaxy()/2,getmaxx()/2,getmaxy());
	do
		{
			switch(random(4))
			{	case 2: rectangle();
								break;
				case 1: line();
								break;
				case 0:	circle2();
								break;
				case 3: pixel();
			}
		} while (!kbhit());

	closegraph();
};

void rectangle()
{
	setcolor(random(16));
	rectangle(random((getmaxx()/2))+1,random((getmaxy()/2))+(getmaxy()/2),random((getmaxx()/2))+1,random((getmaxy()/2))+(getmaxy()/2));
	// Off set is -4

};

void line()
{	setcolor(random(16));
	line(random((getmaxx()/2))+getmaxx()/2,random((getmaxy()/2)-4),random((getmaxx()/2))+getmaxx()/2,random((getmaxy()/2)-4));

};

void circle2()
{ int X,Y,R,Xr,Yr;
	setcolor(random(16));
	X=random((getmaxx()/2))+1;
	Y=random(getmaxy()/2)+1;
	if(X<getmaxx()/4)
	 Xr=X;
	else
	 Xr=(getmaxx()/2)-X;
	if(Y<getmaxy()/4)
	 Yr=Y;
	else
	 Yr=(getmaxy()/2)-Y;
	if(Xr<Yr)
		R=Xr;
	else
		R=Yr;
	circle(X,Y,R);
};

void pixel()
{
	 int X, Y;
	 X=random(getmaxx()/2)+(getmaxx()/2);
	 Y=random(getmaxy()/2)+(getmaxy()/2);
	 putpixel(X,Y,random(16));

};
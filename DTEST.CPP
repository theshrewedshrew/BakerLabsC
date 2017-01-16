

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
#include <dmouse.h>
#include <dgraph.h>
//#include <graphics.inc>
#include <apvector.h>
void ShapeFill (int, int, int &);
apvector <int> Xtemp(100),Ytemp(100);
int I,J,color,oldcolor,X,Y, Count;
void main()
{ int grdriver=VGA;
 int grmode=VGAHI,errorcode;
 initgraph (&grdriver,&grmode,"C:\\Tc\\BGI");
 errorcode=graphresult();
 if (errorcode!=grOk)
	{clrscr();
	 cout <<"error";
	 getch();
	 exit(1);
	 }
 cleardevice();
 setcolor(15);
 line(100,20,100,120);
 line(100,120,200,120);
 line(200,120,150,80);
 line(150,80,175,50);
 line(175,50,100,20);
 rectangle(250,50,260,60);
 color=5;
 oldcolor=0;
 X=110;
 Y=30;
 I=0;
 ShapeFill(X,Y, I);
getch();
closegraph();
}
void ShapeFill(int FX,int FY,int &Count)
{ int N,S,E,W;
	if (Count>5)
			{	Xtemp[I]=FX;
				Ytemp[I]=FY;
				I++;
			return;
			}
	else
	{	Count++;
		if (getpixel(FX,FY-1)== oldcolor)
				{	putpixel(FX,FY-1,color);
					ShapeFill(FX,FY-1,color);
				}
		if (getpixel(FX-1,FY)== oldcolor)
				{	putpixel(FX-1,FY,color);
					ShapeFill(FX-1,FY,color);
				}
		if (getpixel(FX,FY+1)== oldcolor)
				{	putpixel(FX,FY+1,color);
					ShapeFill(FX,FY+1,color);
				}
		if (getpixel(FX+1,FY)== oldcolor)
				{	putpixel(FX+1,FY,color);
					ShapeFill(FX+1,FY,color);
				}





	}
}
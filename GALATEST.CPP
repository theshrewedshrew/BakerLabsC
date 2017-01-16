// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
//#include <apvector.h>
//#include <apstring.h>
#include <bool.h>
//#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include "SVGA.h"
#include "Galagali.h"
//#include <alloc.h>
#include <bitmap.h>

//Const Section

//Var Section
//	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
	image Mypic;
//Proto Section


void main()
{ clrscr();
	//gr_start(grdriver, grmode, errorcode);
	gr_init(SVGA64K, 6, "c:\\tc\\bgi");
	setcolor(110,100,50);
	Mypic.open("a:\\au.bmp");
	Mypic.draw(10,600);
	getch();
	images();
	for(I=50;I<200;I++)
		putpixel(50+I,50,0,105,210);
	cout<<"Max X:"<<getmaxx()<<" Max Y:"<<getmaxy();
	outtextxy(0,1000,"Test");
	line(0,0,getmaxx(),getmaxy());
	bar(200,500,400,700);
	gotoxy(2,50);
	cout<<getpixel(200,500);
	circle(50,800,20);
	do{
	putimage(150,150,A,COPY_PUT);
	delay(1);
	putimage(150,150,D,COPY_PUT);
		delay(1);
		}while(!kbhit());
 //	putimage(200,200,A,COPY_PUT);

// setcolor(110,100,50);

//	for(I=50;I<200;I++)
//		putpixel(50+I,50,0,105,210);

 //	cout<<char(7);
 //	getch();
 closegraph();
};


// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>
#include <math2.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <svga.h>
#include <alloc.h>



//Const Section

//Var Section
	int grdriver, grmode, errorcode;
unsigned	int J,X,Y,Row,Column,Count;
unsigned	int R,G,B;

	unsigned long Size,I;
	void far *P;
	void far *T;
	void far *Q;
	apvector <int> Poly(10);
	//int Poly[10];
//Proto Section
void outtextxy(int, int, apstring);
void drawpoly(int,apvector<int>);
void box(int , int , float , float , BYTE , BYTE , BYTE );

#define W	0.836601f
#define H 8



void main()
{ clrscr();
	gr_init(SVGATC, 6, "c:\\tc\\bin\\svga");
	grdriver =SVGATC;
	grmode = 6;
	//initgraph(&grdriver,&grmode,"c:/tc/bin/svga");

	// cout does not work in this mode
	/**

	 ** gotoxy(1,23);
	 ** cout<<"Test this is just a test";
	 ** getch();

	 **/


	setcolor(255,255,255);
	line(0,0,getmaxx(),getmaxy()); // 0,0,300,300


	J=1000;
	for(I=0;I<8;I++)
	{
	settextstyle(0,0,I);
	outtextxy(100,100+(I*30),ltos(J));
	}
	X=0;
	Y=0;
	R=100;
	G=100;
	B=100;
	for(I=0;I<65536;I++) //(getmaxx()*getmaxy());I++)
	{
	 //	box(I,Y,1,getmaxy(),R,G,B); // X,Y,W,H,R,G,B
		if(I%256==0)
			X++;

		//putpixel(X,Y%256,R,G,B);
		box(X,Y%256,0,getmaxy(),R,G,B);
		Y++;
	}
	 cout<<char(7);
 /*
	for(R=0;R<255;R++)
	{ Y=0;
		for(G=0;G<255;G++)
			for(B=0;B<255;B++)
			{setcolor(R,G,B);
			 //putpixel(X,Y,R,G,B);
			 box(X,Y,0,getmaxy(),R,G,B);
			 Y++;
			}
	 X++;
	}
	*/
// putpixel(random(getmaxx()),random(getmaxy()),random(getmaxcolor()),random(getmaxcolor()),random(getmaxcolor()));
	 //while(!kbhit())
	 //	outtextxy(random(getmaxx()),random(getmaxy()),ltos(J++));
/*	getch();
	cleardevice();
	Poly[0]=20;
	Poly[1]=getmaxy()/2;
	Poly[2]=getmaxx()-20;
	Poly[3]=20;
	Poly[4]=getmaxx()-50;
	Poly[5]=getmaxy()-20;
	Poly[6]=getmaxx()/2;
	Poly[7]=getmaxy()/2;
	Poly[8]=Poly[0];
	Poly[9]=Poly[1];
	drawpoly(10,Poly);
	setfillstyle(1,255,255,255);
	bar(0,0,19,19);
	Size=imagesize(0,0,19,19);
	P=farmalloc(Size);
	getimage(0,0,19,19,P);
	getch();*/
/*

	// With this ON first box has a bleed over of second box
	setcolor(0,0,255);
	setfillstyle(1,100,255,255);
	bar(100,100,119,119);
	//Size=imagesize(0,0,19,19);
	B=farmalloc(Size);
	getimage(100,100,119,119,B);
*/
/*	Count=0;
	do{
		if(Count<getmaxx()-20)
			Count++;
		else
			Count=0;


		putimage(Count,40,P,COPY_PUT);
 //		putimage(Count,80,B,COPY_PUT);
		delay(15);
		putimage(Count,40,P,XOR_PUT); // NOT
//		putimage(Count,80,B,XOR_PUT);

		}while(!kbhit());
	//gr_start(grdriver, grmode, errorcode);

	//box(50,50,100,100,50,50,50);
 */
	getch();

};

void outtextxy(int X,int Y,apstring Test)
{

		moveto(X,Y);
		outtext(Test.c_str());

}
void drawpoly(int Number_Points, apvector<int> Points)
{

 int Ps[20];//Make it bigger then number passed in
 int I;


 for(I=0;I<Points.length();I++)
	Ps[I]=Points[I];

 drawpoly(Number_Points,Ps);


}
void box(int x, int y, float w, float h, BYTE r, BYTE g, BYTE b)
{
	setfillstyle(SOLID_FILL, r, g, b);

	bar((float)x*w, (float)y*h, (float)x*w+w-1, (float)y*h+h-1);
};
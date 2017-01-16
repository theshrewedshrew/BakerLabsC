//Mr. Baker
//Program:sliding square
#include<iostream.h>
#include<conio.h>
#include<apstring.h>
#include<iomanip.h>
#include<apvector.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream.h>
#include<graphics.h>
#include<alloc.h>
#include<dos.h>
//Variable
int Grdriver, Grmode, Errorcode,Count;
unsigned long Size;
void far *P, *Q;
//Prototype
void grsetup (int&, int&, int&);

void main ()
{grsetup(Grdriver,Grmode,Errorcode);

	setcolor(15);
	bar(0,0,20,20);
	Size=imagesize(0,0,20,20);
	P=farmalloc(Size);
	getimage(0,0,20,20,P);
	cleardevice();
	setcolor(2);
	setfillstyle(1,4);
	bar(0,0,20,20);
	Size=imagesize(0,0,20,20);
	Q=farmalloc(Size);
	getimage(0,0,20,20,Q);
	Count=0;
	do{
		if(Count<getmaxx()-20)
			Count++;
		else
			Count=0;


		putimage(Count,40,P,COPY_PUT);
		putimage(Count,80,Q,COPY_PUT);
		delay(15);
		putimage(Count,40,P,NOT_PUT);
		putimage(Count,80,Q,XOR_PUT);

		}while(!kbhit());
};
void grsetup (int& Grdriver, int& Grmode, int& Errorcode)
{
Grdriver=VGA;
Grmode=VGAHI;
initgraph(&Grdriver, &Grmode, "C:\\TC\\BGI");
Errorcode=graphresult();
if (Errorcode!=grOk)
	{clrscr();
	cout<<"Error!";
	getch();
	exit(1);
	}
}
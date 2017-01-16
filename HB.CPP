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
#include <alloc.h>

//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
	void far*P[10];

//Proto Section
	void gr_start( int &, int &, int &);
	void build_horses();

void main()
{ clrscr();
	gr_start(grdriver, grmode, errorcode);
	build_horses();
	cleardevice();
	for(I=0;I<6;I++)
	{putimage(20,30*I,P[I],COPY_PUT);
	getch();
	farfree(P[I]);
	}

//	putimage(20,30*1,P[3],OR_PUT);
//	getch();
//	putimage(20,30*4,P[3],XOR_PUT);
//	getch();
//farfree(P[0]);

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

void build_horses()
{ int Hx,Hx2;
unsigned long Size;
Hx=25;
Hx2=40;



//MOVING///////////////////////////////////////////////////////////////
//BLUE THUNDER/////////////////////////////////////////////////////////////

		setcolor(1);
		setfillstyle(1,1);
				fillellipse(Hx,82,15,10);
				fillellipse(Hx2,70,7,7);
				line(20,80,12,103);
				line(30,80,38,103);
				rectangle(Hx-16,62,Hx2+8,104);
				getch();
				Size=imagesize(Hx-16,62,Hx2+8,104);
				P[0]=farmalloc(Size);
				getimage(Hx-16,62,Hx2+8,104,P[0]);

//LIGHTNING////////////////////////////////////////////////////////////////

		setcolor(3);
		setfillstyle(1,3);
				fillellipse(Hx,157,15,10);
				fillellipse(Hx2,145,7,7);
				line(20,155,12,178);
				line(30,155,38,178);



				Size=imagesize(Hx-16,137,Hx2+8,179);
				P[1]=farmalloc(Size);

				getimage(Hx-16,137,Hx2+8,179,P[1]);

//SPEEDY///////////////////////////////////////////////////////////////////

		setcolor(4);
		setfillstyle(1,4);
				fillellipse(Hx,232,15,10);
				fillellipse(Hx2,220,7,7);
				line(20,230,12,253);
				line(30,230,38,253);

				Size=imagesize(Hx-16,212,Hx2+8,254);
				P[2]=malloc(Size);
				getimage(Hx-16,212,Hx2+8,254,P[2]);

//ROXY/////////////////////////////////////////////////////////////////////

		setcolor(6);
		setfillstyle(1,6);
				fillellipse(Hx,307,15,10);
				fillellipse(Hx2,295,7,7);
				line(20,305,12,328);
				line(30,305,38,328);

				Size=imagesize(Hx-16,287,Hx2+8,329);
				P[3]=farmalloc(Size);
				getimage(Hx-16,287,Hx2+8,329,P[3]);

//POKEY////////////////////////////////////////////////////////////////////

		setcolor(7);
		setfillstyle(1,7);
				fillellipse(Hx,382,15,10);
				fillellipse(Hx2,370,7,7);
				line(20,380,12,403);
				line(30,380,38,403);

				Size=imagesize(Hx-16,287,Hx2+8,329);
				P[4]=farmalloc(Size);
				getimage(Hx-16,362,Hx2+8,404,P[4]);

//MOLASSES////////////////////////////////////////////////////////////////

		setcolor(2);
		setfillstyle(1,2);
				fillellipse(Hx,450,15,10);
				fillellipse(Hx2,438,7,7);
				line(20,448,12,471);
				line(30,448,38,471);

				Size=imagesize(Hx-16,287,Hx2+8,329);
				P[5]=farmalloc(Size);
				getimage(Hx-16,430,Hx2+8,472,P[5]);

}
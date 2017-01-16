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
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>

//Const Section

//Protype Section

void gr_start(int &, int &, int &);

//Var Section
int GrDriver, GrMode, ErrorCode;
int I, J, X, Y, Size, Move, Time;
bool Exit;
apvector <int> Y_Data(640);

void main()
{
	randomize();
	clrscr();
	Exit=false;
	gr_start(GrDriver, GrMode, ErrorCode);
	X=400;
	Y=0;
	Size=getmaxx();
	setcolor(BLUE);
	Y_Data[0]=479-random(80);
	for(I=1;I<getmaxx();I++)
	{	Y_Data[I]=Y_Data[I-1]+(random(3)-1);
		line(I-1,Y_Data[I-1],I-1,getmaxy());
	}
	Time=2;
	Move=0;
	do{

			if(kbhit())
				switch(getch())
				{ case 27:	Exit=true;
										break;
					case 77:	Move=1;
										break;
				}
			if (Move>0)
				{
					for(I=1;I<Size;I++)
					{ setcolor(0);
						line(I,Y_Data[I-1],I,getmaxy());
						delay(Time);
						setcolor(2);
						Y_Data[I-1]=Y_Data[I];
						line(I,Y_Data[I],I,getmaxy());
					}
					Y_Data[Size-1]+=(random(3)-1);
				}

		}while(!Exit);

}

void gr_start(int & grdriver, int & grmode, int & errorcode)
{ initgraph(&grdriver, &grmode, "c:\\tc\\bgi");

	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
		cout<<"Graphics error:"<<grapherrormsg(errorcode)<<endl;
		cout<<"Press any key to halt:"<<endl;
		getch();
		exit(1);             /* return with error code */
	}

}
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

struct Point_Data
{
	int Top;
	int Bottom;

};
//Const Section

//Protype Section

void gr_start(int &, int &, int &);

//Var Section
int GrDriver, GrMode, ErrorCode;
int I, J, X, Y, Size, Move, Time;
bool Exit;
apvector <Point_Data> Data(640);


void main()
{
	randomize();
	clrscr();
	Exit=false;
	gr_start(GrDriver, GrMode, ErrorCode);
	X=400;
	Y=0;
	Size=getmaxx();
	setcolor(2);
	Data[0].Bottom=getmaxy()-random(200);
	Data[0].Top=100+random(100);
	for(I=1;I<=getmaxx();I++)
	{	Data[I].Bottom=Data[I-1].Bottom+(random(3)-1);
		Data[I].Top=Data[I-1].Top+(random(3)-1);
		line(I-1,Data[I-1].Bottom,I-1,getmaxy());
		line(I-1,0,I-1,Data[I-1].Top);
	}
	Time=1;
	I=1;
	do{

			if(kbhit())
				switch(getch())
				{ case 27:	Exit=true;
										break;
					case 77: // Right
										Move=1;
										break;
					case 80: // Down
										Move=0;
										break;
					case 75: // Left
										Move=0;
										break;
					case 72:	// up
										Move=0;
										break;
				}
			if(Move>0)
				{ //for(I=1;I<Size;I++)
					if(I<Size)
						{
							setcolor(0);
							line(I,Data[I-1].Bottom,I,getmaxy());
							line(I,0,I,Data[I-1].Top);
							delay(Time);
							setcolor(2);
							//Data[I-1].Bottom=Data[I].Bottom;
							Data[I-1]=Data[I];
							line(I,Data[I].Bottom,I,getmaxy());
							line(I,0,I,Data[I-1].Top);
							I++;
							if(Data[Size-1].Bottom<350)
								Data[Size-1].Bottom++;
							else if(Data[Size-1].Bottom>450)
										 Data[Size-1].Bottom--;
									 else if(I%100==0)
													Data[Size-1].Bottom+=(random(3)-1);
							if(Data[Size-1].Top<50)
								Data[Size-1].Top++;
							else if(Data[Size-1].Top>150)
										 Data[Size-1].Top--;
									 else if(I%100==0)
													Data[Size-1].Top+=(random(3)-1);
						}
					else
						I=1;


}

}while(!Exit);

}

void gr_start(int & grdriver, int & grmode, int & errorcode)
{ initgraph(&grdriver, &grmode, "c:\\tc\\bgi");

/* read result of initialization */
errorcode = graphresult();

if (errorcode != grOk)  /* an error occurred */
{
cout<<"Graphics error:"<<grapherrormsg(errorcode)<<endl;
cout<<"Press any key to halt:"<<endl;
getch();
exit(1);             /* return with error code */
}

}
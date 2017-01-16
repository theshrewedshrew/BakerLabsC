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

struct Object
{
	int X,Y;
	bool Live;
	int Dir;
	int Speed;
	int Color;
};


//Var Section
	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
	apvector <Object> Objects(5);
	int Key;
	long Count;



//Proto Section
	void gr_start( int &, int &, int &);
	void fireobject(apvector<Object>&);
	void moveobject(apvector<Object>&);
void main()
{ clrscr();
	randomize();
	Objects.resize(random(90)+10);
	for(I=0;I<Objects.length();I++)
	{
		Objects[I].X=random(getmaxx());
		Objects[I].Y=0;
		Objects[I].Live=false;
		Objects[I].Dir=0;
		Objects[I].Speed=1;//random(3)+1;
		Objects[I].Color=random(15)+1;
	}
	Count=0;
	gr_start(grdriver, grmode, errorcode);
	do{ Key=0;
			if(kbhit())
			{
			 Key=getch();
			 if(Key==0)
					Key=getch();
			}
			if(Key==32)
				fireobject(Objects);
			if(Count%1000==0)
				moveobject(Objects);
			if(Count<=100000)
				Count++;
			else
				Count=0;
		}while(Key!=27);
	closegraph();
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

void fireobject(apvector<Object>&Objects)
{
 int Obj;
 bool Exit;

 Obj=0;
 Exit=false;

 do{
		if(!Objects[Obj].Live)
			{
				Objects[Obj].Live=true;
				Objects[Obj].Speed=1;//random(3)+1;
				Objects[Obj].X=random(getmaxx());
				Objects[Obj].Y=0;
				Objects[Obj].Color=random(15)+1;
				Exit = true;
			}
		Obj++;

	 }while(!Exit && Obj<Objects.length());

}

void moveobject(apvector<Object>&Objects)
{
 int Obj;

 for(Obj=0; Obj < Objects.length();Obj++)
	if(Objects[Obj].Live)
	 {	if(Objects[Obj].Y<getmaxy())
			{
			 setcolor(0);
			 line(Objects[Obj].X,Objects[Obj].Y,Objects[Obj].X,Objects[Obj].Y+5);
			 Objects[Obj].Y+=Objects[Obj].Speed;
			 setcolor(Objects[Obj].Color);
			 line(Objects[Obj].X,Objects[Obj].Y,Objects[Obj].X,Objects[Obj].Y+5);
			}
			else
			{
			 setcolor(0);
			 line(Objects[Obj].X,Objects[Obj].Y,Objects[Obj].X,Objects[Obj].Y+5);
				Objects[Obj].Live=false;
			}
	 }


}
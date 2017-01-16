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
	void moveobject(apvector<Object>&,int &);
void main()
{ clrscr();
	randomize();
	//Objects.resize(random(90)+10);
	for(I=0;I<Objects.length();I++)
	{
		Objects[I].X=I+5;//random(getmaxx());
		Objects[I].Y=5;//random(getmaxy());
		Objects[I].Live=true;
		Objects[I].Dir=4;
		Objects[I].Speed=1;//random(3)+1;
		Objects[I].Color=random(15)+1;
	}
	Objects[0].Color=1;
	Count=0;
	Key=0;
	gr_start(grdriver, grmode, errorcode);

	do{
			if(kbhit())
			{
			 Key=getch();
			 if(Key==0)
					Key=getch();
			}
			if(Key==32)
				fireobject(Objects);
			if(Count%1000==0)
				moveobject(Objects,Key);
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



void moveobject(apvector<Object>&Objects, int &Key)
{
 int Obj;
 int ValueX,ValueY;
 ValueX=0;
 ValueY=0;
 bool Flag;
 Flag=false;

 if(Key!=0)
 {
			gotoxy(70,1);
 cout<<Key;
		switch(Key)
		{
		 case 77: if(Objects[Objects.length()-1].Dir!=4)
								 { ValueX=1;
									 Objects[Objects.length()-1].Dir=3;
								 Flag=true;
								 }
							break;
		 case 75: if(Objects[Objects.length()-1].Dir!=3)
								 { ValueX=-1;
									 Objects[Objects.length()-1].Dir=4;
									 Flag=true;
								 }
							break;
		 case 80: if(Objects[Objects.length()-1].Dir!=1)
								 { ValueY=1;
									 Objects[Objects.length()-1].Dir=2;
								 Flag=true;
								 }
							break;
		 case 72: if(Objects[Objects.length()-1].Dir!=2)
								 { ValueY=-1;
									 Objects[Objects.length()-1].Dir=1;
								 Flag=true;
								 }
							break;
		}


	// if(Key==77)
	//	ValueX=1;
	// if(Key==75)
	//	ValueX=-1;
	// if(Key==80)
	//	ValueY=1;
	// if(Key==72)
	//	ValueY=-1;
 if(Flag)
 {
		putpixel(Objects[0].X,Objects[0].Y,0);
	//cleardevice();
	for(Obj=0;Obj< Objects.length()-1;Obj++)
	{ Objects[Obj].X=Objects[Obj+1].X;
		Objects[Obj].Y=Objects[Obj+1].Y;
	}
	 Objects[Objects.length()-1].X+=ValueX;
		Objects[Objects.length()-1].Y+=ValueY;
	for(Obj= Objects.length()-1;Obj>=0;Obj--)
	{
		putpixel(Objects[Obj].X,Objects[Obj].Y,0);
		Objects[Obj].X+=ValueX;
		Objects[Obj].Y+=ValueY;
		putpixel(Objects[Obj].X,Objects[Obj].Y,Objects[Obj].Color);
	}
 }
	Key=0;
 }
}







































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
				Objects[Obj].Color=random(14)+1;
				Exit = true;
			}
		Obj++;

	 }while(!Exit && Obj<Objects.length());

}
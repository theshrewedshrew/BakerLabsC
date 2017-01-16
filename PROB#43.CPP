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


//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
//Proto Section
	void gr_start( int &, int &, int &);
	void move_ball();
void main()
{ clrscr();
	randomize();
	gr_start(grdriver, grmode, errorcode);
	move_ball();
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

void move_ball()
{ int X,Y, D;

	X=getmaxx()/2;
	Y=getmaxy()/2;
	D=random(8);
	while(!kbhit())
		{
			setfillstyle(1,0);
			fillellipse(X,Y,10,10);
			//delay(10);
			setfillstyle(1,1);
			switch(2)
			{ case 0:if(X<10)  //Left to Right
								{ do
									 D=random(8);
									while(D==0);
								}
							 else
									X--;
							 break;
				case 1:if(X>getmaxx()-10) //Right to Left
								{ do
									 D=random(8);
									while(D==1);
								}
							 else
									X++;
							 break;
				case 2:if(Y<10)   // Up
								{ do
									 D=random(8);
									while(D==2);
								}
							 else
									Y--;
							 break;
				case 3:if(Y>getmaxy()-10)
								{ do
									 D=random(8);
									while(D==3);
								}
							 else
									Y++;
							 break;
				case 4:if(X<10 && Y<10)
								{ do
									 D=random(8);
									while(D==4);
								}
							 else
									{	X--;
										Y--;
									}
							 break;
				case 5:if(X<10 && Y<10)
								{ do
									 D=random(8);
									while(D==4);
								}
							 else
									{	X--;
										Y--;
									}
							 break;
			}//End Switch
			fillellipse(X,Y,10,10);
			delay(5);
			gotoxy(1,24);
			cout<<D;
		}


}
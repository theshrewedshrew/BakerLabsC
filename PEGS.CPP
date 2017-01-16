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

struct Values
{
	int G;
	bool BA;
};

//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
	apvector <int> T (4);
	apvector <Values> Guess (4);
	apvector <int> A (4);
	apvector <bool> BA(4);
//Proto Section
	void gr_start( int &, int &, int &);

void main()
{ clrscr();
	//gr_start(grdriver, grmode, errorcode);
	A[0]=A[1]=A[3]=1;
	A[2]=3;
	for(I=0;I<4;I++)
	{ cin>>G[I];
		BA[I]=false;
	}
	for(I=0;I<4;I++)
		{ T[I]=0;
			for(J=I;J<4;J++)
				if(!BA[I])
					if(G[J]==A[I])
					 {	if(J==I)
								T[I]=2;
							else
								T[I]=1;
						 BA[I]=true;
						 J=4;

					 }
			}
	for(I=0;I<4;I++)
	cout<<I<<" Vlaue"<<T[I]<<endl;
	getch();

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

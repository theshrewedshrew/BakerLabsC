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

//Const Section
struct spot
{ int Number;
	bool Flag;
};

//Var Section
apvector <int> Ticket (9);
int I,J,Number;
bool Flag;

void main()
{	clrscr();
	randomize();

	for(Number=0;Number<24;Number++)
	{
	for(I=0;I<9;I++)
		{ Ticket[I]=random(9)+1;
			for(J=0;J<I;J++)
			{ Flag=false;
				while (Ticket[J]==Ticket[I])
				 {	Ticket[I]=random(9)+1;
						Flag=true;
				 }
				if(Flag)
					J=0;
			}
		}
	for(I=0;I<9;I++)
		cout<<Ticket[I]<<" ";
	cout<<endl;
	getch();
	}
}
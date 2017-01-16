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

//Var Section
apvector <int> Ticket (22);
int I,J,K,Number;
bool Flag;


void main()
{	clrscr();
	randomize();

//	for(Number=0;Number<22;Number++)
	{
	for(I=0;I<22;I++)
		{
			for(J=0;J<22;J++)
			 {
				Ticket[I]=random(22)+1;
				do{ Flag=false;
					 for(K=0;K<I;K++)
						if(Ticket[I]==Ticket[K])
							{ Flag=true;
								Ticket[K]=random(22)+1;
							}

					}while(Flag);
			 }

		}
	for(I=0;I<22;I++)
		cout<<Ticket[I]<<" ";
	cout<<endl;
	getch();
	}
}
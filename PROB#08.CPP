// Program: Temperature
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>


//Const Section

//Var Section
int Temp;


void main()
{	clrscr();
	cout<<"Please enter today's Temperature:";
	cin>>Temp;
	cout<<endl<<"Thank you, the sport to play today is ";
	if (Temp>85)
			cout<<"Swimming.";
	else if (Temp>70)
					 cout<<"Tennis.";
			 else if (Temp>32)
								cout<<"Golf.";
						else if (Temp>10)
										 cout<<"Skiing.";
								 else
										 cout<<"Checkers.";

	cout<<endl<<"Have a nice day."<<endl;
	cout<<"Please press return to continue."<<endl;

	getch();
}
// Program: Ticket
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>

//Const Section

//Var Section
	int Age;


void main()
{	clrscr();
	cout<<"Please enter your Age:";
	cin>>Age;
	if (Age<13)
			cout<<endl<<"Thank you, Your Ticket is $6.00"<<endl;
	else
			cout<<endl<<"Thank you, Your Ticket is $8.50"<<endl;

	cout<<"Please press return to continue."<<endl;
	getch();
}
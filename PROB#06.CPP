// Program: Even
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>

//Const Section

//Var Section
	int Number;


void main()
{	clrscr();
	cout<<"Please enter a number:";
	cin>>Number;
	if (Number%2==0)
			cout<<"Thank you, your number "<<Number<<" is even."<<endl;

	cout<<"Please press return to continue."<<endl;
	getch();
}
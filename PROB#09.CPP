// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>


//Const Section

//Var Section
int Speed, Limit;
double Cost;
char School;


void main()
{	clrscr();
	Cost=30.00;
	cout<<setiosflags(ios::showpoint)<<setprecision(2);
	cout<<"Please enter your Speed:";
	cin>>Speed;
	cout<<"Please enter the legal Limit:";
	cin>>Limit;
	cout<<"Was car speeding is a school zone: Y/N";
	cin>>School;

	if ((Speed-Limit)>30)
			 Cost+=100.00;

	if (School=='Y'||School=='y')
			Cost+=((Speed-Limit)*6);
	else
			Cost+=((Speed-Limit)*3);

	cout<<"Your Ticket cost is $"<<Cost<<endl;

	cout<<"Please press return to continue."<<endl;
	getch();
}
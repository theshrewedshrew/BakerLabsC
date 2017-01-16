// Program: Even
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>


//Const Section

//Var Section
	int Hours;
	apstring F_Name, L_Name, Address, Ssn;
	char Answer;
	double Cost;

void main()
{	clrscr();
	cout<<setiosflags(ios::showpoint)<<setprecision(2);
	cout<<"Enter your First Name:";
	cin>>F_Name;
	cout<<"Enter your Last Name:";
	cin>>L_Name;
	cout<<"Please use the underscore ""_"" instead of a space when";
	cout<<" answering"<<endl<<" the following question."<<endl<<endl;
	cout<<"Address:";
	cin>>Address;
	cout<<"Are you a resident Y/N";
	cin>>Answer;
	cout<<"Please enter your SSN (000-00-0000):";
	cin>>Ssn;
	cout<<"Please enter the number of hours taken:";
	cin>>Hours;
	if(Answer=='Y' || Answer=='y')
		{	if (Hours<5)
				Cost=Hours*80.00;
			else if (Hours<12)
							Cost= Hours*70.00;
					 else
							Cost = 900.00;
		}
	else
		{ if (Hours<5)
				Cost=Hours*120.00;
			else if (Hours<12)
							Cost= Hours*110.00;
					 else
							Cost = 1400.00;
		}

	clrscr();
	cout<<"First Name:"<<F_Name<<endl;
	cout<<"Last Name:"<<L_Name<<endl;
	cout<<"Address:"<<Address<<endl;
	cout<<"State Resident:";
	if (Answer=='Y' || Answer =='y')
		cout<<"Yes";
	else
		cout<<"No";
	cout<<endl<<"Your total cost is:$"<<Cost<<endl<<endl;
	cout<<"Please press return to continue."<<endl;
	getch();
}
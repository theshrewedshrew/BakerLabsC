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

//Const Section

//Var Section
 int Day;
 double Amount, Total;
 char Again;


void main()
{
	cout<<setprecision(2)<<setiosflags(ios::fixed)<<setiosflags(ios::showpoint);
do{
		clrscr();
		Total=0;
		Amount=0.01;
		for(Day=0;Day<20;Day++)
		{ Total+=Amount;
			cout<<"Day:"<<Day+1<<" Ms. Williams donated :$"<<Amount<<" and $";
			cout<<Total<<" total."<<endl;
			Amount*=2;
		}
		cout<<"Do you want to run the program again(Y/N)?";
		cin>>Again;
	}while(Again=='Y' || Again=='y');
}
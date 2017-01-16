// Program: Prob#04
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

double Sleep, Jog, Sit, Swim;
int Min15, Min30, Min60;


void main()
{ clrscr();

// Why do I need these???
	cout<<setiosflags(ios::showpoint)<<setprecision(2);


	Sleep=2.3;
	Jog=15.0;
	Sit=1.7;
	Swim= 11.6;
	Min15=15;
	Min30=30;
	Min60=60;

	// Make the headers
	cout<<endl<<endl<<endl;
	cout<<setw(12)<<"Activity"<<setw(15)<<"15 MINUTES"<<setw(15)<<"30 MINUTES";
	cout<<setw(15)<<"60 MINUTES"<<endl;

	cout<<setw(12)<<"SLEEPING"<<setw(15)<<Sleep*Min15<<setw(15)<<Sleep*Min30;
	cout<<setw(15)<<Sleep*Min60<<endl;

	cout<<setw(12)<<"JOGGING"<<setw(15)<<Jog*Min15<<setw(15)<<Jog*Min30;
	cout<<setw(15)<<Jog*Min60<<endl;

	cout<<setw(12)<<"SITTING"<<setw(15)<<Sit*Min15<<setw(15)<<Sit*Min30;
	cout<<setw(15)<<Sit*Min60<<endl;

	cout<<setw(12)<<"SWIMMING"<<setw(15)<<Swim*Min15<<setw(15)<<Swim*Min30;
	cout<<setw(15)<<Swim*Min60<<endl<<endl<<endl;

	cout<<setw(50)<<"Please press return to continue."<<endl;
	getch();
} // End of Main


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

int Lbs, Oz;
double City, State,ECoast,MWest,South,WCoast,Overseas;


void main()
{ clrscr();
	City = 0.15;
	State = 0.35;
	ECoast =0.55;
	MWest = 0.42;
	South = 0.38;
	WCoast = .615;
	Overseas = 1.079;



// Why do I need these???
	cout<<setiosflags(ios::showpoint)<<setprecision(2);
	cout<<"Please enter the package weight pounds first(ie:5) Max:10Lbs. -";
	cin>>Lbs;
	cout<<"Please enter the package's remaining ounces weight(ie:13)";
	cout<<" Max:15ozs -";
	cin>>Oz;

	// Do the Math
	Oz=Oz+(Lbs*16); // or Oz+=(16*Lbs)

	clrscr();
	cout<<endl<<"Your Package of Shrimp from Lone Star SeaFood weighs:";
	cout<<Oz<<"ozs. and it's cost for"<<endl<<" shipping is found below."<<endl;
	cout<<endl<<endl;
	cout<<setw(22)<<"City:$0.15oz"<<setw(10)<<"$"<<City*Oz<<endl;
	cout<<setw(22)<<"State:$0.35oz"<<setw(10)<<"$"<<State*Oz<<endl;
	cout<<setw(22)<<"East Coast:$0.55oz"<<setw(10)<<"$"<<ECoast*Oz<<endl;
	cout<<setw(22)<<"Mid West:$0.42oz"<<setw(10)<<"$"<<MWest*Oz<<endl;
	cout<<setw(22)<<"South:$0.38oz"<<setw(10)<<"$"<<South*Oz<<endl;
	cout<<setw(22)<<"West Coast:$0.615oz"<<setw(10)<<"$"<<WCoast*Oz<<endl;
	cout<<setw(22)<<"Overseas:$1.079oz"<<setw(10)<<"$"<<Overseas*Oz<<endl;

	cout<<endl<<setw(50)<<"Please press return to continue."<<endl;
	getch();
} // End of Main


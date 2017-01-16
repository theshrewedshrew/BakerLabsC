// Program: Prob#02
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>


int Number1, Number2, Number3, Number4;
// Could I have used 0-3? or Number and then 1-3?
// Other Names??

void main()
{ clrscr();

// Why four Promts???

	cout<<"Please enter a whole positive number less then 32767. Ex:5"<<endl;
	cin>>Number1;
	cout<<"Please enter a whole positive number less then 32767. Ex:10"<<endl;
	cin>>Number2;
	cout<<"Please enter a whole positive number less then 32767. Ex101"<<endl;
	cin>>Number3;
	cout<<"Please enter a whole positive number less then 32767. Ex:9"<<endl;
	cin>>Number4;
	clrscr();
	cout<<setw(10)<<"First"<<setw(10)<<"Second"<<setw(10)<<"Third";
	cout<<setw(10)<<"Fourth"<<endl;

	cout<<setw(10)<<Number1<<setw(10)<<Number2<<setw(10)<<Number3;
	cout<<setw(10)<<Number4<<endl<<endl;



	cout<<"Please press return to continue."<<endl;
	getch();
} // End of Main


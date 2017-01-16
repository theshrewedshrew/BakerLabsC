// Program: Fibonacci
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

int Num1, Num2;

bool cont();
void swap_wrong (int, int);
void swap_right (int&, int&);

void main()
{
 do
 {
	 do{
			clrscr();
			cout<<"Please enter a positive number:";
			cin>>Num1;
		 }while(Num1<0);
	 do{
			clrscr();
			cout<<"Please enter a positive number:";
			cin>>Num2;
		 }while(Num2<0);
	 cout<<"Before swap_wrong numbers are: "<<Num1<<" and "<<Num2<<"."<<endl;
	 swap_wrong(Num1,Num2);
	 cout<<"After swap_wrong numbers are: "<<Num1<<" and "<<Num2<<"."<<endl;
	 cout<<"Before swap_right numbers are: "<<Num1<<" and "<<Num2<<"."<<endl;
	 swap_right(Num1,Num2);
	 cout<<"Before swap_right numbers are: "<<Num1<<" and "<<Num2<<"."<<endl;

 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	bool Value;
	cout << endl << "Do you want to run the program again? (Y/N):";
	Answer = getche();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		Value=true;
	else
		Value=false;

	return Value;
}

void swap_wrong ( int X, int Y)
{
	int Temp;
	Temp = X;
	X=Y;
	Y=Temp;
};

void swap_right ( int &X, int &Y)
{
	int Temp;
	Temp = X;
	X=Y;
	Y=Temp;
};
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

int Number;
apstring Name, Address;

bool cont();
long cube (int);
int center (apstring);
apstring evenodd (int);

void main()
{
 do
 {
	do{
			clrscr();
			cout<<"Please enter a positive number :";
			cin>>Number;
		} while(Number<0 || Number > 5000);
		cout<<endl<<"Your number cubed is "<<cube(Number)<<"."<<endl;
		cout<<"Press return to continue.";
		getch();
	do{
		clrscr();
		cout<<endl<<"Please enter a company name :";
		getline(cin,Name);
		}while(Name.length()<1);
	do{
		clrscr();
		cout<<endl<<"Please enter a company address :";
		getline(cin,Address);
		}while(Address.length()<1);
	clrscr();
	gotoxy(center(Name),1);
	cout<<Name;
	gotoxy(center(Address),2);
	cout<<Address<<endl;
	cout<<"Press return to continue.";
		getch();

	clrscr();
	cout<<"Eneter a number to see if it's even or odd :";
	cin>>Number;
	cout<<"Your number is "<<evenodd(Number)<<"."<<endl;


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

long cube ( int N)
{
	return long(N*N*N);
};

int center ( apstring Word)
{
	 return 40-(Word.length()/2);
};

apstring evenodd ( int N)
{
	apstring Value;

	if (N%2==0)
		Value = "Even";
	else
		Value = "Odd";

	return Value;
};


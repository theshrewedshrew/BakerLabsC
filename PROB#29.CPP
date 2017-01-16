// Program: Prob#29
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

int X,Y;

bool cont();
void get_data(int&,int&);
long square(int);

void main()
{
 do
 {
	clrscr();
	get_data(X,Y);
	cout<<"A^2 + B^2 = C^2"<<endl;
	cout<<square(X)<<"+"<<square(Y)<<"="<<square(X)+square(Y)<<endl;
	cout<<endl;

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
};

void get_data (int& A, int &B)
{
	 cout<<"Please enter a number:";
	 cin>>A;
	 cout<<"Please enter a number:";
	 cin>>B;
};

long square (int N)
{
	return long(N*N);
};



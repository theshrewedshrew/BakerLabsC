// Program: Fibonacci
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
//#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

int N;

bool cont();
long fibonacci(int);

void main()
{ clrscr();
 do
 {
	 cout<<"Please Enter a whole number:";
	 cin>>N;
	 cout<<"The fibonacci of "<<N<<" is "<<fibonacci(abs(N))<<endl;
 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	bool Value;
	cout << endl << "Do you want to convert another number? (Y/N):";
	Answer = getche();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		Value=true;
	else
		Value=false;

	return Value;
}

long fibonacci(int N)
{	long Answer;


	Answer=N;
	if (N<3)
		Answer = 1;
	else
			Answer= fibonacci(N-1)+fibonacci(N-2);
	return Answer;
}
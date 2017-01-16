// Program: Factorial
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
double factorial(long);

void main()
{ clrscr();
 do
 {
	 cout<<"Please Enter a whole number:";
	 cin>>N;
	 cout<<"The factorial of "<<N<<" is "<<factorial(N)<<endl;
 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	cout << endl << "Do you want to convert another number? (Y/N):";
	Answer = getche();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		return true;
	else	return false;
}

double factorial(long N)  // 12 is biggest number with longs only
{	double Answer;

	N=abs(N);
	Answer=N;
	if (N>2)
		Answer *= factorial (N-1);

	return Answer;
}
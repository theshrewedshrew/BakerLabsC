// Program: Shell
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

bool cont();
double Ans;
double Sqrt;



void main()
{
 do
 { clrscr();
	 cout<<"Please enter the number to be sqrted:";
	 cin>>Sqrt;
	 Ans=Sqrt;
	 while((Ans*Ans)>Sqrt) Ans/=2;

	 while((Ans*Ans)<Sqrt)
		Ans+=.1;

	 cout<<endl<<"Answer:"<<int(Ans);



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

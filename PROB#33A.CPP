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
apvector <int> Array(200);
int I,J;

long sumarrayr(apvector <int>);

void main()
{ clrscr();
	randomize();
 do
 {
	 J=random(200);
	 for(I=0;I<J;I++)
		Array[I]=random(500);
	 cout<<"Your Total is:"<<sumarrayr(Array)<<endl;

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

long sumarrayr(apvector <int> Array)
{
 long Ans;

	if(Array.length()<2)
		Ans = Array[0];
	else
		{
			Ans = Array[Array.length()-1];
			Array.resize(Array.length()-1);
			Ans+=sumarrayr(Array);
		}
	return Ans;
}

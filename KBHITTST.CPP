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
int Key;
bool cont();

void main()
{ clrscr();
 do
 {
	Key=0;
	if(kbhit())
		Key=getch();
 if(Key!=0)
 cout<<Key;

 }
 while (Key!=27);
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

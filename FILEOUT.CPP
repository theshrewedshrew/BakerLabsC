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
#include <fstream.h>

ofstream Out_File;
int I, Size, Temp;

bool cont();

void main()
{ randomize();
	clrscr();
 do
 {
	Out_File.open("SortFile.dat");
	Size=random(32767);
	for(I=0;I<Size;I++)
	{	Temp=random(32767);
		Out_File<<Temp<<endl;
	}

	Out_File.close();
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

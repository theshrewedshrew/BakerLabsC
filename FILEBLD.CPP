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

bool cont();
void build();

void main()
{ clrscr();
	randomize();
 do
 { build();
 }
 while (!cont());
} // End of Main

bool cont()
{ char Answer;
	bool Value;
	cout << endl << "Do you want to run the program again? (Y/N):";
	Answer = getche();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		Value=false;
	else
		Value=true;

	return Value;
}

void build ()
{  ofstream Fout;
	apstring File_Name;
	int I,A,J,Size;

	File_Name="Datafile";
		//File_Name=File_Name+char(48+I);
		File_Name=File_Name+".dat";
		Fout.open(File_Name.c_str());
		Size = random(10)+1;
		Fout<<Size<<endl<<endl;
	for(I=0;I<Size;I++)
	{

	//cout<<File_Name<<endl;
		A=random(50)+1;
		for(J=0;J<A;J++)
		{
			Fout<<random(32767)<<" ";
		}
		Fout<<endl<<endl;
	}
	Fout.close();
}



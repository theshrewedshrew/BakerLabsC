// Program: Shell
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <bool.h>
#include <math.h>
#include <fstream.h>
#include <stdlib.h>
#include <alloc.h>

struct fManager
{
	ifstream Logfile;
	char Str[50];
	int Age;
};

fManager *FileManager;
unsigned long Dircount;
int I;

bool cont();

void main()
{ clrscr();
 do
 {
	 Dircount = 10;
	 FileManager = (fManager*)calloc (Dircount,sizeof(fManager));
	 if (FileManager==NULL)
			{
			 cout<<"Insufficient Memory for File Manager. Exiting Program.."<<endl;
			 getch();
			 exit(1);

			}
	 else
			cout<<"File Manager Created..."<<endl;

	 for(I=0; I<Dircount;I++)
	 {
		FileManager[I].Age = I;
		cout<<FileManager[I].Age<<endl;
		FileManager[I].Logfile.open("A:\\Prob#37.dat");// this is for my test
		FileManager[I].Logfile.close();
	 }

	 //		cout<<"Successfully Opened File:"<<endl;




 }
 while (cont()==true);
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

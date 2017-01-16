// Program: Diver Reader
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <fstream.h>
#include <bool.h>
#include <math.h>

struct Diver
{
	apstring LName,FName;
	apvector <double> Scores;
	apstring School_Name;
	char School_Size;

};

apvector <Diver> Divers;


bool cont();
void collect_data(apvector <Diver>&);
void display_data(apvector <Diver>);


void main()
{ clrscr();
	collect_data(Divers);
 do
 {
	display_data(Divers);
 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	bool Value;
	cout << endl << "Do you want to run the program again? (Y/N):";
	Answer = getch();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		Value=true;
	else
		Value=false;

	return Value;
}

void collect_data(apvector <Diver>& Divers)
{
	ifstream In_File;
	int I,Count;
	apstring Trash;
	Count=0;
	In_File.open("D-Scores.dat");
	do{
		 Divers.resize(Count+1);
		 Divers[Count].Scores.resize(8);
		 In_File>>Divers[Count].LName;
		 In_File>>Divers[Count].FName;
		 for(I=0;I<8;I++)
			In_File>>Divers[Count].Scores[I];
		 getline(In_File,Trash);
		 getline(In_File,Divers[Count].School_Name);
		 In_File>>Divers[Count].School_Size;


		 Count++;
		}while(!In_File.eof());
	In_File.close();
	Divers.resize(Count-1);


}

void display_data( apvector <Diver> Divers)
{
	int I,J;

	clrscr();

	for (I=0;I<Divers.length();I++)
	{
	 cout<<"Diver's Name: "<<Divers[I].LName<<", "<<Divers[I].FName<<" "<<endl;
	 cout<<"Scores: 1:"<<Divers[I].Scores[0]<<endl;
	 for(J=1;J<8;J++)
		cout<<setw(9)<<J+1<<":"<<Divers[I].Scores[J]<<endl;
	 cout<<"School Name: "<<Divers[I].School_Name<<endl;
	 cout<<"School Size: ";
	 if (Divers[I].School_Size!='S')
		cout<<"Big"<<endl;
	 else
		cout<<"Small"<<endl;
	 cout<<endl;
	 if((I+1)%4==0)
	 {
		cout<<endl<<"Please Press Return to Continue.";
		getch();
		clrscr();
	 }

	}

}


void sort_by_total_points(apvector <Diver>& Divers)
{

}

double total_points(apvector <double> Scores)
{

}
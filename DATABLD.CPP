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

struct Diver
{ apstring FName, LName, School_Name;
	apvector <double> Scores;
	char School_Size;
};


bool cont();
void data_build();
void main()
{ clrscr();
	randomize();
 do
 {
 data_build();
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
		Value=false;
	else
		Value=true;

	return Value;
}

void data_build()
{
	ofstream Out_File;
	int I;
	char Another;
	Diver Diver_Data;
	apstring Trash;

	Diver_Data.Scores.resize(8);
	Out_File.open("D-Scores.dat");
	do{
		clrscr();
		cout<<"Please enter a Divers First Name: ";
		getline(cin,Diver_Data.FName);
		cout<<"Please enter a Divers Last Name: ";
		getline(cin,Diver_Data.LName);
		for(I=0;I<8;I++)
			{
			// cout<<"Please enter the diver's "<<I+1<<" score:";
			// cin>>Diver_Data.Scores[I];
			Diver_Data.Scores[I]=(random(600)+1)/100.0;
			}
		//	getline(cin,Trash);
	 //	cout<<"Please enter the diver's school name:";
//		getline(cin,Diver_Data.School_Name);
	 //	cout<<"Please enter the diver's school size - B-Big S-Small:";
	 //	cin>>Diver_Data.School_Size;

	 switch(random(8))
	 {
		case 0 :  Diver_Data.School_Name="Allen High School";
							Diver_Data.School_Size='B';
							break;
		case 1 :  Diver_Data.School_Name="Plano High School";
							Diver_Data.School_Size='B';
							break;
		case 2 :  Diver_Data.School_Name="Plano East High School";
							Diver_Data.School_Size='B';
							break;
		case 3 :  Diver_Data.School_Name="Plano West High School";
							Diver_Data.School_Size='B';
							break;
		case 4 :  Diver_Data.School_Name="Frisco High School";
							Diver_Data.School_Size='S';
							break;
		case 5 :  Diver_Data.School_Name="Chugiak High School";
							Diver_Data.School_Size='S';
							break;
		case 6 :  Diver_Data.School_Name="MidWay High School";
							Diver_Data.School_Size='S';
							break;
		case 7 :  Diver_Data.School_Name="Prosper High School";
							Diver_Data.School_Size='S';
							break;
	 }

		Out_File<<Diver_Data.LName<<" "<<Diver_Data.FName<<endl;
		for(I=0;I<8;I++)
			Out_File<<Diver_Data.Scores[I]<<" ";
		Out_File<<endl<<Diver_Data.School_Name<<endl;
		Out_File<<Diver_Data.School_Size<<endl;


		cout<<"Do you have another Diver?(Y/N)";
		cin>>Another;
		getline(cin,Trash);
		}while(Another=='Y' || Another == 'y');
	Out_File.close();
}

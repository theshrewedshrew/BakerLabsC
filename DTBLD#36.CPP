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

struct Data_Rec
{
	apstring Name;
	apvector <double> Grades;
	double Avg;
	char Letter_Grade;
};

apvector <Data_Rec> Students;
int Cls,C,S;
bool cont();

void main()
{
	randomize();
	clrscr();
 do
 {
	 cout<<"Number of Classes:";
	 cin>>Cls;
	 for(C=0;C<Cls;C++)
	 {
		Students.resize(random(25)+1);
		for(S=0;S<Students.length();S++)
			{ if(S<10)
					Students[S].Name="Student#"+char(48+S);
				else if (S<20)
							Students[S].Name="Student#"+char(49)+char(48+(S%10));
						 else
							Students[S].Name="Student#"+char(50)+char(48+(S%20));


			}
	 cout<<"Number of Students in Class:"<<Students.length()<<"."<<endl;

	 for(S=0;S<Students.length();S++)
		cout<<Students[S].Name<<endl;
	 }









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
		Value=true;
	else
		Value=false;

	return Value;
}

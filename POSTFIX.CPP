// Program: PostFix - PreFix
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>

int Spot;
int LPar, RPar;
apstring Equ, Op_List, Value_List;
bool Error;
bool cont();
void menu();
void show_moves (long &,int, char, char, char);
void salve_problem (int , apstring &, apstring &, apstring &, bool &);

void main()
{ clrscr();
 do
 { menu();
 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	cout << endl << "Do you want to run again? (Y/N)";
	Answer = getche();
	if (Answer == 'Y' || Answer == 'y')
		return true;
	else	return false;
}

void menu()
{
	{	clrscr();
		cout<<"Please enter an equation:";
		getline(cin,Equ);
	}	while(Equ.length()<1);
	Spot=0;
	Op_List=Value_List="";
	Error=false;
	salve_problem (Spot, Equ, Op_List, Value_List, Error);

};

void show_moves (long &Count, int Disks, char Start_Peg, char Last_Peg, char Spare_Peg)
{ Count++;
	if (Disks==1)
		cout<<"Move disk #1 from "<< Start_Peg <<" to "<<Last_Peg<<endl;
	else
	{	show_moves (Count, Disks -1, Start_Peg, Spare_Peg, Last_Peg);
		cout<<"Move disk #"<<Disks<<" from "<<Start_Peg<<" to "<<Last_Peg<<endl;
		show_moves (Count, Disks-1, Spare_Peg, Last_Peg, Start_Peg);
	}
};


void salve_problem (int Spot, apstring &Equ, apstring &Op_List,
										apstring &Value_List, bool &Error)
{

	if ((Spot < Equ.length()) || Error)
		{	switch (Equ[Spot])
			{	case '(' : LPar++;
									 break;
				case ')' : RPar++;
									 break;
				case '+' :
				case '-' :
				case '/' :
				case '*' :
				case '%' : Op_List = Op_List + Equ[Spot];
									 break;
				default	 :
									 if ((Equ[Spot] >'1') && (Equ[Spot]<':'))
											Value_List=Value_List+Equ[Spot];
									 else if ((Equ[Spot] >'@') && (Equ[Spot]<'[') ||
														((Equ[Spot] >'`') && (Equ[Spot]<'{')))
														 Value_List=Value_List+Equ[Spot];
												else
														Error=true;

			} // Switch Case
			cout<<"Output "<<Op_List<<" Value:"<<Value_List<<endl;
			salve_problem (Spot+1, Equ, Op_List, Value_List, Error);
		}
} //End Function
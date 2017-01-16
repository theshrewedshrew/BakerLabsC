// Program: Tower Of Hanoi
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>



bool cont();
void menu();
void show_moves (long &,int, char, char, char);

void main()
{ clrscr();
 do
 { menu();
 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	bool Ans;
	cout << endl << "Do you want to run again? (Y/N)";
	Answer = getch();
	if (Answer == 'Y' || Answer == 'y')
		Ans= true;
	else	Ans=false;
	return Ans;
}

void menu()
{ int Disks;
	long Count;
	Count=0;
	clrscr();
	do{
			cout<<"Please Enter the number of disk:";
			cin>>Disks;
		}while (Disks<0);
	clrscr();
	cout<<"Start with "<<Disks<<" disks on Peg A"<<endl<<endl;
	cout<<"Then proceed as follows:"<<endl;
	show_moves(Count, Disks,'A','C','B');
	cout<<endl<<"Total Moves:"<<Count<<endl;

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
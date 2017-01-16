// Program: Shell
// By: Bryan J. Baker

#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>
#include <fstream.h>
#include <time.h>
#include <dos.h>

struct Room_Rec
{
	bool Picked;
	apstring Room;

};

apvector <Room_Rec> Rooms(1);
int Max_Rooms;

bool cont();
void read_infile(apvector <Room_Rec>&);
void print_output(apvector <Room_Rec>);
void get_random_rooms(apvector <Room_Rec> & , int );
void how_many_rooms(int & , int );
void screen_output(apvector <Room_Rec>);
void main()
{ clrscr();
	randomize();
 do
 {
	read_infile(Rooms);

	how_many_rooms(Max_Rooms,Rooms.length());

	get_random_rooms(Rooms,Max_Rooms);
	screen_output(Rooms);
	print_output(Rooms);

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

void read_infile(apvector <Room_Rec> & Rooms)
{
	int I;
	ifstream In_file;

	In_file.open("Rooms.txt");
	I=0;
	getline(In_file,Rooms[I].Room);
	Rooms[I].Picked=false;
	I++;
	while(!In_file.eof())
	{
		Rooms.resize(I+1);
		getline(In_file,Rooms[I].Room);
		Rooms[I].Picked=false;
		I++;
	}
}

void print_output(apvector <Room_Rec>  Rooms)
{
	int I, Min, Hour;
	ofstream Printer;
	dosdate_t Date;
	dostime_t Time;

	_dos_getdate(&Date);// get the Date
	_dos_gettime(&Time);// get the Time

	Printer.open("lpt1");// open the printer stream
	//Printer<<setprecision(2)<<setiosflags(ios::showpoint);
	//clrscr();
	Printer<<"Rooms to be checked on "<<int(Date.month)<<"/"<<int(Date.day);
	Printer<<"/"<<Date.year<<" printed at "<<int(Time.hour)<<":";
	if(int(Time.minute)<10)
		Printer<<0;
	Printer<<int(Time.minute)<<endl;
	for (I=0;I<Rooms.length();I++)
		if(Rooms[I].Picked)
			Printer<<Rooms[I].Room<<endl;
}

void get_random_rooms(apvector <Room_Rec> & Rooms, int Max_Rooms)
{
	int I,R;

	for(I=0;I<Max_Rooms;I++)
		{ do
				R=random(Rooms.length());
			while(Rooms[R].Picked);
			Rooms[R].Picked=true;
		}
}


void how_many_rooms(int & Max_Rooms, int L)
{
 do{
		 clrscr();
		 cout<<"How many rooms do you want to check?"<<endl;
		 cout<<"Please enter only numbers greater then 0."<<endl;
		 cout<<":";
		 cin>>Max_Rooms;
		 if(Max_Rooms<0||Max_Rooms>L)
			{	cout<<"Please check your number of rooms and try again."<<endl;
				cout<<"Please press return to continue."<<endl;
				getch();
			}
	 }while(Max_Rooms<0||Max_Rooms>L);
}

void screen_output(apvector <Room_Rec>  Rooms)
{
	int I, Min, Hour;

	dosdate_t Date;
	dostime_t Time;

	_dos_getdate(&Date);// get the Date
	_dos_gettime(&Time);// get the Time



	clrscr();
	cout<<"Rooms to be checked on "<<int(Date.month)<<"/"<<int(Date.day);
	cout<<"/"<<Date.year<<" printed at "<<int(Time.hour)<<":";
	if(int(Time.minute)<10)
		cout<<0;
	cout<<int(Time.minute)<<endl;
	for (I=0;I<Rooms.length();I++)
		if(Rooms[I].Picked)
 //			cout<<Rooms[I].Room<<"*"<<endl;
 //		else
			cout<<Rooms[I].Room<<endl;
}

// Curtis Hastings
// 3rd Period

//Library Section
#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>
#include   <stdio.h>
#include   <dos.h>

//Struct Section
struct Data
{
int AcNum;
double Balance;
apstring Name,Address,Phnum;
};

//Variables Section
char Answer;
int Num_Acc, Max_Num,Choice;
ifstream in;
ofstream out;


void main()
{

do{
Answer='Y';

do{
clrscr();
cout<<"Please Make A Choice:"<<endl<<"1. Modify Existing Account"<<endl;
cout<<"2. Create an Account"<<endl<<"3. Cancel an Account"<<endl<<"4. Exit";
gotoxy(23,1);
cin>>Choice;
}while(Choice<1||Choice>5);


clrscr();
cout<<endl<<"Do you want to run the program again? (Y/N):";
cin>>Answer;
}while(Answer=='Y'||Answer=='y');
cout<<endl<<"Press Any Key to Exit";
getch();
}//END Program





/*
int main(void)
{
	 struct  time t;

	 gettime(&t);
	 printf("The current time is: %2d:%02d:%02d.%02d\n",
					t.ti_hour, t.ti_min, t.ti_sec, t.ti_hund);
	 return 0;
}

int main(void)
{
	 struct date d;

	 getdate(&d);
	 printf("The current year is: %d\n", d.da_year);
	 printf("The current day is: %d\n", d.da_day);
	 printf("The current month is: %d\n", d.da_mon);
	 return 0;
} */
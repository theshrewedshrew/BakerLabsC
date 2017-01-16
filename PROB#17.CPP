// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
//#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

//Const Section

//Var Section
	char Again;
	int Students, Dept, I, Y;
	int Class0,Class01,Class02,Class03,Class04,Class05,Class06,Class07,Class08;
	int Class09;


void main()
{
	do{
			do{
					clrscr();
					cout<<"Please enter Department number (0-9):";
					cin>>Dept;
					if(Dept<0 || Dept>9)
						{
						 cout<<"Please enter ONLY numbers 0 - 9."<<endl;
						 cout<<"Press return to continue."<<endl;
						 getch();

						}

				}while (Dept<0 || Dept>9);
			for (I=0;I<10;I++)
			{	do{ clrscr();
						gotoxy(5,3);
						cout<<setw(65)<<" ";
						gotoxy(5,3);
						cout<<"Please enter the number (0 - 40) of students for class ";
						cout<<Dept<<"0"<<I<<":";
						cin>>Students;

						if(Students<0 || Students>40)
						{
						 gotoxy(5,6);
						 cout<<"Please enter ONLY numbers 0 - 40."<<endl;
						 gotoxy(5,7);
						 cout<<"Press return to continue."<<endl;
						 getch();

						}

					}while(Students<0 || Students>40);
				switch(I)
				{	case 0:	Class0 = Students;
									break;
					case 1:	Class01 = Students;
									break;
					case 2:	Class02 = Students;
									break;
					case 3:	Class03 = Students;
									break;
					case 4:	Class04 = Students;
									break;
					case 5:	Class05 = Students;
									break;
					case 6:	Class06 = Students;
									break;
					case 7:	Class07 = Students;
									break;
					case 8:	Class08 = Students;
									break;
					case 9:	Class09 = Students;
									break;
				}
			}
			clrscr();
			gotoxy(2,4);
			cout<<"Class #";
			gotoxy(10,4);
			cout<<"Graph of Students in Class";
			Y=5;
			gotoxy(6,Y);
			cout<<Dept<<"00 ";
			for(I=0;I<Class0;I++)
				 cout<<"*";
			gotoxy(11+Class0,Y++);
			cout<<Class0;
			gotoxy(6,Y);
			cout<<Dept<<"01 ";
			for(I=0;I<Class01;I++)
				 cout<<"*";
			gotoxy(11+Class01,Y++);
			cout<<Class01;
			gotoxy(6,Y);
			cout<<Dept<<"02 ";
			for(I=0;I<Class02;I++)
				 cout<<"*";
			gotoxy(11+Class02,Y++);
			cout<<Class02;
			gotoxy(6,Y);
			cout<<Dept<<"03 ";
			for(I=0;I<Class03;I++)
				 cout<<"*";
			gotoxy(11+Class03,Y++);
			cout<<Class03;
			gotoxy(6,Y);
			cout<<Dept<<"04 ";
			for(I=0;I<Class04;I++)
				 cout<<"*";
			gotoxy(11+Class04,Y++);
			cout<<Class04;
			gotoxy(6,Y);
			cout<<Dept<<"05 ";
			for(I=0;I<Class05;I++)
				 cout<<"*";
			gotoxy(11+Class05,Y++);
			cout<<Class05;
			gotoxy(6,Y);
			cout<<Dept<<"06 ";
			for(I=0;I<Class06;I++)
				 cout<<"*";
			gotoxy(11+Class06,Y++);
			cout<<Class06;
			gotoxy(6,Y);
			cout<<Dept<<"07 ";
			for(I=0;I<Class07;I++)
				 cout<<"*";
			gotoxy(11+Class07,Y++);
			cout<<Class07;
			gotoxy(6,Y);
			cout<<Dept<<"08 ";
			for(I=0;I<Class08;I++)
				 cout<<"*";
			gotoxy(11+Class08,Y++);
			cout<<Class08;
			gotoxy(6,Y);
			cout<<Dept<<"09 ";
			for(I=0;I<Class09;I++)
				 cout<<"*";
			gotoxy(11+Class09,Y++);
			cout<<Class09<<endl;

			cout<<"Do you want to run again (Y/N)?";
			cin>>Again;
		}while(Again=='Y' || Again=='y');
}
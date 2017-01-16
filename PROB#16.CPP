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
	int Choice;
	apstring Book_Type;
	double Cost, Total;
	int Days, I;

void main()
{ cout<<setprecision(2)<<setiosflags(ios::showpoint);
	do{
		Total=0;
		do{
			do{	clrscr();
					gotoxy(5,2);
					cout<<"1)Paperback: 20 cents a day.";
					gotoxy(5,3);
					cout<<"2)Magazines: 35 cents a day.";
					gotoxy(5,4);
					cout<<"3)Reference: 75 cents a day.";
					gotoxy(5,5);
					cout<<"4)General Books: 50 cents a day.";
					gotoxy(5,6);
					cout<<"5)Stop";
					gotoxy(5,20);
					cout<<"The persons total is:$"<<Total;
					gotoxy(5,8);
					cout<<"Please Enter a Choice:";
					cin>>Choice;
					if(Choice<1 || Choice>5)
					{ gotoxy(5,14);
						cout<<"Please enter a number 1-5 only."<<endl;
						gotoxy(5,15);
						cout<<"Press return to continue."<<endl;
						getch();
					}

				}while(Choice<1 || Choice>5);
				if(Choice!=5)
					{	gotoxy(5,12);
						cout<<"Please enter the days late for a ";
						switch(Choice)
						{	case 1: Book_Type="Paperback Book";
											Cost=.20;
											break;
							case 2: Book_Type="Magazine";
											Cost=.35;
											break;
							case 3: Book_Type="Reference Book";
											Cost=.75;
											break;
							case 4: Book_Type="General Book";
											Cost=.50;
											break;
						}
						cout<<Book_Type<<":";
						do{ gotoxy(5,13);
								cin>>Days;
								if(Days<1)
									{
										gotoxy(5,15);
										cout<<"Please enter only numbers above 0."<<endl;
										gotoxy(5,16);
										cout<<"Press return to continue."<<endl;
										getch();
										for(I=0;I<4;I++)
										{	gotoxy(5,13+I);
											cout<<setw(40)<<"      ";
										}
									}
							}while(Days<1);
						Total+=(Days*Cost);
					 }

			}while(Choice!=5);


				 gotoxy(5,22);
				 cout<<"Do you have more stacks of books? (Y/N)?";
				 cin>>Again;
		}while(Again=='Y' || Again=='y');


	//getch();
}
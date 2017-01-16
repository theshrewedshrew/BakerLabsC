// Phone Program
// Programed By: Bryan J. Baker

#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>
//#include <bool.h>
//Const

//Variables
apstring Name,Address,Trash;
int Start_Hrs, Start_Min, End_Hrs, End_Min, Start, End, Min, Call_Length;
int Hi_Cost, Low_Cost, Length;
double Total;
char Answer;

void main()
{ cout<<setiosflags(ios::showpoint);
	cout<<setprecision(2);
do{

	clrscr();
	cout<<"Please Enter your Name:";
	getline(cin,Name);
	cout<<"Please Enter your Address:";
	getline(cin,Address);
	do {
			clrscr();
			gotoxy(5,5);
			cout<<"Please Enter Starting Hours in 24-hour clock (Ex:21):";
			cin>>Start_Hrs;
		 } while (Start_Hrs<0 || Start_Hrs>24);
	do {
			clrscr();
			gotoxy(5,5);
			cout<<"Please Enter Starting Minutes (Ex:19):";
			cin>>Start_Min;
		 } while (Start_Min<0 || Start_Min>59);
	do {
			clrscr();
			gotoxy(5,5);
			cout<<"Please Enter Ending Hours in 24-hour clock (Ex:21):";
			cin>>End_Hrs;
		 } while (End_Hrs<0 || End_Hrs>24);
	do {
			clrscr();
			gotoxy(5,5);
			cout<<"Please Enter Ending Minutes (Ex:54):";
			cin>>End_Min;
		 } while (End_Min<0 || End_Min>59);

	Start=(Start_Hrs*60)+Start_Min;
	End=(End_Hrs*60)+End_Min;
	if(End<Start)
		End=End+1440;
	Call_Length =End-Start;

	Total=0;
	Hi_Cost=0;
	Low_Cost=0;
	if (Start<480)
		{	for(Min=Start; Min<End; Min++)
			if (Min>=480&&Min<1080)
				{ Total+=.25;
					Hi_Cost+=1;
				}
			else { Total+=.18;
						 Low_Cost+=1;
					 }
		}
	else if (Start>=480 && Start<1080)
					{ for(Min=Start; Min<End; Min++)
							if (Min<1080 || Min>=1920)
								{ Total+=.25;
									Hi_Cost+=1;
								}
							else { Total+=.18;
										 Low_Cost+=1;
									 }
					}
			 else { for(Min=Start; Min<End; Min++)
							if ( Min>=1920 && Min <2520)
								{ Total+=.25;
									Hi_Cost+=1;
								}
							else { Total+=.18;
										 Low_Cost+=1;
									 }
						}

	clrscr();
	gotoxy(5,5);
	cout<<"Name:"<<Name;
	gotoxy(5,6);
	cout<<"Address:"<<Address;
	gotoxy(5,7);
	cout<<"Start Time|"<<Start_Hrs<<":"<<Start_Min;
	gotoxy(5,8);
	cout<<"Ending Time|"<<End_Hrs<<":"<<End_Min;
	gotoxy(5,9);
	cout<<"Length of Call:"<<Call_Length;
	gotoxy(5,10);
	cout<<"Total Mins at 18 cents "<<Low_Cost;
	gotoxy(5,11);
	cout<<"Total Mins at 25 cents "<<Hi_Cost;
	gotoxy(5,12);
	cout<<"Total Cost of Call:$"<<Total;
	gotoxy(5,22);
	cout<<"Do you have another call (Y/N)?";
	cin>>Answer;
	getline(cin,Trash);
	} while (Answer!='N' && Answer!='n');
};
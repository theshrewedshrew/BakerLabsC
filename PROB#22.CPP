// Array Program
// Programed By: Bryan J. Baker

#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>
#include <apvector.h>
//#include <bool.h>
//Const

//Variables
apvector <int> Classes(10);
int I,J, Dept;
char Ans;



void main()
{
	do{
			do{
				 clrscr();
				 cout<<"Please enter your Department Number 0-9:";
				 cin>>Dept;
				 if(Dept<0 || Dept>9)
				 {
					cout<<"Please enter ONLY numbers 0-9. Thank you."<<endl;
					cout<<"Press return to continue.";
					getch();
				 }
				}while(Dept<0 || Dept>9);

			for(I=0;I<10;I++)
			{
				do{
						clrscr();
						cout<<"Please enter the number of students(0-40) in Class#";
						cout<<Dept<<"0"<<I<<":";
						cin>>Classes[I];
						if(Classes[I]<0 || Classes[I]>40)
							{
								cout<<"Please enter ONLY class sizes from 0-40.";
								cout<<" Thank you."<<endl;
								cout<<"Press return to continue.";
								getch();
							}
					}while(Classes[I]<0 || Classes[I]>40);
			 }
			clrscr();
			for(I=0;I<10;I++)
				{
					cout<<"Class "<<Dept<<"0"<<I<<":";
					for(J=0;J<Classes[I];J++)
						cout<<"*";
					cout<<setw(5)<<Classes[I]<<endl;
				}

			cout<<endl<<"Do you want to run the program again(Y/N)?";
			cin>>Ans;

		}while(Ans=='y'||Ans=='Y');

}
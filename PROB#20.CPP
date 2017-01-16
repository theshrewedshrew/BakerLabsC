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
apvector <int> Numbers(20);
apvector <int> Even(10);
apvector <int> Odd(10);
int I, Count;
char Ans;



void main()
{
	do{
			clrscr();
			// Must start Count a Zero for multiple runs
			Count=0;

			// Build the array of Numbers
			for(I=0;I<20;I++)
				Numbers[I]=I+1;

			// Split the numbers into Even and Odd arrays
			for(I=0;I<20;I++)
				if(Numbers[I]%2==0)
					{
						Even[Count]=Numbers[I];
						Count++;// We only need to increase Count AFTER even numbers
					}
				else
						Odd[Count]=Numbers[I];

			// Display the Table
			cout<<setw(9)<<"Odds"<<setw(15)<<"Evens"<<endl;
			for(I=0;I<10;I++)
				cout<<setw(9)<<Odd[I]<<setw(15)<<Even[I]<<endl;


			cout<<endl<<"Do you want to run the program again(Y/N)?";
			cin>>Ans;

		}while(Ans=='y'||Ans=='Y');

}
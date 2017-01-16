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
apvector <int> Numbers(5);
int I;
char Ans;



void main()
{
	do{
			clrscr();
			for (I=0;I<5;I++)
			{	cout<<"Please enter a number:";
				cin>>Numbers[I];
			}
			cout<<endl<<endl<<"Forward:";
			for(I=0;I<5;I++)
				cout<<Numbers[I]<<" ";
			cout<<endl<<endl<<"Backwards:";
			for(I=4;I>=0;I--)
				cout<<Numbers[I]<<" ";
			cout<<endl<<"Do you want to run the program again(Y/N)?";
			cin>>Ans;

		}while(Ans=="y"||Ans=="Y");

}
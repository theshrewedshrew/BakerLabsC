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
apstring Name,Trash;
char Again;



void main()
{
 do{
	do{
			clrscr();
			cout<<"Please enter a name. Enter ZZZ to quit."<<endl;
			cout<<"Name:";
			getline(cin,Name);
		}while(Name!="ZZZ");

		cout<<"Do you want to run this program again(Y/N)?"<<endl;
		cin>>Again;
		getline(cin,Trash);

	 }while(Again=='y' || Again=='Y');
}
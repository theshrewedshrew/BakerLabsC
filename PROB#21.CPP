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
apvector <apstring> Words(20);

int I,J, Count;
apstring Trash, Temp;
char Ans;



void main()
{
	do{
		 Count=0;
		 do{
				clrscr();
				cout<<"Please enter a Name or ZZZ to exit."<<endl;
				cout<<"Name #"<<Count+1<<":";
				getline(cin,Words[Count]);
				if(Words[Count].length()<1)
					{ cout<<"Please enter a name or ZZZ to exit."<<endl;
						cout<<"Press return to continue.";
						getch();
					}
				else
					Count++;

			 }while(Words[Count-1]!="ZZZ" && Count<20);

			// Remove ZZZ from list if Entered 																				if(Words[Count-1]=="ZZZ")
			if(Count<20)
				Words.resize(Count-1);


			// Sort the list
			for(I=0;I<Words.length();I++)
				for(J=I+1;J<Words.length();J++)
					if(Words[J].length()<Words[I].length())
						{	Temp=Words[I];
							Words[I]=Words[J];
							Words[J]=Temp;
						}

			// Display the Names
			clrscr();
			cout<<"List of Names"<<endl;
			for(I=0;I<Words.length();I++)
				cout<<"Names #"<<I+1<<" "<<Words[I]<<endl;


			cout<<endl<<"Do you want to run the program again(Y/N)?";
			cin>>Ans;

			// Clear Buffer for running again and resize Words back to 20.
			getline(cin,Trash);
			Words.resize(20);

		}while(Ans=='y'||Ans=='Y');

}
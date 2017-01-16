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
	int I;
	char Ans;


void main()
{
	do{
			clrscr();
			I=0;
			while(I<7)
				{	switch(I)
					{ case 0:
						case 6: cout<<setw(11)<<"*"<<endl;
										break;
						case 1:
						case 5: cout<<setw(13)<<"* * *"<<endl;
										break;
						case 2:
						case 4: cout<<setw(15)<<"* * * * *"<<endl;
										break;
						case 3: cout<<setw(17)<<"* * * * * * *"<<endl;
					}
					I++;
				 }
			cout<<"Would you like to see the design again (Y/N)?";
			cin>>Ans;
		}while(Ans=='Y'||Ans=='y');


}
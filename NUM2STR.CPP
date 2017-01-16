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
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int Number;
	char *String2;
//Proto Section
	void gr_start( int &, int &, int &);
	void num_2_string(int Number, char * String2 );

void main()
{ clrscr();
 //	gr_start(grdriver, grmode, errorcode);
	cin>>Number;
	num_2_string(Number, String2);
	cout<<"Backward:"<<String2;
getch();

};
void gr_start(int & grdriver, int & grmode, int & errorcode)
{ grdriver = VGA;
	grmode= VGAHI;
	initgraph(&grdriver, &grmode, "C:\\TC\\BGI");
	errorcode=graphresult();
	if (errorcode!=grOk)
		{ clrscr();
			cout<<"Error:"<<errorcode<<endl;
			cout<<"Press Return to Continue.";
			getch();
			exit(1);
		}
};

void num_2_string(int Number, char * String2)
{
	char String[5];
	int  Place, Value;

	Place=0;
	while(Number>0)
	{// cout<<"Num:"<<Number<<endl;
	 Value=Number%10;
	 cout<<"Value:"<<Value<<endl;
	 Number/=10;
	 cout<<"Number:"<<Number<<endl;
	 String[Place]=char(Value+48);
	 cout<<"String:"<<String<<endl;
	 Place++;
	}

	String[Place]='\0';

	cout<<String<<endl;

	String2=strrev(String);
	cout<<"In:"<<String2<<endl;

}
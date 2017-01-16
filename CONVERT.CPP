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

	char Test[40];
	char String[5];
//Proto Section

	void convert(char Test[]);
	void convert2(char String[]);
void main()
{	clrscr();

	convert(Test);
	cout<<endl<<endl<<"Out:"<<Test<<endl;
	convert2(String);
	cout<<endl<<endl<<"Int:"<<String<<endl;
	getch();
}

void convert(char Test[])
{	apstring T_Sent;
	int I;
	cout<<"Please Enter a name:";
	getline(cin,T_Sent);

	for(I=0;I<T_Sent.length();I++)
		Test[I]=T_Sent[I];
	cout<<"In:"<<Test;

}

void convert2(char String[])
{ int Number, Temp, I;
	cout<<"Please Enter a Number:";
	cin>>Number;
	String[0]='0';
	I=Temp=0;
	if (Number==1000)
		{ String[0]=char(49);
			String[1]=char(48);
			String[2]=char(48);
			String[3]=char(48);
			I++;
		}
	else
		{	while(Number>99)
				{	Number-=100;
					Temp++;
					String[I]=char(48+Temp);
				}

			if (Temp!=0)
				{	I++;
					Temp=0;
				}
			if(Number>0)
				while(Number>9)
					{	Number-=10;
						Temp++;
						String[I]=char(48+Temp);
					}
			else
				{	I++;
					String[I]=char(48);
				}
			//if (Temp!=0)
					I++;

			if (Number>=0)

					String[I]=char(48+Number);
		 }
	cout<<"In:"<<String;
	getch();
}
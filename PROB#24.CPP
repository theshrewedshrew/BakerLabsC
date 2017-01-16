// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

//Const Section

//Var Section
apvector <int> Ticket (6);
int I,J,Number,Temp,Tic, Amt;
bool Flag;

void main()
{
	randomize();

	do{ clrscr();
			cout<<"Please enter the number of tickets wanted.";
			cin>>Amt;
			if(Amt<1||Amt>5)
				{	cout<<"Please enter only numbers 1-5."<<endl;
					cout<<"Press return to continue.";
					getch();
				}
		}while(Amt<1||Amt>5);
	for(Tic=0;Tic<Amt;Tic++)
	{
		for(I=0;I<6;I++)
		{


		}

	 //Display the ticket
	 cout<<"Ticket#"<<Tic<<":";
		for(I=0;I<6;I++)
			cout<<Ticket[I]<<" ";
		cout<<endl;

/*







for(Tickets=0;Tickets<1;Tickets++)
{ clrscr();
	for(Number=0;Number<5;Number++)
	{
	for(I=0;I<Ticket.length();I++)
		{ Ticket[I]=random(50)+1;
			for(J=0;J<I;J++)
			 { Flag=false;
			 while (Ticket[J]==Ticket[I])
				 { Ticket[I]=random(50)+1;
					 Flag=true;
				 }
			 if(Flag)
				J=0;
			 }
		}
	 cout<<"Before:";
		for(I=0;I<Ticket.length();I++)
		cout<<Ticket[I]<<" ";
	cout<<endl;


	 for(I=0;I<Ticket.length();I++)
		for(J=I+1;J<Ticket.length();J++)
			if(Ticket[J]<Ticket[I])
				{ Temp=Ticket[I];
					Ticket[I]=Ticket[J];
					Ticket[J]=Temp;
				}


	cout<<"After:";
	for(I=0;I<Ticket.length();I++)
		cout<<Ticket[I]<<" ";
	cout<<endl;

	}
	getch();
 }*/
}
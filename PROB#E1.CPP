// Program: Cash Register
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>
#include <float.h>

bool cont();
double get_prices();
void change(double);

void main()
{cout<<setprecision(2);
// _control87 (MCW_EM, MCW_EM);
 do
 { clrscr();
	 change(get_prices());

 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	bool Value;
	cout << endl << "Do you want to run the program again? (Y/N):";
	clreol();
	Answer = getche();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		Value=true;
	else
		Value=false;

	return Value;
}

double get_prices()
{
	bool Flag;
	double Total, Price;
	Total=0;
	do{ Flag=true;
			gotoxy(2,3);
			clreol();
			cout<<"Please enter a price or 0.0 to end:";
			cin>>Price;
			clreol();
			if((Total+Price)>9.99 || Price == 0.0)
				Flag=false;
			else
				Total+=Price;
			cout<<"Total:"<<Total<<endl;
		}while(Flag);

return (10.00 -Total);
}

void change(double T)
{ int Type, Count;
	double Total, Penny;
	//Penny=0.01;
	Total=T;
	//Total=Total-T;
	gotoxy(2,6);
	Type = 500;
	while(Total>0.00)
	{ Count=0;
		switch (Type)
		{	case 500 : if(Total>=5.00)
									{	Total-=5.00;
										cout<<setw(22)<<"1 Five Dollar Bill"<<endl;
									}
								 Type=100;
								 break;

			case 100 : while(Total>=1.00)
									{ Total-=1.00;
										Count++;
									}
								 if(Count>0)
									{ cout<<setw(6)<<Count<<" One Dollar Bill";
										if (Count>1)
											cout<<"s";
										cout<<endl;
									}
								 Type=25;
								 break;
			case 25	 : while(Total>=.25)
									{ Total-=.25;
										Count++;
									}
								 if(Count>0)
									{ cout<<setw(6)<<Count<<" Quarter";
										if (Count>1)
											cout<<"s";
										cout<<endl;
									}
								 Type=10;
								 break;
			case 10  : /*while(Total>=0.1)
									{	Total=Total -(1.0* 0.1);
										Count++;
									}*/
								 if(Total>=0.1)
									{	Count=Total/0.1;
										Total=Total - (Count*0.1);
									}
								 if(Count>0)
									{ cout<<setw(6)<<Count<<" Dime";
										if (Count>1)
											cout<<"s";
										cout<<endl;
									}
								 Type=5;
								 break;
			case 5	 : while(Total>=.05)
									{ Total-=.05;
										Count++;
									}/*
								 if (Total>=0.05)
										{ Count=Total/.05;
											Total=Total-((Total/0.05)* .05);
										}
										 */
								 if(Count>0)
									{ cout<<setw(6)<<Count<<" Nickle";
										if (Count>1)
											cout<<"s";
										cout<<endl;
									}
								 Type=1;
								 break;
			case 1	 :/* while((Total/0.01)>0 )//&& Count<4)
									{ Total-=Penny;
										Count++;
									}*/
								 if (Total>0.0)
										{ Count=Total/.01;
											Total=Total-((Total/0.01)* .01);
										}
								 if(Count>1)
									{ cout<<setw(6)<<Count<<" Pennies";
										if (Count==1)
											{ clreol();
												cout<<setw(6)<<"1 Penny";
											}
										cout<<endl;
									}

								 Type=0;
								 break;
		 //	default	 :
		}
	}

}

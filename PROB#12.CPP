#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>

char Answer;
apstring L_Name,F_Name,Address;
double Total;
int I,T_Month,D_Month,T_Day,D_Day,T_Year,D_Year;
bool C1,C2,C3,C4,C5,Late;

void main()
{ clrscr();
	cout<<setiosflags(ios::showpoint)<<setprecision(2);
	Total=10.00;
	cout<<"Please enter Today's Month:";
	cin>>T_Month;
	cout<<"Please enter Today's Day:";
	cin>>T_Day;
	cout<<"Please enter Today's Year: (yyyy)";
	cin>>T_Year;
	cout<<"Please enter billing Due Date Month:";
	cin>>D_Month;
	cout<<"Please enter billing Due Date Day:";
	cin>>D_Day;
	cout<<"Please enter billing Due Date Year:";
	cin>>D_Year;
	cout<<"Enter your First Name:";
	cin>>F_Name;
	cout<<"Enter your Last Name:";
	cin>>L_Name;
	cout<<"Please use the underscore ""_"" instead of a space when";
	cout<<" answering"<<endl<<" the following question."<<endl<<endl;
	cout<<"Address:";
	cin>>Address;
	cout<<endl<<"Would you like Advanced Cable service (Y/N):";
	cin>>Answer;
	if (Answer=='Y'|| Answer=='y')
	 { C1=true;
		 Total+=8.00;
		 cout<<endl<<"Would you like the Home Cinema Channel (Y/N):";
		 cin>>Answer;
		 if (Answer=='Y'|| Answer== 'y')
			{ C2=true;
				Total+=2.00;
			}
		 cout<<endl<<"Would you like the Continual Cartoon Channel (Y/N):";
		 cin>>Answer;
		 if (Answer=='Y'|| Answer== 'y')
			{ C3=true;
				Total+=2.00;
			}
		 cout<<endl<<"Would you like the Extra Sports Program ";
		 cout<<"Channel (Y/N):";
		 cin>>Answer;
		 if (Answer=='Y'|| Answer== 'y')
			{ C4=true;
				Total+=2.00;
			}
		 cout<<endl<<"Would you like the Good Music Television ";
		 cout<<"Channel (Y/N):";
		 cin>>Answer;
		 if (Answer=='Y'|| Answer== 'y')
			{ C5=true;
				Total+=0.99;
			}


	 }
	 clrscr();
	 cout<<"Name:"<<F_Name<<" "<<L_Name<<setw(18)<<"Today's Date:"<<setw(3);
	 cout<<T_Month<<"/"<<T_Day<<"/"<<T_Year<<endl<<setw(30)<<"Due Date:";
	 cout<<D_Month<<"/"<<D_Day<<"/"<<D_Year<<endl;

				if (T_Year<D_Year)
						Late=false;
				else if (T_Year==D_Year)
								{
									if (T_Month<D_Month)
											Late=false;
									else if (T_Month==D_Month)
													if (T_Day<=D_Day)
															Late=false;
													else
															{ Late=true;
																Total+=(Total*0.06);
															}
											 else
													 { Late=true;
														 Total+=(Total*0.06);
													 }
								}
						 else
								 { Late=true;
									 Total+=(Total*0.06);
								 }
	 cout<<Address<<endl<<endl<<"Services:"<<endl<<setw(25);
	 cout<<"Standard service"<<setw(23)<<"$10.00"<<endl;
	 if (C1==true)
		 { cout<<setw(31)<<"Advanced Cable Service"<<setw(17)<<"$8.00"<<endl;
			if (C2==true)
					cout<<setw(28)<<"Home Cinema Channel"<<setw(20)<<"$2.00"<<endl;
			if (C3==true)
				{
					cout<<setw(34)<<"Continual Cartoon Channel"<<setw(14);
					cout<<"$2.00"<<endl;
				}
			if (C4==true)
				{
					cout<<setw(37)<<"Extra Sports Program Channel"<<setw(11);
					cout<<"$2.00"<<endl;
				}
			if (C5)
				{
					cout<<setw(38)<<"Good Music Television Channel"<<setw(10);
					cout<<"$0.99"<<endl;
				}
		 }
	 if (Late==false)
				cout<<endl<<setw(26)<<"Total amount due:"<<setw(17)<<"$"<<Total<<endl;
	 else
				cout<<endl<<setw(25)<<"Past Due amount:"<<setw(17)<<"$"<<Total<<endl;

	 cout<<endl<<"Please Press Return to continue.";
	 getch();
};
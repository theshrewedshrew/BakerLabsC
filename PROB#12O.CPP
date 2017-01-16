#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>

char Answer;
apstring L_Name,F_Name,Address;
double Total;
int I,T_Month,D_Month,T_Day,D_Day,T_Year,D_Year;
bool C1,C2,C3,Late;

void main()
{       clrscr();
        Total=7.00;
        cout<<"Please enter Today's Date (mm dd yyyy):";
        cin>>T_Month>>T_Day>>T_Year;
        cout<<"Please enter billing Due Date (mm dd yyyy):";
        cin>>D_Month>>D_Day>>D_Year;
        cout<<"Enter your First Name:";
        cin>>F_Name;
        cout<<"Enter your Last Name:";
        cin>>L_Name;
        cout<<"Please use the underscore ""_"" instead of a space when";
        cout<<" answering"<<endl<<" the following question."<<endl<<endl;
        cout<<"Address:";
        cin>>Address;
        cout<<endl<<"Would you like Cable service (Y/N):";
        cin>>Answer;
        if (Answer=='Y'|| Answer=='y')
					 { C1=true;
						 Total+=4.00;
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
																Total+=(Total*0.05);
															}
											 else
													 { Late=true;
														 Total+=(Total*0.05);
													 }
								}
						 else
								 { Late=true;
									 Total+=(Total*0.05);
								 }
				cout<<Address<<endl<<endl<<"Services:"<<endl<<setw(25)<<"Standard service";
				cout<<setw(10)<<"$7.00"<<endl;
				if (C1)
						cout<<setw(22)<<"Cable Service"<<setw(10)<<"$4.00"<<endl;
				if (C2)
						cout<<setw(28)<<"Home Cinema Channel"<<setw(10)<<"$2.00"<<endl;
				if (C3)
						cout<<setw(34)<<"Continual Cartoon Channel"<<setw(10)<<"$2.00"<<endl;
				if (!Late)
						cout<<endl<<setw(26)<<"Total amount due:"<<setw(4)<<"$"<<Total<<endl;
				else
						cout<<endl<<setw(25)<<"Past Due amount:"<<setw(4)<<"$"<<Total<<endl;

				cout<<endl<<"Please Press Return to continue.";
				getch();
};
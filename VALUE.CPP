
#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>
#include <string.h>
#include <dos.h>
#include <apvector.h>

long value;
char answer[6];
int I,J;

void main()
{ clrscr();
	J=0;
	cin>>value;
	while(value>0)
	{
	 cout<<"Value is:"<<value<<endl;
			if (value>9999)
			 {I=value/10000;
				value=value - (I*10000);
			 }
			else if (value>999)
						{	I=value/1000;
							value=value - (I*1000);
						}
						else if (value>99)
									{	I=value/100;
										value=value-(I*100);
									}
									else if (value>9)
												{	I=value/10;
													value=value-(I*10);
												}
												else
														{ I=value;
															value=value-I;
														}
	 answer[J]=char(I+48);
	 J++;
	 cout<<" I is:"<<I;
		 }

cout<<endl<<"The answer is "<<answer<<endl;
cout<<"The J is "<<J-1;
getch();
}
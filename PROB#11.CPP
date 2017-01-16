// Program: Prob#11
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>


double Eweight;
int Planet;

void main()
{ clrscr();
	cout<<"Please enter your weight on Earth:";
	cin>>Eweight;
	cout<<endl<<endl;
	cout<<"1. Moon"<<endl<<"2. Mercury"<<endl;
	cout<<"3. Venus"<<endl<<"4. Mars"<<endl;
	cout<<"5. Jupiter"<<endl<<"6. Saturn"<<endl;
	cout<<"7. Uranus"<<endl<<"8. Neptune"<<endl;
	cout<<"9. Pluto"<<endl;
	cout<<"Please pick the planet/moon you want to find your weight on:";
	cin>>Planet;
	cout<<endl;
	switch(Planet)
	{
	 case 1: cout<<"On Moon you would weight:"<<Eweight*.16<<endl;
					 break;
	 case 2: cout<<"On Mercury you would weight:"<<Eweight*.37<<endl;
					 break;
	 case 3: cout<<"On Venus you would weight:"<<Eweight*.88<<endl;
					 break;
	 case 4: cout<<"On Mars you would weight:"<<Eweight*.38<<endl;
					 break;
	 case 5: cout<<"On Jupiter you would weight:"<<Eweight*2.64<<endl;
					 break;
	 case 6: cout<<"On Saturn you would weight:"<<Eweight*1.15<<endl;
					 break;
	 case 7: cout<<"On Uranus you would weight:"<<Eweight*1.15<<endl;
					 break;
	 case 8: cout<<"On Neptune you would weight:"<<Eweight*1.12<<endl;
					 break;
	 case 9: cout<<"On Pluto you would weight:"<<Eweight*.04<<endl;
					 break;
	 default: cout<<"Please pick only 1 - 9."<<endl;
	}

	cout<<endl<<"Press return to continue.";
	getch();

} // End of Main

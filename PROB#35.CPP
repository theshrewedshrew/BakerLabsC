// Program: Fibonacci
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

struct Planet
{
	apstring Name, Rev, Rot;
	double Dist, Dia;
	int Sat, Ring;

};

apvector <Planet> Planets(9);

bool cont();
void setdata( apvector <Planet>&);
int pick();
void display(Planet);

void main()
{ clrscr();
  setdata(Planets);
 do
 {
	 display(Planets[pick()]);
 }
 while (cont());
} // End of Main

bool cont()
{ char Answer;
	bool Value;
	cout << endl << "Do you want to run the program again? (Y/N):";
	Answer = getche();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		Value=true;
	else
		Value=false;

	return Value;
}
void setdata( apvector <Planet> &Planets)
{
	Planets[0].Name="Mercury";
	Planets[0].Dist=36;
	Planets[0].Rev="88 days";
	Planets[0].Rot="59 days";
	Planets[0].Dia=3032;
	Planets[0].Sat=0;
	Planets[0].Ring=0;
	Planets[1].Name="Venus";
	Planets[1].Dist=67.24;
	Planets[1].Rev="224.7 days";
	Planets[1].Rot="243 days retrograde";
	Planets[1].Dia=7519;
	Planets[1].Sat=0;
	Planets[1].Ring=0;
	Planets[2].Name="Earth";
	Planets[2].Dist=92.9;
	Planets[2].Rev="365.2 Days";
	Planets[2].Rot="23 hours 56 minutes 4 seconds";
	Planets[2].Dia=7926.2;
	Planets[2].Sat=1;
	Planets[2].Ring=0;
	Planets[3].Name="Mars";
		Planets[3].Dist=141.71;
		Planets[3].Rev="687 days";
		Planets[3].Rot="24 hours 37 minutes";
		Planets[3].Dia=4194;
		Planets[3].Sat=2;
	Planets[3].Ring=0;
	Planets[4].Name="Jupiter";
		Planets[4].Dist=483.88;
		Planets[4].Rev="11.86 years";
		Planets[4].Rot="9 hours 55 minutes 30 seconds";
		Planets[4].Dia=88736;
		Planets[4].Sat=16;
	Planets[4].Ring=1;
	Planets[5].Name="Saturn";
		Planets[5].Dist=887.14;
		Planets[5].Rev="29.46 years";
		Planets[5].Rot="10 hours 40 minutes 24 seconds";
		Planets[5].Dia=74978;
		Planets[5].Sat=18;
	Planets[5].Ring=1000;
	Planets[6].Name="Uranus";
		Planets[6].Dist=1783.98;
		Planets[6].Rev="84 years";
		Planets[6].Rot="16.8 hours retrograde";
		Planets[6].Dia=32193;
		Planets[6].Sat=15;
	Planets[6].Ring=11;
	Planets[7].Name="Neptune";
		Planets[7].Dist=2796.46;
		Planets[7].Rev="165 years";
		Planets[7].Rot="16 hours 11 minutes";
		Planets[7].Dia=30775;
		Planets[7].Sat=8;
	Planets[7].Ring=4;
	Planets[8].Name="Pluto";
		Planets[8].Dist=3666;
		Planets[8].Rev="248 years";
		Planets[8].Rot="6 days 9 hours 18 minutes";
		Planets[8].Dia=1423;
		Planets[8].Sat=1;
	Planets[8].Ring=0;
};

int pick()
{
	int Ans;
	do{
		clrscr();

		cout<<"1. Mercury"<<endl;
		cout<<"2. Venus"<<endl;
		cout<<"3. Earth"<<endl;
		cout<<"4. Mars"<<endl;
		cout<<"5. Jupiter"<<endl;
		cout<<"6. Saturn"<<endl;
		cout<<"7. Uranus"<<endl;
		cout<<"8. Naptune"<<endl;
		cout<<"9. Pluto"<<endl;
		cin>>Ans;

   	  }while(Ans<0 || Ans<9);
	return Ans-1;

};

void display(Planet P)
{
	cout<<"Name:"<<P.Name<<endl;
	cout<<"Distance from Sun:"<<P.Dist<<" millions of miles."<<endl;
	cout<<"Period of Solar Revolution:"<<P.Rev<<endl;
	cout<<"Planetary Rotation Period:"<<P.Rot<<endl;
	cout<<"Equatorial Diameter:"<<P.Dia<<endl;
	cout<<"Satellites:"<<P.Sat<<endl;
	cout<<"Rings:"<<P.Ring<<endl<<endl;
};
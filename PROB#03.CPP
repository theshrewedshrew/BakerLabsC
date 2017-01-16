// Program: Prob#02
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

	// Do I need these Variables???
double Sweater, Skirt, Blouse, Boots, Bracelet, EarRings;
double Base_Total, Sales_Total;
double Discount;

void main()
{ clrscr();

	// Why do I need these???
	cout<<setiosflags(ios::showpoint)<<setprecision(2);



	Sweater=65.00;
	Skirt=28.50;
	Blouse=22.95;
	Boots=79.35;
	Bracelet=41.00;
	EarRings=60.00;

	Discount=.85; // Why .85???



	// Is this the only place to do the math???
	Base_Total=Sweater+Skirt+Blouse+Boots+Bracelet+EarRings;
	Sales_Total=((Sweater+Skirt+Blouse+Boots)*Discount)+Bracelet+EarRings;


	//Next I will write the output in two different ways...
	cout<<"Before the Sale costs"<<endl;
	cout<<setw(14)<<"Sweater:$"<<Sweater<<endl;
	cout<<setw(14)<<"Skirt:$"<<Skirt<<endl;
	cout<<setw(14)<<"Blouse:$"<<Blouse<<endl;
	cout<<setw(14)<<"Boots:$"<<Boots<<endl;
	cout<<setw(14)<<"Bracelet:$"<<Bracelet<<endl;
	cout<<setw(14)<<"EarRings:$"<<EarRings<<endl;
	cout<<endl<<setw(14)<<"Total:$"<<Base_Total<<endl<<endl;
	cout<<"Sale costs"<<endl;
	cout<<setw(14)<<"Sweater:$"<<Sweater*Discount<<endl;
	cout<<setw(14)<<"Skirt:$"<<Skirt*Discount<<endl;
	cout<<setw(14)<<"Blouse:$"<<Blouse*Discount<<endl;
	cout<<setw(14)<<"Boots:$"<<Boots*Discount<<endl;

	// why not Discount here??
	cout<<setw(14)<<"Bracelet:$"<<Bracelet<<endl;
	cout<<setw(14)<<"EarRings:$"<<EarRings<<endl;

	cout<<endl<<setw(14)<<"Total:$"<<Sales_Total<<endl<<endl;

	cout<<endl<<"Please press return to continue.";
	getch();





	// Second Way...
	clrscr();
	cout<<"Before the Sale costs"<<endl;
	cout<<setw(14)<<"Sweater:$"<<Sweater<<endl;
	cout<<setw(14)<<"Skirt:$"<<Skirt<<endl;
	cout<<setw(14)<<"Blouse:$"<<Blouse<<endl;
	cout<<setw(14)<<"Boots:$"<<Boots<<endl;
	cout<<setw(14)<<"Bracelet:$"<<Bracelet<<endl;
	cout<<setw(14)<<"EarRings:$"<<EarRings<<endl;
	cout<<endl<<setw(14)<<"Total:$"<<Base_Total<<endl<<endl;
	cout<<endl<<"Please press return to continue.";
	getch();

	clrscr();
	cout<<"Sale costs"<<endl;
	cout<<setw(14)<<"Sweater:$"<<Sweater*Discount<<endl;
	cout<<setw(14)<<"Skirt:$"<<Skirt*Discount<<endl;
	cout<<setw(14)<<"Blouse:$"<<Blouse*Discount<<endl;
	cout<<setw(14)<<"Boots:$"<<Boots*Discount<<endl;

	// why not Discount here??
	cout<<setw(14)<<"Bracelet:$"<<Bracelet<<endl;
	cout<<setw(14)<<"EarRings:$"<<EarRings<<endl;

	cout<<endl<<setw(14)<<"Total:$"<<Sales_Total<<endl<<endl;

	// What other ways could I have changed the code??


	cout<<endl<<"Please press return to continue.";
	getch();
} // End of Main


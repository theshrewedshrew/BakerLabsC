// Roman - Aribic Number Conversion
// Program By: Bryan Baker

#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>

// Prototype Section
bool CONTINUE ();
void MENU();
void FIND_ROMAN();
void FIND_ARIBIC();

// Varaible Section
apstring Roman_In, Roman_Out;
int Aribic_In, Aribic_Out, I;
char Answer;


void main()
{ clrscr();
 do
 { MENU();
 }
 while (CONTINUE());
} // End of Main

bool CONTINUE()
{ cout << endl << "Do you want to convert another number? (Y/N)";
	Answer = getche();
	if (Answer == 'Y' || Answer == 'y')
		return true;
	else	return false;
}

void MENU ()
{ do
	{
	clrscr();
	Roman_In="";
	Roman_Out="";
	cout <<"Number Converter"<<endl<<endl;
	cout <<"Please Enter :"<<endl;
	cout <<"A: Aribic to Roman"<< endl;
	cout <<"B: Roman to Aribic"<< endl;
	Answer = getche();
	}
	while (Answer != 'A' && Answer != 'a' && Answer != 'B' && Answer != 'b');

	if (Answer == 'A' || Answer == 'a')
		FIND_ROMAN();
	else
		FIND_ARIBIC();
}

void FIND_ROMAN()
{
 do
 {
 cout<< endl << endl <<"Please Enter the Aribic Number (0 - 10000):";
 cin>>Aribic_In;
 }
 while (Aribic_In < 0);
 while (Aribic_In > 0)
 {
	if (Aribic_In- 5000 >= 0)
		{ Aribic_In-=5000;Roman_Out+='Z';}
		else if (Aribic_In- 1000 >= 0)
		{ Aribic_In-=1000;Roman_Out+='M';}
		else if (Aribic_In- 500 >= 0)
		{ Aribic_In-=500;Roman_Out+='D';}
		else if (Aribic_In- 100 >= 0)
		{ Aribic_In-=100;Roman_Out+='C';}
		else if (Aribic_In- 50 >= 0)
		{ Aribic_In-=50;Roman_Out+='L';}
		else if (Aribic_In- 10 >= 0)
		{ Aribic_In-=10;Roman_Out+='X';}
		else if (Aribic_In- 5 >= 0)
		{ Aribic_In-=5;Roman_Out+='V';}
		else if (Aribic_In- 1 >= 0)
		{ Aribic_In-=1;Roman_Out+='I';}
		else Aribic_In = -1;
 }
	cout << endl<<"The Roman equivalent is:"<<Roman_Out<<endl;
}


void FIND_ARIBIC()
{
 do
 {
 cout<< endl << endl <<"Please Enter the Roman Number (1 - 10000):";
 cin>>Roman_In;
 }
 while (Roman_In !="");


}
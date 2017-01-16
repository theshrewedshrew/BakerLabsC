// Cable Sales
// Programed By: Bryan J. Baker

#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>
#include <ctype.h>
//#include <bool.h>

apstring F_Name, L_Name, Address1, Address2;
double Total;
char Answer;
int in;

int char_to_int(char);
char int_to_char(int);

void main()
{	clrscr();
	cout<<"Please Enter a char digit";
	cin>>Answer;
	cin>>in;
	cout<<10+char_to_int(Answer);

	cout<<endl<<char(tolower(Answer));
	cout<<endl<<"test"+int_to_char(in);
	getch();

};

int char_to_int(char ch)
{
	return ch-'0';
}

char int_to_char (int in)
{
	return in+'0';

}
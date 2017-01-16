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
long Value;

apstring itos(int);
apstring ltos (long);

bool cont();

void main()
{ clrscr();
 do
 {
	cout<<"Please enter Value to convert to an Apstring:";
	cin>>Value;
	cout<<"Your apsrting is:"<<ltos(Value)<<"."<<endl;
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



apstring itos (int Val)
{ apstring Answer, Ans;
	int Base, Pos, I;

	Ans = "     ";
	Answer="";
	Pos = 4;
	Base = 10;

	if (Val<0)
	{
		Val=abs(Val);
		Answer+='-';
	}

	while(Val>0)
	{
		Ans[Pos]=char((Val%Base)+48);
		Val-=(Val%Base);
		Val/=Base;
		Pos--;
	}

	for(I=0;I<=4;I++)
	 if(Ans[I]!=' ')
		Answer+=Ans[I];

	return Answer;
};

apstring ltos (long Val)
{ apstring Answer, Ans;
	long Base, Pos, I;

	Ans = "            ";
	Answer="";
	Pos = 11;
	Base = 10;

	if (Val<0)
	{
		Val=labs(Val);
		Answer+='-';
	}

	while(Val>0)
	{
		Ans[Pos]=char((Val%Base)+48);
		Val-=(Val%Base);
		Val/=Base;
		Pos--;
	}

	for(I=0;I<=11;I++)
	 if(Ans[I]!=' ')
		Answer+=Ans[I];

	return Answer;
};
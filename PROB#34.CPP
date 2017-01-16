// Program: Prob#34
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

struct Player
{ apstring Name;
	int Score;
	apstring Date;
};

apvector <Player> Players(10);

bool cont();
void collect_data (apvector <Player> &);
void sort ( apvector <Player> &);
void display_players( apvector <Player>);


void main()
{ clrscr();
 do
 {   collect_data(Players);
		 sort(Players);
		 display_players(Players);
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

void collect_data( apvector<Player> & Players)
{  int I;
	 apstring Trash;

	for(I=0;I<10;I++)
	{
		clrscr();
		do{
				gotoxy(2,2);
				cout<<"Players Name:";
				getline(cin,Players[I].Name);
			}while(Players[I].Name.length()==0);
		do{
				gotoxy(2,3);
				cout<<"Players Score:";
				cin>>Players[I].Score;
			}while(Players[I].Score<0);

		getline(cin,Trash);
		do{
				gotoxy(2,4);
				cout<<"Players Score Date:";
				getline(cin,Players[I].Date);
			}while(Players[I].Date.length()==0);
	}
};

void sort ( apvector <Player> &Players)
{  int I,J;
	 Player Temp;

	for(I=0;I<10;I++)
		for(J=I+1; J<10;J++)
		{
			if ( Players[I].Score<Players[J].Score)
				{ Temp= Players[I];
					Players[I] = Players[J];
					Players[J] = Temp;
				}
		}
};

void display_players( apvector <Player> Players)
{ int I;
	for(I=0;I<10;I++)
	 {
		cout<<"Name:"<<Players[I].Name<<" Score:"<<Players[I].Score<<" Date:";
		cout<<Players[I].Date<<endl;
		}
	 cout<<endl<<endl;
};
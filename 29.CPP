// Shane Crawford
// Computer Science I - 7th Period
// Mr. Baker
// Program:
#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>
#include <apvector.h>
#include <apmatrix.h>
#include <stdlib.h>
// Constants

// Global Variables
apvector <apstring> Words (20);
apvector <apstring> Letters (20);
bool Key [20][20];
int Col;
int Row;
int x;
int y;
int a;
bool Flag;
int TotLetters;
int Word_Num;
char Ans;
int SizeX;
int SizeY;
int NumWords;

// Prototypes
void size_get (int&, int&);
void word_get (int&, int, int);
void horizontal (int, int, apstring, int, int, int, bool);
void vertical (int, int, apstring, int, int, int, bool);
void down_and_right (int, int, apstring, int, int, int, bool);
void up_and_left (int, int, apstring, int, int, int, bool);
void backwards_horizontal (int, int, apstring, int, int, int, bool);
void backwards_vertical (int, int, apstring, int, int, int, bool);
void up_and_right (int, int, apstring, int, int, int, bool);
void down_and_left (int, int, apstring, int, int, int, bool);
void display (int, int, int, int);



void main ()
{
clrscr();
randomize();
clrscr();
size_get (SizeX, SizeY);
do
	{ for(a=0;a<20;a++)
		Letters[a]="";
word_get(NumWords, SizeX, SizeY);
for (Word_Num=0;Word_Num<NumWords;Word_Num++)
	switch(0)
		{case 0 : horizontal (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		 case 1 : vertical (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		 case 2 : down_and_right (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		 case 3 : up_and_left (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		 case 4 : backwards_horizontal (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		 case 5 : backwards_vertical (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		 case 6 : up_and_right (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		 case 7 : down_and_left (SizeX, SizeY, Words[Word_Num], x, y, a, Flag);
							break;
		}
	}while (Ans=='y'||Ans=='Y');


display(Col, Row, SizeX, SizeY);
getch();
};

void size_get (int& SizeX, int& SizeY)
	{ cout <<"Enter the number of columns           >>";
		cin >>SizeY;
		cout <<"Enter the number of rows              >>";
		cin >>SizeX;
	};

void word_get (int& NumWords, int SizeX, int SizeY)
		{do
			{	cout <<"How many words?     >>";
				cin >>NumWords;
			}while (NumWords<1||NumWords>21);
		 for (Col=0;Col<NumWords;Col++)
			{Words[Col]=".!";}
/*		{ do
			{ cout <<"Enter name number " <<Col+1 <<"     >>";
				cin >>Words[Col];
				TotLetters=TotLetters+Words[Col].length();
			} while (Words[Col].length()>8||Words[Col].length()<2);}
*/
	clrscr();
		for (Col=0;Col<SizeY;Col++)
			{for (Row=0;Row<SizeX;Row++)
				{Letters[Col]=Letters[Col] + char(random(25)+65);
				Key[Col][Row]=false;
			}
		}
	};

void horizontal (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{do
			{ x=random(SizeX-(Word.length()-1));
				y=random(SizeY);
				Flag=true;
				for(a=0;a<Word.length();a++)
					{ if(Key[x+a][y])
						Flag=false;
					}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x+a][y]=Word[a];
				Key[x+a][y]=true;
			}
	 cout <<"Made It" <<endl;
	};

void vertical (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{ do
			{ x=random(SizeX);
				y=random(SizeY-(Word.length()-1));
				Flag=true;
				for(a=0;a<Word.length();a++)
					{	if(Key[x+a][y])
						Flag=false;
					}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x+a][y]=Word[a];
				Key[x+a][y]=true;
			}
	};

void down_and_right (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{	do
			{x=random(SizeX);
			 y=random(SizeY-(Word.length()-1));
			 Flag=true;
			 for(a=0;a<Word.length();a++)
				{ if(Key[x+a][y+a])
					Flag=false;
				}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x+a][y+a]=Word[a];
				Key[x+a][y+a]=true;
			}
	};

void up_and_left (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{	do
			{ x=random(SizeX-(Word.length()-1))+(Word.length()-1);
				y=random(SizeY-(Word.length()-1))+(Word.length()-1);
				Flag=true;
				for(a=0;a<Word.length();a++)
					{ if(Key[x-a][y-a])
						Flag=false;
					}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x-a][y-a]=Word[a];
				Key[x-a][y-a]=true;
			}
	};

void backwards_horizontal (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{	do
			{ x=random(SizeX);
				y=random(SizeY-(Word.length()-1))+(Word.length()-1);
				Flag=true;
				for(a=0;a<Word.length();a++)
					{ if(Key[x][y-a])
						Flag=false;
					}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x][y-a]=Word[a];
				Key[x][y-a]=true;
			}
	};

void backwards_vertical (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{	do
			{ x=random(SizeX-(Word.length()-1))+(Word.length()-1);
				y=random(SizeY);
				Flag=true;
				for(a=0;a<Word.length();a++)
					{ if(Key[x-a][y])
						Flag=false;
					}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x-a][y]=Word[a];
				Key[x-a][y]=true;
			}
	};

void up_and_right (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{ do
			{ x=random(SizeX-((Word.length())-1))+(Word.length()-1);
				y=random(SizeY-(Word.length()-1));
				Flag=true;
				for(a=0;a<Word.length();a++)
					{ if(Key[x-a][y+a])
						Flag=false;}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x-a][y+a]=Word[a];
				Key[x-a][y+a]=true;
			}
	};

void down_and_left (int SizeX, int SizeY, apstring Word, int x, int y, int a, bool Flag)
	{	do
			{ x=random(SizeX-(Word.length()-1));
				y=random(SizeY-(Word.length()-1))+(Word.length()-1);
				Flag=true;
				for(a=0;a<Word.length();a++)
					{ if(Key[x-a][y+a])
						Flag=false;
					}
			}while (!Flag);
		for(a=0;a<Word.length();a++)
			{ Letters[x+a][y-a]=Word[a];
				Key[x+a][y-a]=true;
			}
	};

void display (int Col, int Row, int SizeX, int SizeY)
	{ for(Col=0;Col<SizeY;Col++)
			{for(Row=0;Row<SizeX;Row++)
				{	cout <<Letters[Col][Row] <<" ";
				}
		cout <<endl;
			}

		for(Col=0;Col<NumWords;Col++)
			{ gotoxy(60,Col+1);
				cout <<Words[Col];
			}
	};
// WordFind
// Programed By: Bryan J. Baker

#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>

int KeyPress();
void get_data();
void init_grids();
void place_words();
void right();
void left();
void up();
void down();
void up_right();
void down_right();
void up_left();
void down_left();
void print_grids();
void preset_words();



//const Grid_Size_X = 20;
//const Grid_Size_Y = 20;
const Max_Words=4;
int X,Y,I,Place,Error,Grid_Size_X=20;
int  Grid_Size_Y=20;
//apmatrix <char> Char_Grid(Grid_Size_X, Grid_Size_Y);
//apmatrix <bool> Bool_Grid(Grid_Size_X, Grid_Size_Y);
//apvector <apstring> Words(Max_Words);
//apstring Trash;
//bool Flag;


void main()
{
	clrscr();
//	for (I=0;I<10;I++)
	do
	{
	X=KeyPress();
	cout<<"value:"<<X<<endl;
	} while(X!=13);
//	get_data();
//	init_grids();
//	preset_words();
//	place_words();
//	print_grids();

getch();
}

int KeyPress()
{ while(!kbhit());
	return getch();
}
/*
void get_data()
{do{
		gotoxy(5,2);
		cout<<setw(30)<<"";
		gotoxy(5,2);
		cout<<"Please Enter Puzzle Width:";
		cin>>Grid_Size_Y;
		getline(cin,Trash);
	 }while((Grid_Size_Y<2)||(Grid_Size_Y>20));
 do{
		gotoxy(5,4);
		cout<<setw(30)<<"";
		gotoxy(5,4);
		cout<<"Please Enter Puzzle Higth:";
		cin>>Grid_Size_X;
		getline(cin,Trash);
	 }while((Grid_Size_X<2)||(Grid_Size_X>20));

}
void init_grids()
{
	for (X=0;X<Grid_Size_X;X++)
	for (Y=0;Y<Grid_Size_Y;Y++)
			{	Char_Grid[X][Y]=char(random(26)+65);
				Bool_Grid[X][Y]=false;
			}
}

void place_words()
{
		for (I=0;I<Max_Words;I++)
		 {Error=0;
			switch(/*random(8)+*//*1)
		 { case 1:right();break;
			 case 2:left();break;
			 case 3:up();break;
			 case 4:down();break;
			 case 5:up_right();break;
			 case 6:down_right();break;
			 case 7:up_left();break;
			 case 8:down_left();break;
		 }
		 }
}



void right()
{	gotoxy(70,I+5);
	cout<<Words[I];
 do	{
			Error++;
			Flag = true;
			X=random(Grid_Size_X);
			Y=random(Grid_Size_Y-Words[I].length());
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X][Y+Place])
							 { Flag=false;
								 break;
							 }

		}while(!Flag || Error<50);
		cout<<Error;
		getch();
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X][Y+Place]=Words[I][Place];
				Bool_Grid[X][Y+Place]=true;
			}
}
void left()
{ gotoxy(70,I+5);
	cout<<Words[I];
 do	{
			Flag = true;
			X=random(Grid_Size_X);
			Y=random(Grid_Size_Y-Words[I].length())+Words[I].length();
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X][Y-Place])
							 { Flag=false;
								 break;
							 }

		}while(!Flag);
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X][Y-Place]=Words[I][Place];
				Bool_Grid[X][Y-Place]=true;
			}
}

void up()
{ gotoxy(70,I+5);
	cout<<Words[I];
 do	{
			Flag = true;
			X=random(Grid_Size_X-Words[I].length())+Words[I].length();
			Y=random(Grid_Size_Y);
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X-Place][Y])
							 { Flag=false;
								 break;
							 }

		}while(!Flag);
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X-Place][Y]=Words[I][Place];
				Bool_Grid[X-Place][Y]=true;
			}
}
void down()
{ gotoxy(70,I+5);
	cout<<Words[I];
 do	{
			Flag = true;
			X=random(Grid_Size_X-Words[I].length());
			Y=random(Grid_Size_Y);
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X+Place][Y])
							 { Flag=false;
								 break;
							 }

		}while(!Flag);
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X+Place][Y]=Words[I][Place];
				Bool_Grid[X+Place][Y]=true;
			}
}
void up_right()
{ gotoxy(70,I+5);
	cout<<Words[I];
 do	{
			Flag = true;
			X=random(Grid_Size_X-Words[I].length())+Words[I].length();
			Y=random(Grid_Size_Y-Words[I].length());
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X-Place][Y+Place])
							 { Flag=false;
								 break;
							 }

		}while(!Flag);
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X-Place][Y+Place]=Words[I][Place];
				Bool_Grid[X-Place][Y+Place]=true;
			}
}
void down_right()
{ gotoxy(70,I+5);
	cout<<Words[I];
 do	{
			Flag = true;
			X=random(Grid_Size_X-Words[I].length());
			Y=random(Grid_Size_Y-Words[I].length());
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X+Place][Y+Place])
							 { Flag=false;
								 break;
							 }

		}while(!Flag);
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X+Place][Y+Place]=Words[I][Place];
				Bool_Grid[X+Place][Y+Place]=true;
			}
}
void up_left()
{ gotoxy(70,I+5);
	cout<<Words[I];
 do	{
			Flag = true;
			X=random(Grid_Size_X-Words[I].length())+Words[I].length();
			Y=random(Grid_Size_Y-Words[I].length())+Words[I].length();
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X-Place][Y-Place])
							 { Flag=false;
								 break;
							 }

		}while(!Flag);
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X-Place][Y-Place]=Words[I][Place];
				Bool_Grid[X-Place][Y-Place]=true;
			}
}
void down_left()
{ gotoxy(70,I+5);
	cout<<Words[I];

 do	{
			Flag = true;
			X=random(Grid_Size_X-Words[I].length());
			Y=random(Grid_Size_Y-Words[I].length())+Words[I].length();
			for	(Place=0;Place<Words[I].length();Place++)
					 if (Bool_Grid[X+Place][Y-Place])
							 { Flag=false;
								 break;
							 }

		}while(!Flag);
 for (Place=0;Place<Words[I].length();Place++)
			{	Char_Grid[X+Place][Y-Place]=Words[I][Place];
				Bool_Grid[X+Place][Y-Place]=true;
			}
}


void print_grids()
{ clrscr();
	gotoxy(70,3);
	cout<<"Words";
	gotoxy(1,1);
	for (X=0;X<Grid_Size_X;X++)
	{
	for (Y=0;Y<Grid_Size_Y;Y++)
					cout<<Char_Grid[X][Y]<<" ";

	cout<<endl;
	}
}

void preset_words()
{
 Words[0]="water";
 Words[1]="computer";
 Words[2]="test";
 Words[3]="programs";
}*/
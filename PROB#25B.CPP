// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

//Const Section

//Var Section

apvector <apstring> Words;
apvector <apstring> Puzzle_Grid(20);
apmatrix <bool> Bool_Grid(20,20);
int I,J,X,Y,W, Num_Words, Total_Word_Size, Biggest_Word;
int Grid_Size_X;
int Grid_Size_Y;
apstring Trash;
double R;
bool Again;

void main()
{	randomize();
	Biggest=1;
	do{ clrscr();
			cout<<"Please enter the number of words in the puzzle";
			cout<<" (Min 0 & Max 20):";
			cin>>Num_Words;
		} while(Num_Words<0 || Num_Words>20);
	Words.resize(Num_Words);
	getline(cin,Trash);
	for(I=0;I<Num_Words;I++)
		{ //Words[I]="1***2";
			R++;
			do {
					cout<<"Please enter a word of size from 2 to 8";
					cout<<" letters long in ALL CAPS."<<endl;
					cout<<"#"<<R<<":";
					getline(cin,Words[I]);
				 }while(Words[I].length()<2 || Words[I].length()>8);
			Total_Word_Size+=Words[I].length();
			if(Biggest_Word<Words[I].length())
					Biggest_Word=Words[I].length();
		}

	do{ clrscr();
			cout<<"Please enter the size of the Width of the puzzle (2 to 20):";
			cin>>Grid_Size_X;

	clrscr();

	for(X=0;X<20;X++)
	 for(Y=0;Y<20;Y++)
		{ Puzzle_Grid[X]+=char(random(26)+65);
			Bool_Grid[X][Y]=false;
		}
	cout<<endl<<endl;


	for(I=0;I<Num_Words;I++)
		switch(random(8))
		{	case  0: //Down
							do{	X=random(20-Words[I].length()-1);
									Y=random(20);
									Again=false;
									for(J=0;J<Words[I].length();J++)
										if(Bool_Grid[X+J][Y]==true && Puzzle_Grid[X+J][Y]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<Words[I].length();J++)
									{	Puzzle_Grid[X+J][Y]=Words[I][J];
										Bool_Grid[X+J][Y]=true;
									}
							break;
			case  1: //Right
							do{	X=random(20);
									Y=random(20-Words[I].length()-1);
									Again=false;
									for(J=0;J<Words[I].length();J++)
										if(Bool_Grid[X][Y+J]==true && Puzzle_Grid[X][Y+J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<Words[I].length();J++)
									{	Puzzle_Grid[X][Y+J]=Words[I][J];
										Bool_Grid[X][Y+J]=true;
									}
							break;
			 case  2: //Up
							do{	X=random(20-Words[I].length()-1)+Words[I].length()-1;
									Y=random(20);
									Again=false;
									for(J=Words[I].length()-1;J>=0;J--)
										if(Bool_Grid[X-J][Y]==true && Puzzle_Grid[X-J][Y]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=Words[I].length()-1;J>=0;J--)
									{	Puzzle_Grid[X-J][Y]=Words[I][J];
										Bool_Grid[X-J][Y]=true;
									}
							break;
			 case  3: //Left
							do{	X=random(20);
									Y=random(20-Words[I].length()-1)+Words[I].length()-1;
									Again=false;
									for(J=Words[I].length()-1;J>=0;J--)
										if(Bool_Grid[X][Y-J]==true && Puzzle_Grid[X][Y-J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=Words[I].length()-1;J>=0;J--)
									{	Puzzle_Grid[X][Y-J]=Words[I][J];
										Bool_Grid[X][Y-J]=true;
									}
							break;
			 case  4: //Up and Right
							do{	X=random(20-Words[I].length()-1)+Words[I].length()-1;
									Y=random(20-Words[I].length()-1);
									Again=false;
									for(J=0;J<Words[I].length();J++)
										if(Bool_Grid[X-J][Y+J]==true && Puzzle_Grid[X-J][Y+J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<Words[I].length();J++)
									{	Puzzle_Grid[X-J][Y+J]=Words[I][J];
										Bool_Grid[X-J][Y+J]=true;
									}
							break;
			 case  5: //Down and Right
							do{	X=random(20-Words[I].length()-1);
									Y=random(20-Words[I].length()-1);
									Again=false;
									for(J=0;J<Words[I].length();J++)
										if(Bool_Grid[X+J][Y+J]==true && Puzzle_Grid[X+J][Y+J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<Words[I].length();J++)
									{	Puzzle_Grid[X+J][Y+J]=Words[I][J];
										Bool_Grid[X+J][Y+J]=true;
									}
							break;
			 case  6: //Down and Left
							do{	X=random(20-Words[I].length()-1);
									Y=random(20-Words[I].length()-1)+Words[I].length()-1;
									Again=false;
									for(J=0;J<Words[I].length();J++)
										if(Bool_Grid[X+J][Y-J]==true && Puzzle_Grid[X+J][Y-J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<Words[I].length();J++)
									{	Puzzle_Grid[X+J][Y-J]=Words[I][J];
										Bool_Grid[X+J][Y-J]=true;
									}
							break;
			 case  7: //Up and Left
							do{	X=random(20-Words[I].length()-1)+Words[I].length()-1;
									Y=random(20-Words[I].length()-1)+Words[I].length()-1;
									Again=false;
									for(J=Words[I].length()-1;J>=0;J--)
										if(Bool_Grid[X-J][Y-J]==true && Puzzle_Grid[X-J][Y-J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=Words[I].length()-1;J>=0;J--)
									{	Puzzle_Grid[X-J][Y-J]=Words[I][J];
										Bool_Grid[X-J][Y-J]=true;
									}
							break;

		}
	for(X=0;X<20;X++)
	 { for(Y=0;Y<20;Y++)
			cout<<Puzzle_Grid[X][Y]<<" ";
		 cout<<endl;
	 }
	for(X=0;X<Num_Words;X++)
	 { gotoxy(50,X+3);
		 R=X;
		 cout<<R+1<<" "<<Words[X];
	 }
	 gotoxy(10,1);
	 cout<<"Word Find Pizzle";
	 gotoxy(50,1);
	 cout<<"Words";
	 gotoxy(5,24);
	 cout<<"Please Press Return to Continue";
	 getch();
	 clrscr();
	 cout<<endl<<endl;
	 for(X=0;X<20;X++)
	 { for(Y=0;Y<20;Y++)
			if(Bool_Grid[X][Y]==true)
				cout<<Puzzle_Grid[X][Y]<<" ";
			else
				cout<<"  ";
		 cout<<endl;
	 }
	for(X=0;X<Num_Words;X++)
	 { gotoxy(50,X+3);
		 R=X;
		 cout<<R+1<<" "<<Words[X];
	 }
	 gotoxy(10,1);
	 cout<<"Word Find Pizzle Answers";
	 gotoxy(50,1);
	 cout<<"Words";
	 gotoxy(5,24);
	 cout<<"Please Press Return to Continue";
	 getch();
}
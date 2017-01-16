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

apvector <apstring> Words(20);
apvector <apstring> Puzzle_Grid(20);
apmatrix <bool> Bool_Grid(20,20);
int I,J,X,Y,W;
double R;
bool Again;

void main()
{	clrscr();
	randomize();
	for(I=0;I<20;I++)
		{ //Words[I]="1***2";
			R++;
			do {
					cout<<"Please enter a 5 letter word #"<<R<<":";
					getline(cin,Words[I]);
				 }while(Words[I].length()!=5);
		}
	clrscr();

	for(X=0;X<20;X++)
	 for(Y=0;Y<20;Y++)
		{ Puzzle_Grid[X]+=char(random(26)+65);
			Bool_Grid[X][Y]=false;
		}
	cout<<endl<<endl;


	for(I=0;I<20;I++)
		switch(random(8))
		{	case  0: //Down
							do{	X=random(20-4);
									Y=random(20);
									Again=false;
									for(J=0;J<5;J++)
										if(Bool_Grid[X+J][Y]==true && Puzzle_Grid[X+J][Y]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<5;J++)
									{	Puzzle_Grid[X+J][Y]=Words[I][J];
										Bool_Grid[X+J][Y]=true;
									}
							break;
			case  1: //Right
							do{	X=random(20);
									Y=random(20-4);
									Again=false;
									for(J=0;J<5;J++)
										if(Bool_Grid[X][Y+J]==true && Puzzle_Grid[X][Y+J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<5;J++)
									{	Puzzle_Grid[X][Y+J]=Words[I][J];
										Bool_Grid[X][Y+J]=true;
									}
							break;
			 case  2: //Up
							do{	X=random(20-4)+4;
									Y=random(20);
									Again=false;
									for(J=4;J>=0;J--)
										if(Bool_Grid[X-J][Y]==true && Puzzle_Grid[X-J][Y]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=4;J>=0;J--)
									{	Puzzle_Grid[X-J][Y]=Words[I][J];
										Bool_Grid[X-J][Y]=true;
									}
							break;
			 case  3: //Left
							do{	X=random(20);
									Y=random(20-4)+4;
									Again=false;
									for(J=4;J>=0;J--)
										if(Bool_Grid[X][Y-J]==true && Puzzle_Grid[X][Y-J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=4;J>=0;J--)
									{	Puzzle_Grid[X][Y-J]=Words[I][J];
										Bool_Grid[X][Y-J]=true;
									}
							break;
			 case  4: //Up and Right
							do{	X=random(20-4)+4;
									Y=random(20-4);
									Again=false;
									for(J=0;J<5;J++)
										if(Bool_Grid[X-J][Y+J]==true && Puzzle_Grid[X-J][Y+J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<5;J++)
									{	Puzzle_Grid[X-J][Y+J]=Words[I][J];
										Bool_Grid[X-J][Y+J]=true;
									}
							break;
			 case  5: //Down and Right
							do{	X=random(20-4);
									Y=random(20-4);
									Again=false;
									for(J=0;J<5;J++)
										if(Bool_Grid[X+J][Y+J]==true && Puzzle_Grid[X+J][Y+J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<5;J++)
									{	Puzzle_Grid[X+J][Y+J]=Words[I][J];
										Bool_Grid[X+J][Y+J]=true;
									}
							break;
			 case  6: //Down and Left
							do{	X=random(20-4);
									Y=random(20-4)+4;
									Again=false;
									for(J=0;J<5;J++)
										if(Bool_Grid[X+J][Y-J]==true && Puzzle_Grid[X+J][Y-J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=0;J<5;J++)
									{	Puzzle_Grid[X+J][Y-J]=Words[I][J];
										Bool_Grid[X+J][Y-J]=true;
									}
							break;
			 case  7: //Up and Left
							do{	X=random(20-4)+4;
									Y=random(20-4)+4;
									Again=false;
									for(J=4;J>=0;J--)
										if(Bool_Grid[X-J][Y-J]==true && Puzzle_Grid[X-J][Y-J]!=Words[I][J])
											Again=true;
								}while(Again);

								for(J=4;J>=0;J--)
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
	for(X=0;X<20;X++)
	 { gotoxy(50,X+3);
		 R=X;
		 cout<<R<<" "<<Words[X];
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
	for(X=0;X<20;X++)
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
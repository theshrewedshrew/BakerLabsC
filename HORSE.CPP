
//Melissa and Jonathan
//Program name
//Due Date
//Mr Baker
//8th

//Library
#include<conio.h>
#include<iostream.h>
#include<iomanip.h>
#include<apstring.h>
#include<apvector.h>
#include<stdlib.h>
#include<apmatrix.h>
#include<fstream.h>
#include<graphics.h>
#include<dos.h>
#include<alloc.h>

//Structure

//Constants

//Global Variable
ifstream in_file;
int grdriver,grmode,errorcode, X,I;
double Money,Bet;
int Choice, Ins, Horse, Odds, Moves, BMoves, LMoves, SMoves, RMoves, PMoves, MMoves, Bx,Bx2, Lx,Lx2, Sx,Sx2, Rx,Rx2, Px,Px2, Mx,Mx2;
apstring Words,Names;
char A;
void far *P[7];
unsigned Size;

//Prototype
void gr_start(int&, int&, int&);
void instructions(apstring);
void FAQ(apstring);
void game(apstring,int, int);
void main ()
{
randomize();
clrscr();

gr_start(grdriver,grmode,errorcode);

 settextstyle(2,0,11);
	outtextxy(115,0,"A Day at the Races");
 settextstyle(2,0,7);
	outtextxy(150,75,"1. Play Game");
	outtextxy(150,100,"2. Game Instructions");
	outtextxy(150,125,"3. Frequently Asked Questions");
	outtextxy(150,150,"4. Exit");

 Choice=getche();


switch(Choice)
{

	case 49:cleardevice();
					game(Names,Odds,Moves);
					getch();
					break;

	case 50: cleardevice();
				instructions(Words);
				getch();
				break;

	case 51: cleardevice();
					FAQ(Words);
					getch();
	case 52: break;
};
//for (I=0;I<6;I++)

//farfree(P[I]);




};

//Graphic Mode Function ///////////////////////////////////////////////////
void gr_start(int& grdriver, int& grmode, int& errorcode)
{
grdriver= VGA;
grmode= VGAHI;

initgraph(& grdriver, &grmode, "C:\\TC\\BGI");
errorcode=graphresult();
	if(errorcode!=grOk)
		{clrscr();
		cout<<"Error: "<<errorcode;
		getch();
		exit(1);
		}
};

//Instructions Function  ///////////////////////////////////////////////////
void instructions(apstring Words)
{
	do{
		cout<<"Instructions"<<endl;
		cout<<"Step 1: Look at the race odds for each horse."<<endl;
		cout<<"Step 2: Select your horse from the Menu based on these odds."<<endl;
		cout<<"Step 3: Decide how much money you want to bet on your horse."<<endl;
		cout<<"Step 4: The player must bet in whole dollar amounts."<<endl;
		cout<<"Step 5: Hit the return key to start race. "<<endl;
		cout<<"Step 6: If your horse wins your money will increase based on the race odds of"<<endl;
		cout<<"that horse. However if your horse loses you will lose the money you bet"<<endl;
		cout<<"Step 7: Repeat steps 1-6 until you go Bankrupt or reach $100,000.00"<<endl;

		cout<<"1. Return to Menu"<<endl;
		cout<<"2. Exit"<<endl;
			cin>>Ins;

		 }while (Ins!=2);
		 };


//Game function  ////////////////////////////////////////////////////////////
void game (apstring Name, int Odds, int Moves)
{
char A;

Money=5000;

	do{
		cout<<"Please choose a horse:"<<endl;
		cout<<"#  Horse Name   Race Odds"<<endl;
		cout<<"1: Blue Thunder    2:1"<<endl;
		cout<<"2: Lightning       2:1"<<endl;
		cout<<"3: Speedy          3:1"<<endl;
		cout<<"4: Roxy            4:1"<<endl;
		cout<<"5: Pokey           5:1"<<endl;
		cout<<"6: Molasses        6:1"<<endl;
		cout<<"Horse#:";
			cin>>Horse;


	switch(Horse)
	{
	case 1: Name="Blue Thunder";
					Odds=2;
					break;
	case 2: Name="Lightning";
					Odds=2;
					break;
	case 3: Name="Speedy";
					Odds=3;
					break;
	case 4: Name="Roxy";
					Odds=4;
					break;
	case 5: Name="Pokey";
					Odds=5;
					break;
	case 6: Name="Molasses";
					Odds=6;
					break;
	}

		cout<<"You currently have: $"<<Money<<endl;
	do{
		cout<<"How much money would you like to bet on "<<Name<<endl;
		cout<<"Bet:$";
			cin>>Bet;
	}while (Bet<0||Bet>Money);
		cout<<"Are you sure you would like bet $"<<Bet<<" on "<<Name<<"(Y/N)"<<endl;
			cin>>A;
	}while (A!='Y'&& A!='y');

//RACE///////////////////////////////////////////////////////////////////////
cleardevice();
//TRACK/////////////////////////////////////////////////////////////////////
	setcolor(15);
		line(1,45,1,480);
		line(1,45,640,45);
		line(1,479,639,479);
		line(585,45,585,479);
			 settextstyle(2,1,20);
			 outtextxy(600,195,"Finish");

//PENS/////////////////////////////////////////////////////////////////////
		line(1,120,55,120);
		line(1,195,55,195);
		line(1,270,55,270);
		line(1,345,55,345);
		line(1,420,55,420);
//HORSES////////////////////////////////////////////////////////////////////

Bx=25,Lx=25,Sx=25,Rx=25,Px=25,Mx=25;
Bx2=40,Lx2=40,Sx2=40,Rx2=40,Px2=40,Mx2=40;

//MOVING///////////////////////////////////////////////////////////////
//BLUE THUNDER/////////////////////////////////////////////////////////////
/*
		setcolor(1);
		setfillstyle(1,1);
				fillellipse(Bx,82,15,10);
				fillellipse(Bx2,70,7,7);
				line(20,80,12,103);
				line(30,80,38,103);

				Size=(Bx-16,62,Bx2+8,104);
				P[0]=farmalloc(Size);
				getimage(Bx-16,62,Bx2+8,104,P[0]);
*/
//LIGHTNING////////////////////////////////////////////////////////////////

		setcolor(3);
		setfillstyle(1,3);
				fillellipse(Lx,157,15,10);
				fillellipse(Lx2,145,7,7);
				line(20,155,12,178);
				line(30,155,38,178);



				Size=(Lx-16,137,Lx2+8,179);
				P[1]=farmalloc(Size);
				P[6]=farmalloc(Size);
				getimage(Lx-16,137,Lx2+8,179,P[1]);
				getimage(Lx-16,137,Lx2+8,179,P[6]);
				setfillstyle(1,0);
				bar(Lx-16,137,Lx2+8,179);

//SPEEDY///////////////////////////////////////////////////////////////////

		setcolor(4);
		setfillstyle(1,4);
				fillellipse(Sx,232,15,10);
				fillellipse(Sx2,220,7,7);
				line(20,230,12,253);
				line(30,230,38,253);

				Size=(Sx-16,212,Sx2+8,254);
				P[2]=malloc(Size);
				getimage(Sx-16,212,Sx2+8,254,P[2]);

//ROXY/////////////////////////////////////////////////////////////////////
/*
		setcolor(6);
		setfillstyle(1,6);
				fillellipse(Rx,307,15,10);
				fillellipse(Rx2,295,7,7);
				line(20,305,12,328);
				line(30,305,38,328);

				Size=(Rx-16,287,Rx2+8,329);
				P[3]=farmalloc(Size);
				getimage(Rx-16,287,Rx2+8,329,P[3]);

//POKEY////////////////////////////////////////////////////////////////////

		setcolor(7);
		setfillstyle(1,7);
				fillellipse(Px,382,15,10);
				fillellipse(Px2,370,7,7);
				line(20,380,12,403);
				line(30,380,38,403);

				Size=(Px-16,287,Px2+8,329);
				P[4]=farmalloc(Size);
				getimage(Px-16,362,Px2+8,404,P[4]);

//MOLASSES////////////////////////////////////////////////////////////////

		setcolor(2);
		setfillstyle(1,2);
				fillellipse(Mx,450,15,10);
				fillellipse(Mx2,438,7,7);
				line(20,448,12,471);
				line(30,448,38,471);

				Size=(Mx-16,287,Mx2+8,329);
				P[5]=farmalloc(Size);
				getimage(Mx-16,430,Mx2+8,472,P[5]);
*/


//				putimage(Bx-16,62,P[0],OR_PUT);
				putimage(Lx-16,137,P[1],OR_PUT);
				putimage(Sx-16,212,P[2],OR_PUT);
//				putimage(Rx-16,287,P[3],OR_PUT);
//				putimage(Px-16,362,P[4],OR_PUT);
//				putimage(Mx-16,430,P[5],OR_PUT);

				delay(10);

//				putimage(Bx-16,62,P[0],XOR_PUT);
				putimage(Lx-16,137,P[1],XOR_PUT);
				putimage(Sx-16,212,P[2],XOR_PUT);
//				putimage(Rx-16,287,P[3],XOR_PUT);
//				putimage(Px-16,362,P[4],XOR_PUT);
//				putimage(Mx-16,430,P[5],XOR_PUT);

				delay(10);



	do{

		Bx=Bx+random(25);
		//delay(350);
		Lx=Lx+random(25);
		//delay(350);
		Sx=Sx+random(25);
		//delay(350);
		Rx=Rx+random(25);
		//delay(350);
		Px=Px+random(25);
		//delay(350);
		Mx=Mx+random(25);
		//delay(350);


//	rectangle(60+Bx2,200,Bx2+68,216+Bx);

//				putimage(Bx-16,62,P[0],OR_PUT);
				putimage(Lx-16,137,P[1],OR_PUT);
				putimage(Sx-16,212,P[2],OR_PUT);
//				putimage(Rx-16,287,P[3],OR_PUT);
//				putimage(Px-16,362,P[4],OR_PUT);
//				putimage(Mx-16,430,P[5],OR_PUT);

				delay(350);

//				putimage(Bx-16,62,P[0],XOR_PUT);
				putimage(Lx-16,137,P[1],XOR_PUT);
				putimage(Sx-16,212,P[2],XOR_PUT);
//				putimage(Rx-16,287,P[3],XOR_PUT);
//				putimage(Px-16,362,P[4],XOR_PUT);
//				putimage(Mx-16,430,P[5],XOR_PUT);


				}while(Lx<=585&&Sx<=585);
}

//FAQ's /////////////////////////////////////////////////////////////////////

void FAQ (apstring Words)
 {
		do{
			cout<<"FAQ (Frequently Asked Questions)"<<endl;
			cout<<"1. Return to Menu"<<endl;
			cout<<"2. Exit"<<endl;
				cin>>Ins;

			}while (Ins!=2);
 }

//BETTING  //////////////////////////////////////////////////////////////////


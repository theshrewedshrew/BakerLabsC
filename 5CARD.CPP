/******************************
Jeffrey Mahmoudi & Jake Hurst *
BlAcKjAcK                     *
Due Date                      *
6th Period        						*
Mr.Baker        						  *
******************************/

//Library Section
#include<iostream.h>
#include<iomanip.h>
#include<conio.h>
#include<apstring.h>
#include<apvector.h>
#include<apmatrix.h>
#include<stdlib.h>
#include<fstream.h>
#include<graphics.h>
#include<dos.h>
#include<alloc.h>;
#include<gmouse.c>;
#include<5card.h>;
//Struct Section

//Constant Section

//Variable Section

//Main
void main()
	{
randomize ();
End=false;
clrscr ();
gr_start (grdriver, grmode, errorcode);
do{
Money=1000;
Shuffle=0;
cleardevice ();
tcards ();
SetMouse ();
rectangle (0,0,625,200);
setcolor (RED);
settextstyle (3,0,5);
outtextxy (200,10,"BlAcKjAcK");
setcolor (WHITE);
rectangle (225,75,275,150);
line (230,90,235,80);
line (235,80,240,90);
line (233,85,237,85);
line (260,135,265,145);
line (265,145,270,135);
line (263,138,267,138);
rectangle (325,75,375,150);
line (330,90,330,80);
line (330,85,335,80);
line (330,85,335,90);
line (370,145,370,135);
line (370,140,365,135);
line (370,140,365,145);
settextstyle (3,0,1);
setcolor (YELLOW);
outtextxy (265,160,"WiNnEr!!!");
setcolor (BLUE);
outtextxy (10,10,"BuSt!");
outtextxy (75,25,"StAnD?");
outtextxy (575,0,"SpLiT");
settextstyle (3,1,1);
setcolor (GREEN);
outtextxy (500,25,"21");
outtextxy (400,50,"HiT?");
outtextxy (150,30,"DoUbLe");
setcolor (WHITE);
rectangle (245,225,370,275);
rectangle (75,300,200,350);
rectangle (400,300,525,350);
rectangle (245,375,370,425);
rectangle (580,420,630,470);
settextstyle (3,0,2);
setcolor (RED);
outtextxy (255,235,"Instructions");
outtextxy (85,310,"One Player");
outtextxy (430,310,"Cheats");
outtextxy (255,385,"High Score");
outtextxy (590,430,"Exit");
ShowMouse ();
Exit=false;
do
{
	if (GetMouseButton ()==1)
		{MX=GetMouseX ();
		 MY=GetMouseY ();
		 if ((MX>245)&&(MX<370)&&(MY>225)&&(MY<275))
			{cleardevice ();
			 HideMouse ();
			 Infile.open("A:\\instruct.txt");
			 restorecrtmode ();
			 do
			 {getline (Infile,Instruct);
				cout<<Instruct<<endl;
			 }while (Instruct!="Press Enter To Continue...");
			 Infile.close ();
			 getch ();
			 Exit=true;
			}
		 else if ((MX>75)&&(MX<200)&&(MY>300)&&(MY<350))
				{HideMouse ();
				 cleardevice ();
				 oneplayer ();
				 getch ();
				 Exit=true;
				}
		 else if ((MX>400)&&(MX<525)&&(MY>300)&&(MY<350))
				{HideMouse ();
				 cleardevice ();
				 cheats ();
				 getch ();
				 Exit=true;
				}
		 else if ((MX>245)&&(MX<370)&&(MY>375)&&(MY<425))
				{HideMouse ();
				 cleardevice ();
				 setcolor (YELLOW);
				 outtextxy (250,5,"High Scores");
				 line (250,35,365,35);
				 Infile.open("A:\\hscore.txt");
				 HY=50;
				 for (A=0; A<10; A++)
						{getline (Infile, HScore);
						 convert (String, HScore);
						 outtextxy (150,HY,String);
						 HY+=25;
						 setcolor (WHITE);
						}
				 Infile.close ();
				 getch ();
				 Exit=true;
				}
		else if ((MX>590)&&(MX<640)&&(MY>430)&&(MY<480))
				{HideMouse ();
				 cleardevice ();
				 gotoxy (25,12);
				 cout<<"Thank you for Playing BlAcKjAcK...";
				 //delay (5000);
				 End=true;
				 Exit=true;
				}

		}
}while (!Exit);
setgraphmode (grmode);
closegraph ();
}while (!End);
	};

//Funtion Section
void gr_start (int& grdriver, int&grmode, int&errorcode)
	{grdriver=VGA;
	 grmode=VGAHI;
	 initgraph (&grdriver, &grmode, "C:\\TC\\BGI");
	 errorcode=graphresult();
	 if (errorcode!=grOk)
		{clrscr();
		 getch();
		 exit(1);
		}
	 };
void convert (char string [], apstring Sent_In)
	{int I;
	 for (I=0; I<Sent_In.length (); I++)
		string [I]=Sent_In[I];
		string [I]='\0';
	};
void checkcards ()
{for (A=0; A<52; A++)
		CheckCard [A]=0;
};
void tcards ()
{Card  [0]="Ace Of Spades";
 Score [0]=1;
 Card  [1]="Two (2) Of Spades";
 Score [1]=2;
 Card  [2]="Three (3) Of Spades";
 Score [2]=3;
 Card  [3]="Four (4) Of Spades";
 Score [3]=4;
 Card  [4]="Five (5) Of Spades";
 Score [4]=5;
 Card  [5]="Six (6) Of Spades";
 Score [5]=6;
 Card  [6]="Seven (7) Of Spades";
 Score [6]=7;
 Card  [7]="Eight (8) Of Spades";
 Score [7]=8;
 Card  [8]="Nine (9) Of Spades";
 Score [8]=9;
 Card  [9]="Ten (10)Of Spades";
 Score [9]=10;
 Card  [10]="Jack Of Spades";
 Score [10]=10;
 Card  [11]="Queen Of Spades";
 Score [11]=10;
 Card  [12]="King Of Spades";
 Score [12]=10;
 Card  [13]="Ace Of Clubs";
 Score [13]=1;
 Card  [14]="Two (2) Of Clubs";
 Score [14]=2;
 Card  [15]="Three (3) Of Clubs";
 Score [15]=3;
 Card  [16]="Four (4) Of Clubs";
 Score [16]=4;
 Card  [17]="Five (5) Of Clubs";
 Score [17]=5;
 Card  [18]="Six (6) Of Clubs";
 Score [18]=6;
 Card  [19]="Seven (7) Of Clubs";
 Score [19]=7;
 Card  [20]="Eight (8) Of Clubs";
 Score [20]=8;
 Card  [21]="Nine (9) Of Clubs";
 Score [21]=9;
 Card  [22]="Ten (10) Of Clubs";
 Score [22]=10;
 Card  [23]="Jack Of Clubs";
 Score [23]=10;
 Card  [24]="Queen Of Clubs";
 Score [24]=10;
 Card  [25]="King Of Clubs";
 Score [25]=10;
 Card  [26]="Ace Of Diamonds";
 Score [26]=1;
 Card  [27]="Two (2) Of Diamonds";
 Score [27]=2;
 Card  [28]="Three (3) Of Diamonds";
 Score [28]=3;
 Card  [29]="Four (4) Of Diamonds";
 Score [29]=4;
 Card  [30]="Five (5) Of Diamonds";
 Score [30]=5;
 Card  [31]="Six (6) Of Diamonds";
 Score [31]=6;
 Card  [32]="Seven (7) Of Diamonds";
 Score [32]=7;
 Card  [33]="Eight (8) Of Diamonds";
 Score [33]=8;
 Card  [34]="Nine (9) Of Diamonds";
 Score [34]=9;
 Card  [35]="Ten (10)Of Diamonds";
 Score [35]=10;
 Card  [36]="Jack Of Diamonds";
 Score [36]=10;
 Card  [37]="Queen Of Diamonds";
 Score [37]=10;
 Card  [38]="King Of Diamonds";
 Score [38]=10;
 Card  [39]="Ace Of Hearts";
 Score [39]=1;
 Card  [40]="Two (2) Of Hearts";
 Score [40]=2;
 Card  [41]="Three (3) Of Hearts";
 Score [41]=3;
 Card  [42]="Four (4) Of Hearts";
 Score [42]=4;
 Card  [43]="Five (5) Of Hearts";
 Score [43]=5;
 Card  [44]="Six (6) Of Hearts";
 Score [44]=6;
 Card  [45]="Seven (7) Of Hearts";
 Score [45]=7;
 Card  [46]="Eight (8) Of Hearts";
 Score [46]=8;
 Card  [47]="Nine (9) Of Hearts";
 Score [47]=9;
 Card  [48]="Ten (10) Of Hearts";
 Score [48]=10;
 Card  [49]="Jack Of Hearts";
 Score [49]=10;
 Card  [50]="Queen Of Hearts";
 Score [50]=10;
 Card  [51]="King Of Hearts";
 Score [51]=10;
};
void bust()
{
setcolor(10);
setlinestyle(0,0,3);
line(80,100,80,300);
ellipse(80,150,270,90,70,50);
ellipse(80,250,270,90,90,50);
ellipse(230,110,180,0,50,190);
ellipse(370,150,70,265,70,50);
ellipse(340,247,230,70,70,50);
line(410,105,530,105);
line(470,105,470,300);
line(560,102,560,260);
circle(560,290,10);
};
void oneplayer ()
{int Bet;
 char Play;
 bool DD,BJ;
 Bet=0;
 outtextxy (0,5,"Enter Name");
 cout<<endl<<endl;
 line (0,48,150,48);
 getline (cin,Name);
 do
 {do{
	cleardevice ();
	setcolor (RED);
	Total=0;
	gotoxy (15,6);
	settextstyle (3,0,1);
	cout<<"Money: $"<<Money;
	outtextxy (0,45,"Enter The Amount Of Your Bet");
	gotoxy (1,6);
	cout<<"$";
	cin>>Bet;
	}while (Bet>Money);
	getline (cin,Trash);
	cleardevice ();
	outtext ("Welcome To The Blackjack Table, ");
	convert (String,Name);
	outtext (String);
	line (0,30,getx (),30);
	CY=200;
	moveto (0,CY);
	Stay=false;
	setcolor (WHITE);
	settextstyle (3,0,1);
	setcolor (RED);
	I=1;
	gcard ();
	I++;
	do
	{CY+=20;
	 moveto (0,CY);
	 gcard ();
	 I++;
	 gotoxy (1,25);
	 cout<<"Total: "<<Total;
	 setcolor (YELLOW);
	 settextstyle (3,0,1);
	 rectangle (250,200,400,250);
	 rectangle (425,200,575,250);
	 rectangle (335,275,485,325);
	 outtextxy (310,210,"HiT");
	 outtextxy (475,210,"StAnD");
	 outtextxy (380,285,"DoUbLe");
	 ShowMouse ();
	 Exit=false;
	 Bust=false;
	 do
	 {
		 if (Total>21)
			 {HideMouse ();
				bust ();
				Money-=Bet;
				Bust=true;
				Stay=true;
				Exit=true;
			 }
		 else if ((Total==21)&&(I==3))
						{HideMouse ();
						 setcolor (GREEN);
						 settextstyle (6,0,25);
						 outtextxy (15,150,"BLACKJACK");
						 BJ=true;
						 Stay=true;
						 Exit=true;
						}
		 else if (GetMouseButton ()==1)
						{delay (250);
						 MX=GetMouseX ();
						 MY=GetMouseY ();
						 if ((MX>250)&&(MX<400)&&(MY>200)&&(MY<250))
							 {HideMouse ();
								Exit=true;
							 }
		 else if ((MX>425)&&(MX<575)&&(MY>200)&&(MY<250))
						{HideMouse ();
						 Stay=true;
						 Exit=true;
						}
		 else if ((MX>335)&&(MX<485)&&(MY>275)&&(MY<325))
						{HideMouse ();
						 if (I==3)
							 {gcard ();
								gotoxy (1,25);
								cout<<"Total: "<<Total;
								DD=true;
								Stay=true;
								Exit=true;
							 }
						 else
						 Exit=true;
						}
						}
	}while (!Exit);
 }while (!Stay);
DTotal=0;
if (Bust==false)
	{do{
	 A=random (52);
	 DTotal+=Score [A];
	 CheckCard[A]=1;
	 Shuffle++;
	 }while(DTotal<17);
	gotoxy (1,26);
	cout<<endl<<"Dealer Total: "<<DTotal;
	if (BJ==true)
		Money+=Bet*2;
	else if ((Total>DTotal)&&(DD==true))
				 Money+=Bet*2;
	else if (Total>DTotal)
				 Money+=Bet;
	else if (DTotal>21)
				 Money+=Bet;
	else if (Total<DTotal)
				 Money-=Bet;
	}
gotoxy (1,27);
cout<<endl<<"Do You Want To Play Again? (Y/N)"<<endl;
cin>>Play;
cleardevice ();
}while ((Play=='y')||(Play=='Y'));
Infile.open("A:\\hscore.txt");
for (A=0; A<10; A++)
	{Infile>>HMoney [A];
	 getline (Infile,HName [A]);
	}
Infile.close ();
Outfile.open("A:\\hscore.txt");
A=0;
Exit=false;
do{
	if (Money>HMoney [A])
	 {
		HMoney [A+1]=HMoney [A];
		HName [A+1]=HName [A];
		HMoney [A]=Money;
		HName [A]=Name;
		Exit=true;
	 }
A++;
}while (!Exit);
do{
HMoney [A+1]=HMoney [A];
HName [A+1]=HName [A];
A++;
}while (A<10);
for (A=0; A<10; A++)
 {Outfile<<HMoney [A]<<" ";
	Outfile<<HName [A]<<" "<<endl;
 }
Outfile.close ();
gotoxy (25,12);
cout<<"Press Enter To Continue...";
};
void cheats ()
{outtextxy (5,5,"Cheats");
};
void gcard ()
{if (I==1)
	 gcard1 ();
 else if (I==2)
				gcard2 ();
 else if (I==3)
//				gcard3 ();
// else if (I==4)
				gcard4 ();
};

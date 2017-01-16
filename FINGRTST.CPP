//Jeff Gittle
//Prob#
//Pd. 4
//Library Section
#include<iostream.h>
#include<iomanip.h>
#include<conio.h>
#include<apstring.h>
#include<apmatrix.h>
#include<apvector.h>
#include<fstream.h>
#include<graphics.h>
#include<dos.h>
#include<alloc.h>
#include"SVGA.h"
//Const Section

//Structs Section

//Global Var Section
char Repeat;
bool Flag,Bflag,Boxflag,Supb,Supb2,Exflag,Endex,Endex2;
int GrDriver,GrMode,ErrorCode,Key,X,Y,Z,Bomb,Bx,By,Pkey,Btimer,Reccolor;
int Boxx,Boxy,X2,Y2,Bx2,By2,Bflag2,Btimer2,Misc,Exctr,Exflag2,Exctr2;
apstring Trash;
//Prototype
void gr_start(int&,int&,int&);
//Main Section
void main()
{
randomize();
//do{
	cout<<setprecision(2)<<setiosflags(ios::showpoint);
	clrscr();
	//gr_start(GrDriver,GrMode,ErrorCode);
	gr_init(SVGATC, 6, "c:\\tc\\bgi");
	//draws arena
		rectangle(10,10,611,471);
		setfillstyle(1,8,8,8);
		floodfill(1,1,15);
		rectangle(50,50,80,80);
		floodfill(51,51,15);
		rectangle(50,120,80,150);
		floodfill(51,121,15);
		rectangle(50,190,80,220);
		floodfill(51,191,15);
		rectangle(50,260,80,290);
		floodfill(51,261,15);
		rectangle(50,330,80,360);
		floodfill(51,331,15);
		rectangle(50,400,80,430);
		floodfill(51,401,15);
		rectangle(120,50,150,80);
		floodfill(121,51,15);
		rectangle(120,120,150,150);
		floodfill(121,121,15);
		rectangle(120,190,150,220);
		floodfill(121,191,15);
		rectangle(120,260,150,290);
		floodfill(121,261,15);
		rectangle(120,330,150,360);
		floodfill(121,331,15);
		rectangle(120,400,150,430);
		floodfill(121,401,15);
		rectangle(190,50,220,80);
		floodfill(191,51,15);
		rectangle(190,120,220,150);
		floodfill(191,121,15);
		rectangle(190,190,220,220);
		floodfill(191,191,15);
		rectangle(190,260,220,290);
		floodfill(191,261,15);
		rectangle(190,330,220,360);
		floodfill(191,331,15);
		rectangle(190,400,220,430);
		floodfill(191,401,15);
		rectangle(260,50,290,80);
		floodfill(261,51,15);
		rectangle(260,120,290,150);
		floodfill(261,121,15);
		rectangle(260,190,290,220);
		floodfill(261,191,15);
		rectangle(260,260,290,290);
		floodfill(261,261,15);
		rectangle(260,330,290,360);
		floodfill(261,331,15);
		rectangle(260,400,290,430);
		floodfill(261,401,15);
		rectangle(330,50,360,80);
		floodfill(331,51,15);
		rectangle(330,120,360,150);
		floodfill(331,121,15);
		rectangle(330,190,360,220);
		floodfill(331,191,15);
		rectangle(330,260,360,290);
		floodfill(331,261,15);
		rectangle(330,330,360,360);
		floodfill(331,331,15);
		rectangle(330,400,360,430);
		floodfill(331,401,15);
		rectangle(400,50,430,80);
		floodfill(401,51,15);
		rectangle(400,120,430,150);
		floodfill(401,121,15);
		rectangle(400,190,430,220);
		floodfill(401,191,15);
		rectangle(400,260,430,290);
		floodfill(401,261,15);
		rectangle(400,330,430,360);
		floodfill(401,331,15);
		rectangle(400,400,430,430);
		floodfill(401,401,15);
		rectangle(470,50,500,80);
		floodfill(471,51,15);
		rectangle(470,120,500,150);
		floodfill(471,121,15);
		rectangle(470,190,500,220);
		floodfill(471,191,15);
		rectangle(470,260,500,290);
		floodfill(471,261,15);
		rectangle(470,330,500,360);
		floodfill(471,331,15);
		rectangle(470,400,500,430);
		floodfill(471,401,15);
		rectangle(540,50,570,80);
		floodfill(541,51,15);
		rectangle(540,120,570,150);
		floodfill(541,121,15);
		rectangle(540,190,570,220);
		floodfill(541,191,15);
		rectangle(540,260,570,290);
		floodfill(541,261,15);
		rectangle(540,330,570,360);
		floodfill(541,331,15);
		rectangle(540,400,570,430);
		floodfill(541,401,15);
		getch();

		 /*


	//player movement

	Bomb=0;
	Btimer=-1;
	Btimer2=-1;
	Bflag=false;
	Bflag2=false;
	Pkey=Key=0;
	Supb=false;
	Supb2=false;
	Exflag=true;
	Exctr=-1;
	Misc=1;
	X=30;
	Y=30;
	X2=590;
	Y2=450;
	Endex=true;
	Endex2=true;
	circle(310,240,14);


	do{
		if(X==310&&Y==240)
			Supb=true;
		if(X2==310&&Y2==240)
			Supb2=true;


		 if(kbhit())
		 {	Key=getch();
			setcolor(0);
			circle(X,Y,14);
			circle(X2,Y2,14);
			setfillstyle(1,0);
			fillellipse(X,Y,14,14);
			fillellipse(X2,Y2,14,14);
			setcolor(15);
		 }
		Flag=true;
	 //	cout<<Key<<" ";
		switch (Key)
		{
		//p1 left
		case 97:
						if(X>30)
						if(getpixel(X-21,Y+14)!=8&&getpixel(X-21,Y-14)!=8)
						if(getpixel(X-21,Y+14)!=6&&getpixel(X-21,Y-14)!=6)
							X=X-10;
						 break;
		//p1 down
		case 115:
						if(Y<450)
						if(getpixel(X-14,Y+21)!=8&&getpixel(X+14,Y+21)!=8)
						if(getpixel(X-14,Y+21)!=6&&getpixel(X+14,Y+21)!=6)
							Y=Y+10;
						 break;
		//p1 right
		case 100:
						if(X<590)
						if(getpixel(X+21,Y+14)!=8&&getpixel(X+21,Y-14)!=8)
						if(getpixel(X+21,Y+14)!=6&&getpixel(X+21,Y-14)!=6)
							X=X+10;
						 break;
		//p1 up
		case 119:
						if(Y>30)
						if(getpixel(X+14,Y-21)!=8&&getpixel(X-14,Y-21)!=8)
						if(getpixel(X+14,Y-21)!=6&&getpixel(X-14,Y-21)!=6)
						 Y=Y-10;
						 break;
		//p2left
		case 106:
						if(X2>30)
						if(getpixel(X2-21,Y2+14)!=8&&getpixel(X2-21,Y2-14)!=8)
						if(getpixel(X2-21,Y2+14)!=6&&getpixel(X2-21,Y2-14)!=6)
							X2=X2-10;
						 break;
		//p2 right
		case 108:
						if(X2<590)
						if(getpixel(X2+21,Y2+14)!=8&&getpixel(X2+21,Y2-14)!=8)
						if(getpixel(X2+21,Y2+14)!=6&&getpixel(X2+21,Y2-14)!=6)
							X2=X2+10;
						 break;
		//p2 up
		case 105:
						if(Y2>30)
						if(getpixel(X2+14,Y2-21)!=8&&getpixel(X2-14,Y2-21)!=8)
						if(getpixel(X2+14,Y2-21)!=6&&getpixel(X2-14,Y2-21)!=6)
						 Y2=Y2-10;
						 break;
		//p2 down
		case 107:
						if(Y2<450)
						if(getpixel(X2-14,Y2+21)!=8&&getpixel(X2+14,Y2+21)!=8)
						if(getpixel(X2-14,Y2+21)!=6&&getpixel(X2+14,Y2+21)!=6)
							Y2=Y2+10;
						 break;
		//p1 bomb
		case 113:
						if(Bflag==false&&Endex==true)
							{
							Btimer=200;
							Bx=X;
							By=Y;
							Bflag=true;
							Exctr=0;
							Exflag=true;
							}
						break;
		case 111:
						if(Bflag2==false&&Endex2==true)
							{
							Btimer2=200;
							Bx2=X2;
							By2=Y2;
							Bflag2=true;
							Exctr2=0;
							Exflag2=true;
							}
						break;

		case 27:Flag=false;
		}
		//boxes
		Boxx=400;
		Boxy=200;
		Boxflag=true;
		if(Boxflag==true)
			{
			setfillstyle(1,6);
			bar(51,86,79,114);
			}
		//bomb dropping p2
		if(Btimer2>0&&Bflag2==true)
			{
			setfillstyle(1,4);
			fillellipse(Bx2,By2,5,5);
			delay(5);

			setfillstyle(1,14);
			fillellipse(Bx2,By2,5,5);
			delay(5);
			Btimer2--;
			Endex2=false;
			}
		else
			{
			Bflag2=false;

			}
		if(Btimer2==0&&Endex2==false)
			{
			//you said it could go off the screen this time....
			if(Exflag2==true)
				setfillstyle(1,4);
			if(Exflag2==false)
				setfillstyle(1,0);
			bar(Bx2-14,By2-14,Bx2+14,By2+14);
			if(Supb2!=true)
				{
				if(getpixel(Bx2-25,By2+15)!=8&&getpixel(Bx2-25,By2-15)!=8&&getpixel(Bx2-25,By2+15)!=15&&getpixel(Bx2-25,By2-15)!=15)
					{
					if(Bx2>60)
						bar(Bx2-44,By2-14,Bx2+14,By2+14);
					else
						bar(14,By2-14,Bx2+14,By2+14);
					}
				if(getpixel(Bx2-15,By2+25)!=8&&getpixel(Bx2+15,By2+25)!=8&&getpixel(Bx2-15,By2+25)!=15&&getpixel(Bx2+15,By2+25)!=15)
					{
					if(By2<420)
						bar(Bx2-14,By2-14,Bx2+14,By2+44);
					else
						bar(Bx2-14,By2-14,Bx2+14,465);
					}
				if(getpixel(Bx2+25,By2+15)!=8&&getpixel(Bx2+25,By2-15)!=8&&getpixel(Bx2+25,By2+15)!=15&&getpixel(Bx2+25,By2-15)!=15)
					{
					if(Bx2<550)
						bar(Bx2-14,By2-14,Bx2+44,By2+14);
					else
						bar(Bx2-14,By2-14,605,By2+14);
					}
				if(getpixel(Bx2+15,By2-25)!=8&&getpixel(Bx2-15,By2-25)!=8&&getpixel(Bx2+15,By2-25)!=15&&getpixel(Bx2-15,By2-25)!=15)
					bar(Bx2-14,By2-44,Bx2+14,By2+14);
				}
			if(Supb2==true)
				{
				if(getpixel(Bx2-25,By2+15)!=8&&getpixel(Bx2-25,By2-15)!=8&&getpixel(Bx2-25,By2+15)!=15&&getpixel(Bx2-25,By2-15)!=15)
					bar(15,By2-14,Bx2+14,By2+14);
				if(getpixel(Bx2-15,By2+25)!=8&&getpixel(Bx2+15,By2+25)!=8&&getpixel(Bx2-15,By2+25)!=15&&getpixel(Bx2+15,By2+25)!=15)
					bar(Bx2-14,By2-14,Bx2+14,465);
				if(getpixel(Bx2+25,By2+15)!=8&&getpixel(Bx2+25,By2-15)!=8&&getpixel(Bx2+25,By2+15)!=15&&getpixel(Bx2+25,By2-15)!=15)
					bar(Bx2-14,By2-14,605,By2+14);
				if(getpixel(Bx2+15,By2-25)!=8&&getpixel(Bx2-15,By2-25)!=8&&getpixel(Bx2+15,By2-25)!=15&&getpixel(Bx2-15,By2-25)!=15)
					bar(Bx2-14,15,Bx2+14,By2+14);
				}
			Exctr2++;
			if(Exflag2==false)
				Endex2=true;
			if(Exctr2>600)
				Exflag2=false;
			}

		//bomb dropping p1
		if(Btimer>0&&Bflag==true)
			{
			setfillstyle(1,4);
			fillellipse(Bx,By,5,5);
			delay(5);

			setfillstyle(1,14);
			fillellipse(Bx,By,5,5);
			delay(5);
			Btimer--;
			Endex=false;
			}
		else
			{
			Bflag=false;

			}
		if(Btimer==0&&Endex==false)
			{
			//you said it could go off the screen this time....

			if(Exflag==true)
				setfillstyle(1,4);
			if(Exflag==false)
				setfillstyle(1,0);
			bar(Bx-14,By-14,Bx+14,By+14);
			if(Supb!=true)
				{
				if(getpixel(Bx-25,By+15)!=8&&getpixel(Bx-25,By-15)!=8&&getpixel(Bx-25,By+15)!=15&&getpixel(Bx-25,By-15)!=15)
					{
					if(Bx>60)
						bar(Bx-44,By-14,Bx+14,By+14);
					else
						bar(14,By-14,Bx+14,By+14);
					}
				if(getpixel(Bx-15,By+25)!=8&&getpixel(Bx+15,By+25)!=8&&getpixel(Bx-15,By+25)!=15&&getpixel(Bx+15,By+25)!=15)
					{
					if(By<420)
						bar(Bx-14,By-14,Bx+14,By+44);
					else
						bar(Bx-14,By-14,Bx+14,465);
					}
				if(getpixel(Bx+25,By+15)!=8&&getpixel(Bx+25,By-15)!=8&&getpixel(Bx+25,By+15)!=15&&getpixel(Bx+25,By-15)!=15)
					{
					if(Bx<550)
						bar(Bx-14,By-14,Bx+44,By+14);
					else
						bar(Bx-14,By-14,605,By+14);
					}
				if(getpixel(Bx+15,By-25)!=8&&getpixel(Bx-15,By-25)!=8&&getpixel(Bx+15,By-25)!=15&&getpixel(Bx-15,By-25)!=15)
					{
					if(By>60)
						bar(Bx-14,By-44,Bx+14,By+14);
					else
						bar(Bx-14,14,Bx+14,By+14);
					}
				}
			if(Supb==true)
				{
				if(getpixel(Bx-25,By+15)!=8&&getpixel(Bx-25,By-15)!=8&&getpixel(Bx-25,By+15)!=15&&getpixel(Bx-25,By-15)!=15)
					bar(15,By-14,Bx+14,By+14);
				if(getpixel(Bx-15,By+25)!=8&&getpixel(Bx+15,By+25)!=8&&getpixel(Bx-15,By+25)!=15&&getpixel(Bx+15,By+25)!=15)
					bar(Bx-14,By-14,Bx+14,465);
				if(getpixel(Bx+25,By+15)!=8&&getpixel(Bx+25,By-15)!=8&&getpixel(Bx+25,By+15)!=15&&getpixel(Bx+25,By-15)!=15)
					bar(Bx-14,By-14,605,By+14);
				if(getpixel(Bx+15,By-25)!=8&&getpixel(Bx-15,By-25)!=8&&getpixel(Bx+15,By-25)!=15&&getpixel(Bx-15,By-25)!=15)
					bar(Bx-14,15,Bx+14,By+14);
				}

			Exctr++;
			if(Exflag==false)
				Endex=true;
			if(Exctr>600)
				Exflag=false;
			}
		circle(X,Y,14);
		setfillstyle(1,2);
		fillellipse(X,Y,14,14);
		setfillstyle(1,5);
		fillellipse(X2,Y2,14,14);
		Key=0;
	}while(Flag==true);

	*/



	// reruns program
/*	cout<<"Do you want to run the program again? (Y/N)"<<endl;
	cin>>Repeat;
	}while(Repeat=='Y'||Repeat=='y');*/
}
//end main
// functions n stuff
void gr_start(int&GrDriver,int&GrMode,int&ErrorCode)
{
	GrDriver=VGA;
	GrMode=VGAHI;
	initgraph(&GrDriver,&GrMode,"C:\\TC\\BGI");
	ErrorCode=graphresult();
	if(ErrorCode!=grOk)
	{
		clrscr();
		cout<<"Error Code:"<<ErrorCode;
		getch();
		exit(1);
	}
}


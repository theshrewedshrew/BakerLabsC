

#include <iomanip.h>
#include <apstring.h>
#include <string.h>
#include <apvector.h>
#include <iostream.h>
#include <apstring.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <gmouse.c>
//#include <dmouse.h>
//#include <dgraph.h>
//#include <graphics.inc>

void ShapeFill(int,int);
void Output_Data(int,int,int);
void Pencil(bool, int &, int);
int Size(int, int, int,int);
//int RPColor;
int oldcolor, newcolor,X,Y,I,X1,Y1,radius,Items,T;
bool Exit, Draw, Rtangle, Flag, LFlag;
void main()
{ int grdriver=VGA;
 int grmode=VGAHI,errorcode;
 initgraph (&grdriver,&grmode,"C:\\Tc\\BGI");
 errorcode=graphresult();
 if (errorcode!=grOk)
	{clrscr();
	 cout <<"error";
	 getch();
	 exit(1);
	 }
//SetScreenMode(VGA256);
cleardevice();
Exit=Draw=LFlag=false;
X=Y=150;
newcolor=15;
oldcolor=0;
SetMouse();
ShowMouse();
Output_Data(X,Y,newcolor);
putpixel(X,Y,newcolor);
//for(I=0;I<16;I++)

do{
		if (kbhit())
			{ Output_Data(X,Y,newcolor);
				switch(getch())
				{ case 64://@
									cleardevice();
									Output_Data(X,Y,newcolor);
									break;
					case 99:// C
					case 67:
									gotoxy(5,24);
									cout<<"New Color (0-15):";
									cin>>newcolor;
									gotoxy(5,24);
									cout<<setw(50)<<" "<<endl;
									gotoxy(2,4);
									cout<<setw(10)<<" "<<endl;
									gotoxy(2,4);
									cout<<"Color:"<<newcolor<<endl;
									setcolor(newcolor);
									putpixel(X,Y,newcolor);
									break;
					case 75://Left
									if (X>0)
										{ if (oldcolor==getpixel(X-1,Y))
													{putpixel(X,Y,oldcolor);
													 putpixel(X-1,Y,newcolor);
													 //outtextxy(500,2,"O");
													}
											else
												 { putpixel(X,Y,oldcolor);
													 oldcolor=getpixel(X-1,Y);
													 putpixel(X-1,Y,newcolor);
													// outtextxy(500,2,"N");
												 }
											X--;

										}
									break;
					case 77://Right
									if (X<getmaxx())
										{ if (oldcolor==getpixel(X+1,Y))
													{putpixel(X,Y,oldcolor);
													 putpixel(X+1,Y,newcolor);
													// outtextxy(500,2,"O");
													}
											else
												 { putpixel(X,Y,oldcolor);
													 oldcolor=getpixel(X+1,Y);
													 putpixel(X+1,Y,newcolor);
													// outtextxy(500,2,"N");
												 }
											X++;

										}
									break;
					case 80://Down
									if (Y<getmaxy()) //{putpixel(X,Y,oldcolor);Y++;}
										{ if (oldcolor==getpixel(X,Y+1))
													{putpixel(X,Y,oldcolor);
													 putpixel(X,Y+1,newcolor);
													// outtextxy(500,2,"O");
													}
											else
												 { putpixel(X,Y,oldcolor);
													 oldcolor=getpixel(X,Y+1);
													 putpixel(X,Y+1,newcolor);
													// outtextxy(500,2,"N");
												 }
											Y++;

										}
									break;
					case 72://Up
									if (Y>0) //{putpixel(X,Y,oldcolor);Y--;}
									{ if (oldcolor==getpixel(X,Y-1))
													{putpixel(X,Y,oldcolor);
													 putpixel(X,Y-1,newcolor);
													 //outtextxy(500,2,"O");
													}
											else
												 { putpixel(X,Y,oldcolor);
													 oldcolor=getpixel(X,Y-1);
													 putpixel(X,Y-1,newcolor);
													// outtextxy(500,2,"N");
												 }
											Y--;

										}
									break;
					case 100:// D
					case 68: if (Draw)
											Draw=false;
									 else Draw=true;
									 break;
					case 70:// F
					case 102:	ShapeFill(X,Y);
										oldcolor=newcolor;
										setcolor(newcolor);
										gotoxy(5,24);
										cout<<"Items:"<<Items;
										Flag=true;
										break;
					case 82:// R
					case 114: if (Rtangle)
												{ setcolor(newcolor);
													if (X1>X)
														{	rectangle(X,Y,X1,Y1);
															gotoxy(5,24);
															cout<<setw(50)<<" ";
															gotoxy(5,24);
															cout<<"Size:"<<Size(X,X1,Y,Y1);
														}
													else
														{	rectangle(X1,Y1,X,Y);
															gotoxy(5,24);
															cout<<setw(50)<<" ";
															gotoxy(5,24);
															cout<<"Size:"<<Size(X1,X,Y1,Y);
														}
													Rtangle=false;
													oldcolor=newcolor;
													Flag=true;
												}
										else
												{	X1=X;
													Y1=Y;
													Rtangle=true;
												}
										break;
					case 79://O
					case 111:	gotoxy(5,24);
										cout<<"Radius:";
										cin>>radius;
										gotoxy(5,24);
										cout<<setw(50)<<" "<<endl;
										setcolor(newcolor);
										circle(X,Y,radius);
										putpixel(X,Y,oldcolor);
										//floodfill(X,Y,newcolor);
										break;
					case 122:// Z
					case 90:  setcolor(newcolor);
										putpixel(X,Y,oldcolor);
										floodfill(X,Y,newcolor);
										break;
					case 76://L
					case 108: if (LFlag)
										{ setcolor(newcolor);
											line(X,Y,X1,Y1);
											oldcolor=newcolor;
											LFlag=false;
										}
										else
											{ X1=X;
												Y1=Y;
												LFlag=true;
											}
										break;
					case 27: Exit=true;
				}
				T=0;
				while(kbhit()&&T<10)
				{ getch();
					T++;
				}
			}
		Pencil(Draw, oldcolor, newcolor);
	} while(!Exit);

closegraph();
};

void ShapeFill(int fx,int fy)
{ int G;
	int Max=10;
	if (getpixel(fx,fy-1) == oldcolor)
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx,fy-G) == oldcolor)
				putpixel(fx,fy-G,newcolor);
		 else
				break;
		 Items++;getch();
		}
		ShapeFill(fx,fy-(G-1));

	}
	if (getpixel(fx-1,fy) == oldcolor)
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx-G,fy) == oldcolor)
				putpixel(fx-G,fy,newcolor);
		 else
				break;Items++;
		}
		ShapeFill(fx-(G-1),fy);
	}
	if (getpixel(fx,fy+1) == oldcolor)
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx,fy+G) == oldcolor)
				putpixel(fx,fy+G,newcolor);
		 else
				break;Items++;
		}
		ShapeFill(fx,fy+(G-1));
	}
	if (getpixel(fx+1,fy) == oldcolor)
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx+G,fy) == oldcolor)
				putpixel(fx+G,fy,newcolor);
		 else
				break;Items++;
		}
		ShapeFill(fx+(G-1),fy);
	}

};
void Output_Data(int X, int Y, int Color)
{ gotoxy(2,2);
	cout<<setw(10)<<" ";
	gotoxy(2,2);
	cout<<"X:"<<X<<endl;
	gotoxy(2,3);
	cout<<setw(10)<<" ";
	gotoxy(2,3);
	cout<<"Y:"<<Y<<endl;
	gotoxy(2,4);
	cout<<setw(10)<<" ";
	gotoxy(2,4);
	cout<<"Color:"<<Color<<endl;
};

void Pencil(bool Draw, int &oldcolor, int newcolor)
{ int Temp;
	if (Draw)
		{
			oldcolor=getpixel(X,Y);
			putpixel(X,Y,newcolor);
			gotoxy(70,3);
			cout<<setw(10)<<" ";
			gotoxy(70,3);
			cout<<"Draw On";
			delay(15);
		}
		else
		{	gotoxy(70,3);
			cout<<setw(10)<<" ";
			gotoxy(70,3);
			cout<<"Draw Off";
			Temp=getpixel(X,Y);

			putpixel(X,Y,newcolor);
			if(oldcolor!=newcolor)
			 { 	oldcolor=newcolor;
					newcolor=getpixel(X,Y);
					putpixel(X,Y,15);
			 }
			delay(15);
		}
};

int Size(int X,int X1,int Y,int Y1)
{	int L,K,V=0;

	for(K=X;K<=X1;K++)
		for(L=Y;L<=Y1;L++)
				V++;
	return V;
};

/*void ShapeFill(int fx,int fy)
{ int G;
	int Max=3;
	if (getpixel(fx,fy-1) == oldcolor)
		 {

			if (getpixel(fx-1,fy) == oldcolor)
				putpixel(fx-1,fy,newcolor);
			if (getpixel(fx,fy+1) == oldcolor)
				putpixel(fx,fy+1,newcolor);
			if (getpixel(fx+1,fy) == oldcolor)
				putpixel(fx+1,fy,newcolor);
			ShapeFill(fx,fy-1);
			putpixel(fx,fy-1,newcolor);
		 }
	if (getpixel(fx-1,fy) == oldcolor)
		 {

			if (getpixel(fx,fy-1) == oldcolor)
				putpixel(fx,fy-1,newcolor);
			if (getpixel(fx,fy+1) == oldcolor)
				putpixel(fx,fy+1,newcolor);
			if (getpixel(fx+1,fy) == oldcolor)
				putpixel(fx+1,fy,newcolor);
			ShapeFill(fx-1,fy);
			putpixel(fx-1,fy,newcolor);
		 }
	if (getpixel(fx,fy+1) == oldcolor)
		 {

			if (getpixel(fx,fy-1) == oldcolor)
				putpixel(fx,fy-1,newcolor);
			if (getpixel(fx-1,fy) == oldcolor)
				putpixel(fx-1,fy,newcolor);
			if (getpixel(fx+1,fy) == oldcolor)
				putpixel(fx+1,fy,newcolor);
			ShapeFill(fx,fy+1);
			putpixel(fx,fy+1,newcolor);
		 }
	if (getpixel(fx+1,fy) == oldcolor)
		 {

			if (getpixel(fx,fy-1) == oldcolor)
				putpixel(fx,fy-1,newcolor);
			if (getpixel(fx,fy+1) == oldcolor)
				putpixel(fx,fy+1,newcolor);
			if (getpixel(fx-1,fy) == oldcolor)
				putpixel(fx-1,fy,newcolor);
			ShapeFill(fx+1,fy);
			putpixel(fx+1,fy,newcolor);
		 }
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx,fy-G) == oldcolor)
				putpixel(fx,fy-G,newcolor);
		 else
				break;
		}
		ShapeFill(fx,fy-(G-1));
	}
	if (getpixel(fx-1,fy) == oldcolor)
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx-G,fy) == oldcolor)
				putpixel(fx-G,fy,newcolor);
		 else
				break;
		}
		ShapeFill(fx-(G-1),fy);
	}
	if (getpixel(fx,fy+1) == oldcolor)
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx,fy+G) == oldcolor)
				putpixel(fx,fy+G,newcolor);
		 else
				break;
		}
		ShapeFill(fx,fy+(G-1));
	}
	if (getpixel(fx+1,fy) == oldcolor)
	{ for(G=1;G<Max;G++)
		{if(getpixel(fx+G,fy) == oldcolor)
				putpixel(fx+G,fy,newcolor);
		 else
				break;
		}
		ShapeFill(fx+(G-1),fy);
	}

}  */
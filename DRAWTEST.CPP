

#include <iomanip.h>
#include <string.h>
#include <iostream.h>
#include <apstring.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <gmouse.c>
#include <svga.h>
//#include <dgraph.h>
//#include <graphics.inc>

void ShapeFill(int,int);
void Output_Data(int,int,int,int);
void test();
int oldcolor, newcolor,X,Y,I,X1,Y1,radius,Button, Max;
bool Exit, Draw, Rtangle, Flag, LFlag,Hide;

void main()
{
gr_init(SVGA64K,6, "c:\\tc\\bgi");// middle value was 6

cleardevice();
Exit=Draw=LFlag=false;
X=Y=150;
newcolor=15;
oldcolor=0;
Output_Data(X,Y,newcolor,oldcolor);
putpixel(X,Y,newcolor);
//for(I=0;I<16;I++)
SetMouse();
ShowMouse();
do{
		if (kbhit())
			{ Output_Data(X,Y,newcolor,oldcolor);

				switch(getch())
				{ case 64://@
									cleardevice();
									Output_Data(X,Y,newcolor,oldcolor);
									putpixel(X,Y,newcolor);
									break;
					case 99:// C
					case 67:
									gotoxy(5,24);
									cout<<"New Color (0-15):";
									cin>>newcolor;
									gotoxy(5,24);
									cout<<setw(20)<<" "<<endl;
									gotoxy(2,4);
									cout<<setw(12)<<" "<<endl;
									gotoxy(2,4);
									cout<<"New Color:"<<newcolor<<endl;
									setcolor(newcolor);
									putpixel(X,Y,newcolor);
									break;
					case 70:// F
					case 102: HideMouse();
										moveto(X,Y);
										Max=0;
										ShapeFill(X,Y);
										oldcolor=newcolor;
										setcolor(newcolor);
										Flag=true;
										ShowMouse();
										break;
					case 82:// R
					case 114: if (Rtangle)
												{ setcolor(newcolor);
													if (X1>X)
														{ HideMouse();
															rectangle(X,Y,X1,Y1);
															gotoxy(5,24);
															cout<<setw(20)<<" ";
															gotoxy(5,24);
//															cout<<"Size:"<<Size(X,X1,Y,Y1);
															ShowMouse();
														}
													else
														{ HideMouse();
															rectangle(X1,Y1,X,Y);
															gotoxy(5,24);
															cout<<setw(20)<<" ";
															gotoxy(5,24);
//															cout<<"Size:"<<Size(X1,X,Y1,Y);
															ShowMouse();
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
					case 13: test();
					case 27: Exit=true;
									} //End of Case
			} //End of If

				gotoxy(10,25);
				cout<<GetMouseButton();
				if(GetMouseButton()==1)
					{ HideMouse();
						putpixel(X,Y,oldcolor);
						X=GetMouseX();
						Y=GetMouseY();
						oldcolor=getpixel(X,Y);
						putpixel(X,Y,newcolor);
						ShowMouse();
						Output_Data(X,Y,newcolor,oldcolor);
					}
			//	if(GetMouseButton()==2)
				//		Exit=true;

} while(!Exit);

//getch();
closegraph();
}

void Output_Data(int X, int Y, int NColor, int OColor)
{ gotoxy(2,2);
	cout<<setw(10)<<" ";
	gotoxy(2,2);
	cout<<"X:"<<X<<endl;
	gotoxy(2,3);
	cout<<setw(10)<<" ";
	gotoxy(2,3);
	cout<<"Y:"<<Y<<endl;
	gotoxy(2,4);
	cout<<setw(13)<<" ";
	gotoxy(2,4);
	cout<<"New Color:"<<NColor<<endl;
	gotoxy(2,5);
	cout<<setw(13)<<" ";
	gotoxy(2,5);
	cout<<"Old Color:"<<OColor<<endl;

}

void ShapeFill(int FX, int FY)
{ int G = 10;
	bool Repeat;

	do { Repeat = false;
			 for(I=0;I<G;I++)
				{	if (getpixel(FX,FY-I) == oldcolor) //up
							putpixel(FX,FY-I,newcolor);
					else if(getpixel(FX,FY-I)!=newcolor)
								 {	Repeat=true;
										break;
								 }

				}	delay(20);	 ShapeFill(FX,FY-(I-1));

			 for(I=0;I<G;I++)
				{	if (getpixel(FX-I,FY) == oldcolor) //right
							putpixel(FX-I,FY,newcolor);
					else if(getpixel(FX-I,FY)!=newcolor)
								 {	Repeat=true;
										break;
								 }
				}
						 ShapeFill(FX-(I-1),FY);
			 for(I=0;I<G;I++)
				{	if (getpixel(FX,FY+I) == oldcolor) //up
							putpixel(FX,FY+I,newcolor);
					else if(getpixel(FX,FY+I)!=newcolor)
								 {	Repeat=true;
										break;
								 }
				}		 ShapeFill(FX,FY+(I-1));
			 for(I=0;I<G;I++)
				{	if (getpixel(FX+I,FY) == oldcolor) //up
							putpixel(FX+I,FY,newcolor);
					else if(getpixel(FX+I,FY)!=newcolor)
								 {	Repeat=true;
										break;
								 }
				}		 ShapeFill(FX+I,FY);

			 G--;
			}while(!Repeat);
}

void test()
{ double X, Y;
	double Slope, PX, PY;
 X=GetMouseX();
 Y=GetMouseY();
 Slope = X/Y;

}

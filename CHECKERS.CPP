// Program:
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
//#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>


//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int I,J,X,Y,Row,Column;
//Proto Section
	void gr_start( int &, int &, int &);
	void build_board();
	void move_square(int & , int &);
void main()
{ clrscr();
	gr_start(grdriver, grmode, errorcode);
	build_board();
	Row=3;
	Column=2;
	move_square(Row, Column);
	//getch();

};
void gr_start(int & grdriver, int & grmode, int & errorcode)
{ grdriver = VGA;
	grmode= VGAHI;
	initgraph(&grdriver, &grmode, "C:\\TC\\BGI");
	errorcode=graphresult();
	if (errorcode!=grOk)
		{ clrscr();
			cout<<"Error:"<<errorcode<<endl;
			cout<<"Press Return to Continue.";
			getch();
			exit(1);
		}
};

void build_board()
{ int R,C;
	cleardevice();
		for (R=0; R<8; R++)
		for (C=0; C<8; C++)
			if (R%2 == 0)
				if (C%2 == 0)
					 { setfillstyle(1,4);
						 bar((R*60),(C*60),(R*60)+60,(C*60)+60);
					 }
				else
					 { setfillstyle(1,0);
						 bar((R*60),(C*60),(R*60)+60,(C*60)+60);
					 }
			else
				if (C%2 == 0)
					 { setfillstyle(1,0);
						 bar((R*60),(C*60),(R*60)+60,(C*60)+60);
					 }
				else
					 { setfillstyle(1,4);
						 bar((R*60),(C*60),(R*60)+60,(C*60)+60);
					 }
	setcolor(15);
	rectangle(0,0,480,479);

};

void move_square(int & Row, int & Column)
{ int Key;
	bool Flag;
	Key = 0;
	setcolor(14);
	rectangle(Row*60,Column*60,(Row*60)+60,(Column*60)+60);
	do {
			if (kbhit())
				{	Key = getche();
					Flag = true;
				}
			else
					Flag = false;
			switch(Key)
				{	case 75 : // Left
										if (Row >0)
											{	if (Row%2==0)
													if (Column%2==0)
															{ setcolor(4);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
															}
													else
														 { setcolor(0);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
														 }
												else
													if (Column%2==0)
															{ setcolor(0);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
															}
													else
														 { setcolor(4);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
															}
												if(Row==7)
													{	setcolor(15);
														line((Row*60)+60,Column*60,
															(Row*60)+60,(Column*60)+60);
													}
												Row--;
												setcolor(14);
												rectangle(Row*60,Column*60,(Row*60)+60,(Column*60)+60);
												Key=0;
											}
										break;
					case 77 : if (Row <7)
											{	if (Row%2==0)
													if (Column%2==0)
															{ setcolor(4);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
															}
													else
														 { setcolor(0);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
															}
												else
													if (Column%2==0)
															{ setcolor(0);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
															}
													else
														 { setcolor(4);
																rectangle(Row*60,Column*60,
																(Row*60)+60,(Column*60)+60);
															}
												if(Row==0)
													{	setcolor(15);
														line(Row*60,Column*60,Row*60,(Column*60)+60);
													}
												Row++;
												setcolor(14);
												rectangle(Row*60,Column*60,(Row*60)+60,(Column*60)+60);
												Key=0;
											}
				}
			}while(Key!=27);
};

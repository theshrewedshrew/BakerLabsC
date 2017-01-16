#include<iostream.h>
#include<iomanip.h>
#include<conio.h>
#include<stdlib.h>
#include<apvector.h>
#include<apmatrix.h>
#include<fstream.h>
#include<graphics.h>
#include<dos.h>

//Structures Section

//Constant Section

//Variable Section
int grdriver,grmode,errorcode;

//Prototype Section
void gr_start(int &,int &,int &);
void c_curve(int x1, int y1, int x2, int y2, int level)
{
	int xm, ym;

	if (level == 0)
		line(x1, y1, x2, y2);
	else
	{
		xm = (x1 + x2 + y1 - y2) / 2;
		ym = (x2 + y1 + y2 - x1) / 2;
		c_curve(x1, y1, xm, ym, level - 1);
		c_curve(xm, ym, x2, y2, level - 1);
	}
}

void main()
{
	clrscr();
	gr_start(grdriver,grmode,errorcode);

	//start of code
	int level = 0;
	int ch;
	ch = 's';
	while (ch != 'q')
	{
		cleardevice();
		c_curve(350, 130, 350, 350, level);
		ch = getch();
		level++;
	}
	cleardevice();
	//end of code

	closegraph();
}

void gr_start(int & grdriver,int & grmode,int & errorcode)
{
	grdriver=VGA;
	grmode=VGAHI;
	initgraph(& grdriver, & grmode, "C:\\TC\\BGI");
	errorcode=graphresult();
	if(errorcode!=grOk)
	{
		clrscr();
		cout<<"error:"<<errorcode<<endl;
		cout<<"Press Return to Continue.";
		getch();
		exit(1);
	}
}
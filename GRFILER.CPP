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
#include <bitmap.h>
#include <fstream.h>


//Const Section

//Var Section
	int grdriver, grmode, errorcode;
	int I,J,W,H,X,Y,Row,Column, Color;
	apstring Name,FName,OFName;
	image Image;
	ofstream Out_file;
	ifstream In_file;
//Proto Section
	void gr_start( int &, int &, int &);

void main()
{ clrscr();
	FName="a:\\";
	OFName="a:\\";
	cout<<"Plase enter the file name from the A drive:";
	getline(cin,Name);
	FName+=Name;
	FName+=".bmp";
	OFName+=Name;
	OFName+=".dat";
	cout<<"How wide in pixels is the image?";
	cin>>W;
	cout<<"How high in pixels is the image?";
	cin>>H;
	cout<<FName.c_str();
	getch();

	gr_start(grdriver, grmode, errorcode);
	graphinit(GR16);
	Image.open(FName.c_str());
	Image.draw (50,50);
	Out_file.open(OFName.c_str());
	Out_file<<W<<" "<<H<<endl;
	for(X=50;X<(50+W);X++)
	 {	for(Y=50;Y<(50+H);Y++)
			{ putpixel(200+X,200+Y,getpixel(X,Y));
				Out_file<<getpixel(X,Y)<<" ";
			}
			Out_file<<endl;
	 }
	getch();
	Out_file.close();
	closegraph();
	In_file.open(OFName.c_str());
	In_file>>W;
	In_file>>H;
	gr_start(grdriver, grmode, errorcode);
	for(X=0;X<W;X++)
	 {	for(Y=0;Y<H;Y++)
			{ In_file>>Color;
				putpixel(X,Y,Color);
			}
	 }
	getch();
	In_file.close();
	closegraph();

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

//Erick Van Houten

#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
#include <iostream.h>
#include <bool.h>
//X=639 Y=479
struct shot   //includes all information about the projectiles
{
	int x,y,life;
	float xv,yv,xr,yr;
};

struct astroid  //includes all information about the astroids
{
	int x,y,size;
	float xv,yv,xr,yr;
};

float xr,yr; //xr&yr- the 'real' location of the ship
float yv,xv; //yv&xv- vecotors of the ship
int x,y,deg,snum=0,rnum=0,wait=0; //x&y- the x,y location of the ship, used for graphic funtions
shot shots[5];	//array of above structure
astroid roids[40]; //array of above structure
int ba=0;
int key;
bool Exit;
void shipstill(int &,int &,int &,float &,float &,float &,float &);
void shipmove(int &,int &,int &,float &,float &,float &,float &);
void astroidlarge(int,int);
void astroidmed(int,int);
void astroidsmall(int,int);
void createroids(astroid *,int &rnum);
void drawroids(astroid *,shot *);
void roidcollisioncheck(astroid &,shot *,int,int,int &,astroid *);
void createshot(int,shot &,int &,float,float);
void moveshots(shot *);

void main ()
{
	clrscr();
	randomize();

	int graphdriver=DETECT,graphmode;
	initgraph(&graphdriver,&graphmode,"C:\\tc\\bgi");

	setfillstyle(0,0);
	setcolor(15);

	xr=320;
	yr=240;
	Exit=false;
	//createroids(roids,rnum);

do{

			if(wait==0)
			{
				if(kbhit())
				 switch(getche())
					{ case 75:
										deg+=25;
										shipstill(x,y,deg,xv,yv,xr,yr);
										break;
						case 77:
										deg-=25;
										shipstill(x,y,deg,xv,yv,xr,yr);
										break;
						case 72:
										shipmove(x,y,deg,xv,yv,xr,yr);
										break;
						case 32:if (snum==1)
											{	gotoxy(45,1);
												cout<<"XR:"<<xr<<" YR:"<<yr;
												cout<<" Shot XR:"<<shots[snum].xr;
												cout<<" Shot YR:"<<shots[snum].yr;
											}
										createshot(deg,shots[snum],snum,xr,yr);
										if (snum==1)
											{	gotoxy(1,1);
												cout<<"XR:"<<xr<<" YR:"<<yr;
												cout<<" Shot XR:"<<shots[snum].xr;
												cout<<" Shot YR:"<<shots[snum].yr;
											}
										break;
						case 27: Exit = true;
					}
				else
					shipstill(x,y,deg,xv,yv,xr,yr);

			}
			else
				wait--;

			moveshots(shots);

		 //	drawroids(roids,shots);

			delay(25);
	}while(!Exit);
};

void shipstill(int &x,int &y,int &deg,float &xv,float &yv,float &xr,float &yr)
{
	//Draws ship while 'thrust' is not being aplied

	//***********************************
	//This area slows the ship gradually
	if(xv!=0)
	{
		if((xv>-1&&xv<0)||(xv<1&&xv>0))
				xv=0;
		else
				xv/=1.01;
	}
	if(yv!=0)
	{
		if((yv>-1&&yv<0)||(yv<1&&yv>0))
			yv=0;
		else
			yv/=1.01;
	}
	//************************************

	//************************************
	//This area 'rolls' the ship around the screen
	if(x>639||x<0||y>479||y<0)
	{

		if(x>639)
		{
			xr=0;
		}
		else if(x<0)
		{
			xr=639;
		}
		if(y>479)
		{
			yr=0;
		}
		else if(y<0)
		{
			yr=479;
		}
	}
	//*************************************

	xr+=xv;
	yr+=yv;

	setcolor(0);
	fillellipse(x,y,11,11);
	setcolor(15);

	x=xr;
	y=yr;

	//**************************************
	//Acutally Drawing the ship
	line((8*cos(deg-40))+x,(8*sin(deg-40))+y,(8*cos(deg))+x,(8*sin(deg))+y);
	line((8*cos(deg))+x,(8*sin(deg))+y,(8*cos(deg+40))+x,(8*sin(deg+40))+y);
	line((5*cos(deg-180))+x,5*sin(deg-180)+y,(5*cos(deg+180))+x,(5*sin(deg+180))+y);
	//**************************************
};

void shipmove(int &x,int &y,int &deg,float &xv,float &yv,float &xr,float &yr)
{
	//draws ship while 'thrust' is being applied

	xv+=cos(deg);
	yv+=sin(deg);

	//**************************************
	//'Rolls' the ship around the screen
	if(x>639||x<0||y>479||y<0)
	{
		if(x>639)
		{
			xr=0;
			setcolor(0);
			fillellipse(x,y,11,11);
			setcolor(15);
		}
		else if(x<0)
		{
			xr=639;
			setcolor(0);
			fillellipse(x,y,11,11);
			setcolor(15);
		}
		if(y>479)
		{
			yr=0;
			setcolor(0);
			fillellipse(x,y,11,11);
			setcolor(15);
		}
		else if(y<0)
		{
			yr=479;
			setcolor(0);
			fillellipse(x,y,11,11);
			setcolor(15);
		}
	}
	//***************************************

	xr+=xv;
	yr+=yv;

	setcolor(0);
	fillellipse(x,y,11,11);
	setcolor(15);

	x=xr;
	y=yr;

	//***************************************
	//Acutally draws the ship
	line((8*cos(deg-40))+x,(8*sin(deg-40))+y,(8*cos(deg))+x,(8*sin(deg))+y);
	line((8*cos(deg))+x,(8*sin(deg))+y,(8*cos(deg+40))+x,(8*sin(deg+40))+y);
	line((5*cos(deg-180))+x,5*sin(deg-180)+y,(5*cos(deg+180))+x,(5*sin(deg+180))+y);
	line((4*cos(deg-161))+x,(4*sin(deg-161))+y,(10*cos(deg+185))+x,(10*sin(deg+185))+y);
	line((10*cos(deg+185))+x,(10*sin(deg+185))+y,(7*cos(deg+110))+x,(7*sin(deg+110))+y);
	line((7*cos(deg+110))+x,(7*sin(deg+110))+y,(10*cos(deg+104))+x,(10*sin(deg+104))+y);
	line((10*cos(deg+104))+x,(10*sin(deg+104))+y,(4*cos(deg+161))+x,(4*sin(deg+161))+y);
	//***************************************
};

void astroidlarge(int x,int y)
{
	//Draws large astroid
	line(x-33,y-27,x+5,y-34);
	line(x+5,y-34,x+2,y-19);
	line(x+2,y-19,x+27,y-12);
	line(x+27,y-12,x+35,y+31);
	line(x+35,y+31,x+35,y+33);
	line(x+35,y+33,x+5,y+26);
	line(x+5,y+26,x-25,y+33);
	line(x-25,y+33,x-35,y-1);
	line(x-35,y-1,x-33,y-27);
};

void astroidmed(int x,int y)
{
	//Draws Medium Astroid

	line(x-16,y-13,x+2,y-17);
	line(x+2,y-17,x+1,y-9);
	line(x+1,y-9,x+13,y-6);
	line(x+13,y-6,x+17,y+15);
	line(x+17,y+15,x+17,y+16);
	line(x+17,y+16,x+2,y+13);
	line(x+2,y+13,x-12,y+16);
	line(x-12,y+16,x-17,y);
	line(x-17,y,x-16,y-13);
};

void astroidsmall(int x,int y)
{
	//Draws Small Astroid

	line(x-8,y-6,x+1,y-8);
	line(x+1,y-8,x,y-4);
	line(x,y-4,x+6,y-3);
	line(x+6,y-3,x+8,y+7);
	line(x+8,y+7,x+8,y+8);
	line(x+8,y+8,x+1,y+6);
	line(x+1,y+6,x-6,y+8);
	line(x-6,y+8,x-8,y);
	line(x-8,y,x-8,y-6);
};

void createroids(astroid *roids,int &rnum)
{
	//Generates Values for astroids

	int cnt;

	for(cnt=0;cnt<5;cnt++)
	{
		roids[cnt].size=3;
		if(random(2))
		{
			roids[cnt].xr=random(640);
			if(random(2))
				roids[cnt].yr=random(80)+80;
			else
				roids[cnt].yr=random(80)+320;
		}
		else
		{
			roids[cnt].yr=random(480);
			if(random(2))
				roids[cnt].xr=random(106)+106;
			else
				roids[cnt].xr=random(106)+426;
		}

		//*******************************
		//Generating vectors for astroids
		roids[cnt].xv=random(1000);
		roids[cnt].yv=random(1000);
		roids[cnt].xv/=1000;
		roids[cnt].yv/=1000;
		//*******************************
		rnum++;
	}
};

void drawroids(astroid *roids,shot *shots)
{
	//Draws Astroids

	int cnt;

	for(cnt=0;cnt<40;cnt++)
	{
		if(roids[cnt].size!=0)
		{
			if(roids[cnt].size==3)
			{
				setcolor(0);
				bar(roids[cnt].x-35,roids[cnt].y-35,roids[cnt].x+35,roids[cnt].y+35);
				setcolor(15);

				roids[cnt].xr+=roids[cnt].xv;
				roids[cnt].yr+=roids[cnt].yv;
				roids[cnt].x=roids[cnt].xr;
				roids[cnt].y=roids[cnt].yr;

				astroidlarge(roids[cnt].x,roids[cnt].y);
			}
			else if(roids[cnt].size==2)
			{
				setcolor(0);
				bar(roids[cnt].x-18,roids[cnt].y-18,roids[cnt].x+18,roids[cnt].y+18);
				setcolor(15);

				roids[cnt].xr+=roids[cnt].xv;
				roids[cnt].yr+=roids[cnt].yv;
				roids[cnt].x=roids[cnt].xr;
				roids[cnt].y=roids[cnt].yr;

				astroidmed(roids[cnt].x,roids[cnt].y);
			}
			else
			{
				setcolor(0);
				bar(roids[cnt].x-10,roids[cnt].y-10,roids[cnt].x+10,roids[cnt].y+10);
				setcolor(15);

				roids[cnt].xr+=roids[cnt].xv;
				roids[cnt].yr+=roids[cnt].yv;
				roids[cnt].x=roids[cnt].xr;
				roids[cnt].y=roids[cnt].yr;

				astroidsmall(roids[cnt].x,roids[cnt].y);
			}
			if(roids[cnt].size!=0)
				roidcollisioncheck(roids[cnt],shots,x,y,rnum,roids);

			if(roids[cnt].x>639||roids[cnt].x<0||roids[cnt].y>479||roids[cnt].y<0)
			{
				if(roids[cnt].x>639)
				{
					roids[cnt].xr=0;
				}
				else if(roids[cnt].x<0)
				{
					roids[cnt].xr=639;
				}
				if(roids[cnt].y>479)
				{
					roids[cnt].yr=0;
				}
				else if(roids[cnt].y<0)
				{
					roids[cnt].yr=479;
				}
			}
		}
	}
};

void roidcollisioncheck(astroid &roid,shot *shots,int x,int y,int &rnum,
													astroid *roids)
{
	if(roid.size==3)
	{
		if((x>roid.x-35&&x<roid.x+35)&&(y>roid.y-35&&y<roid.y+35))
		{
			//life--;
			wait=100;
			setcolor(0);
			fillellipse(x,y,11,11);
			setcolor(15);

			xr=320;
			yr=240;
			xv=0;
			yv=0;

		}
		for(int cnt=0;cnt<5;cnt++)
		{
			if((shots[cnt].x>roid.x-35&&shots[cnt].x<roid.x+35)
					&&(shots[cnt].y>roid.y-35&&shots[cnt].y<roid.y+35))
			{
				rnum++;
				roid.size--;
				roid.xv=random(1000);
				roid.yv=random(1000);
				roid.xv/=500;
				roid.yv/=500;
				shots[cnt].life=0;
				shots[cnt].x=-100;
				shots[cnt].y=-100;

				setcolor(0);
				bar(roid.x-35,roid.y-35,roid.x+35,roid.y+35);
				setcolor(15);

				roids[rnum].size=roid.size;
				roids[rnum].xr=roid.xr;
				roids[rnum].yr=roid.yr;
				roids[rnum].xv=random(1000);
				roids[rnum].yv=random(1000);
				roids[rnum].xv/=100;
				roids[rnum].yv/=100;

				break;
			}
		}
	}
	else if(roid.size==2)
	{
		if((x>roid.x-18&&x<roid.x+18)&&(y>roid.y-18&&y<roid.y+18))
		{
			//life--;
			wait=100;
			setcolor(0);
			fillellipse(x,y,11,11);
			setcolor(15);

			xr=320;
			yr=240;
			xv=0;
			yv=0;
		}
		for(int cnt=0;cnt<5;cnt++)
		{
			if((shots[cnt].x>roid.x-18&&shots[cnt].x<roid.x+18)
					&&(shots[cnt].y>roid.y-18&&shots[cnt].y<roid.y+18))
			{
				rnum++;
				roid.size--;
				roid.xv=random(1000);
				roid.yv=random(1000);
				roid.xv/=250;
				roid.yv/=250;
				shots[cnt].life=0;
				shots[cnt].x=-100;
				shots[cnt].y=-100;

				setcolor(0);
				bar(roid.x-18,roid.y-18,roid.x+18,roid.y+18);
				setcolor(15);

				roids[rnum].size=roid.size;
				roids[rnum].xr=roid.xr;
				roids[rnum].yr=roid.yr;
				roids[rnum].xv=random(1000);
				roids[rnum].yv=random(1000);
				roids[rnum].xv/=1000;
				roids[rnum].yv/=1000;

				break;
			}
		}
	}
	else if(roid.size==1)
	{
		if((x>roid.x-9&&x<roid.x+9)&&(y>roid.y-9&&y<roid.y+9))
		{
			//life--;
			wait=100;
			setcolor(0);
			fillellipse(x,y,11,11);
			setcolor(15);

			xr=320;
			yr=240;
			xv=0;
			yv=0;
		}
		for(int cnt=0;cnt<5;cnt++)
		{
			if((shots[cnt].x>roid.x-9&&shots[cnt].x<roid.x+9)
					&&(shots[cnt].y>roid.y-9&&shots[cnt].y<roid.y+9))
			{
				roid.size--;
				shots[cnt].life=0;
				shots[cnt].x=-100;
				shots[cnt].y=-100;

				setcolor(0);
				bar(roid.x-18,roid.y-9,roid.x+9,roid.y+9);
				setcolor(15);

				break;
			}
		}
	}
};

void createshot(int deg,shot &shot,int &snum,float xr,float yr)
{
	//Generates Values for shots
	if(shot.life<1)
	{
		shot.xv=10*cos(deg);
		shot.yv=10*sin(deg);

		shot.xr=xr;
		shot.yr=yr;

		shot.life=40;
		putpixel(shot.xr,shot.yr-15,2);
		if(snum<4)
		{
			snum++;
		}
		else
		{
			snum=0;
		}
	}
};

void moveshots(shot *shots)
{
	//Draws and moves all shots

	int cnt;

	for(cnt=0;cnt<5;cnt++)
	{
		if(shots[cnt].life>0)
		{
			if(shots[cnt].x>639||shots[cnt].x<0||shots[cnt].y>479||shots[cnt].y<0)
			{
				if(shots[cnt].x>639)
					shots[cnt].xr=0;

				else if(shots[cnt].x<0)
							 shots[cnt].xr=639.0;

				if(shots[cnt].y>479)
					shots[cnt].yr=0;
				else if(shots[cnt].y<0)
							 shots[cnt].yr=479.0;

			}

			putpixel(shots[cnt].x,shots[cnt].y,0);
			shots[cnt].life--;

			if(shots[cnt].life>0)
			{
				shots[cnt].xr+=shots[cnt].xv;
				shots[cnt].yr+=shots[cnt].yv;
				shots[cnt].x=int(shots[cnt].xr);
				shots[cnt].y=int(shots[cnt].yr);
				//putpixel(shots[cnt].x,shots[cnt].y-20,4);
				putpixel(shots[cnt].x,shots[cnt].y,15);
			}
			else
			{
				putpixel(shots[cnt].x,shots[cnt].y,0);
				shots[cnt].x=xr;//-100;
				shots[cnt].y=yr;//-100;
			}
		}
	}
};

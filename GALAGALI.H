//Shannon Lesher & Rachel Jaggers
//Galaga Library - Images!

#include <alloc.h>

void far *A,*C,*D,*E,*F,*B;
char BlueM,GreenM,RedM;
char BlueS,GreenS,RedS;
char BlueA,GreenA,RedA;
unsigned long Size;
int Main, Sec, Acc;
void images ();

void images ()
{
	//Blue Bug no Closed Wings
Main=1; // Blue
Sec=5; // Purple
Acc=13;// Pink

RedM=0;
GreenM = 105;
BlueM = 210;
RedS=142;
GreenS=96;
BlueS=159;
RedA=233;
GreenA=150;
BlueA=204;
//*
putpixel(7,4,RedM,GreenM,BlueM);
putpixel(9,4,RedM,GreenM,BlueM);
putpixel(7,5,RedM,GreenM,BlueM);
putpixel(9,5,RedM,GreenM,BlueM);
putpixel(7,6,RedA,GreenA,BlueA);
putpixel(7,7,RedA,GreenA,BlueA);
putpixel(9,6,RedA,GreenA,BlueA);
putpixel(9,7,RedA,GreenA,BlueA);
putpixel(7,8,RedM,GreenM,BlueM);
putpixel(7,9,RedM,GreenM,BlueM);
putpixel(9,8,RedM,GreenM,BlueM);
putpixel(9,9,RedM,GreenM,BlueM);
putpixel(7,10,RedS,GreenS,BlueS);
putpixel(7,11,RedS,GreenS,BlueS);
putpixel(7,12,RedS,GreenS,BlueS);
putpixel(7,13,RedS,GreenS,BlueS);
putpixel(9,10,RedS,GreenS,BlueS);
putpixel(9,11,RedS,GreenS,BlueS);
putpixel(9,12,RedS,GreenS,BlueS);
putpixel(9,13,RedS,GreenS,BlueS);
putpixel(7,14,RedA,GreenA,BlueA);
putpixel(7,15,RedA,GreenA,BlueA);
putpixel(9,14,RedA,GreenA,BlueA);
putpixel(9,15,RedA,GreenA,BlueA);


putpixel(8,5,RedM,GreenM,BlueM);
putpixel(8,6,RedM,GreenM,BlueM);
putpixel(8,7,RedM,GreenM,BlueM);
putpixel(8,8,RedM,GreenM,BlueM);
putpixel(8,9,RedS,GreenS,BlueS);
putpixel(8,10,RedS,GreenS,BlueS);
putpixel(8,11,RedS,GreenS,BlueS);
putpixel(8,12,RedS,GreenS,BlueS);

putpixel(6,6,RedA,GreenA,BlueA);
putpixel(6,7,RedA,GreenA,BlueA);
putpixel(6,8,RedM,GreenM,BlueM);
putpixel(6,9,RedS,GreenS,BlueS);
putpixel(6,10,RedS,GreenS,BlueS);
putpixel(6,11,RedS,GreenS,BlueS);
putpixel(6,12,RedS,GreenS,BlueS);
putpixel(6,13,RedS,GreenS,BlueS);

putpixel(10,6,RedA,GreenA,BlueA);
putpixel(10,7,RedA,GreenA,BlueA);
putpixel(10,8,RedM,GreenM,BlueM);
putpixel(10,9,RedS,GreenS,BlueS);
putpixel(10,10,RedS,GreenS,BlueS);
putpixel(10,11,RedS,GreenS,BlueS);
putpixel(10,12,RedS,GreenS,BlueS);
putpixel(10,13,RedS,GreenS,BlueS);

putpixel(5,6,RedM,GreenM,BlueM);
putpixel(5,7,RedM,GreenM,BlueM);
putpixel(5,9,RedM,GreenM,BlueM);
putpixel(5,10,RedM,GreenM,BlueM);
putpixel(5,11,RedM,GreenM,BlueM);
putpixel(5,12,RedM,GreenM,BlueM);
putpixel(5,13,RedM,GreenM,BlueM);
putpixel(5,14,RedM,GreenM,BlueM);

putpixel(11,6,RedM,GreenM,BlueM);
putpixel(11,7,RedM,GreenM,BlueM);
putpixel(11,9,RedM,GreenM,BlueM);
putpixel(11,10,RedM,GreenM,BlueM);
putpixel(11,11,RedM,GreenM,BlueM);
putpixel(11,12,RedM,GreenM,BlueM);
putpixel(11,13,RedM,GreenM,BlueM);
putpixel(11,14,RedM,GreenM,BlueM);

putpixel(4,6,RedM,GreenM,BlueM);
putpixel(4,10,RedM,GreenM,BlueM);
putpixel(4,11,RedM,GreenM,BlueM);
putpixel(4,12,RedM,GreenM,BlueM);
putpixel(4,13,RedM,GreenM,BlueM);
putpixel(4,14,RedM,GreenM,BlueM);
putpixel(4,15,RedM,GreenM,BlueM);
putpixel(4,16,RedM,GreenM,BlueM);
putpixel(4,17,RedM,GreenM,BlueM);
putpixel(4,18,RedM,GreenM,BlueM);
putpixel(4,19,RedM,GreenM,BlueM);

putpixel(12,6,RedM,GreenM,BlueM);
putpixel(12,10,RedM,GreenM,BlueM);
putpixel(12,11,RedM,GreenM,BlueM);
putpixel(12,12,RedM,GreenM,BlueM);
putpixel(12,13,RedM,GreenM,BlueM);
putpixel(12,14,RedM,GreenM,BlueM);
putpixel(12,15,RedM,GreenM,BlueM);
putpixel(12,16,RedM,GreenM,BlueM);
putpixel(12,17,RedM,GreenM,BlueM);
putpixel(12,18,RedM,GreenM,BlueM);
putpixel(12,19,RedM,GreenM,BlueM);

putpixel(3,20,RedM,GreenM,BlueM);
putpixel(3,10,RedM,GreenM,BlueM);
putpixel(3,11,RedM,GreenM,BlueM);
putpixel(3,12,RedM,GreenM,BlueM);
putpixel(3,13,RedA,GreenA,BlueA);
putpixel(3,14,RedA,GreenA,BlueA);
putpixel(3,15,RedM,GreenM,BlueM);
putpixel(3,16,RedA,GreenA,BlueA);
putpixel(3,17,RedA,GreenA,BlueA);
putpixel(3,18,RedM,GreenM,BlueM);
putpixel(3,19,RedM,GreenM,BlueM);

putpixel(13,20,RedM,GreenM,BlueM);
putpixel(13,10,RedM,GreenM,BlueM);
putpixel(13,11,RedM,GreenM,BlueM);
putpixel(13,12,RedM,GreenM,BlueM);
putpixel(13,13,RedA,GreenA,BlueA);
putpixel(13,14,RedA,GreenA,BlueA);
putpixel(13,15,RedM,GreenM,BlueM);
putpixel(13,16,RedA,GreenA,BlueA);
putpixel(13,17,RedA,GreenA,BlueA);
putpixel(13,18,RedM,GreenM,BlueM);
putpixel(13,19,RedM,GreenM,BlueM);

putpixel(2,20,RedM,GreenM,BlueM);
putpixel(2,11,RedM,GreenM,BlueM);
putpixel(2,12,RedM,GreenM,BlueM);
putpixel(2,13,RedM,GreenM,BlueM);
putpixel(2,14,RedM,GreenM,BlueM);
putpixel(2,15,RedA,GreenA,BlueA);
putpixel(2,16,RedA,GreenA,BlueA);
putpixel(2,17,RedA,GreenA,BlueA);
putpixel(2,18,RedM,GreenM,BlueM);
putpixel(2,19,RedM,GreenM,BlueM);

putpixel(14,20,RedM,GreenM,BlueM);
putpixel(14,11,RedM,GreenM,BlueM);
putpixel(14,12,RedM,GreenM,BlueM);
putpixel(14,13,RedM,GreenM,BlueM);
putpixel(14,14,RedM,GreenM,BlueM);
putpixel(14,15,RedA,GreenA,BlueA);
putpixel(14,16,RedA,GreenA,BlueA);
putpixel(14,17,RedA,GreenA,BlueA);
putpixel(14,18,RedM,GreenM,BlueM);
putpixel(14,19,RedM,GreenM,BlueM);

putpixel(1,11,RedM,GreenM,BlueM);
putpixel(1,14,RedM,GreenM,BlueM);
putpixel(1,15,RedM,GreenM,BlueM);
putpixel(1,16,RedM,GreenM,BlueM);
putpixel(1,17,RedM,GreenM,BlueM);
putpixel(1,18,RedM,GreenM,BlueM);
putpixel(1,19,RedM,GreenM,BlueM);

putpixel(15,11,RedM,GreenM,BlueM);
putpixel(15,14,RedM,GreenM,BlueM);
putpixel(15,15,RedM,GreenM,BlueM);
putpixel(15,16,RedM,GreenM,BlueM);
putpixel(15,17,RedM,GreenM,BlueM);
putpixel(15,18,RedM,GreenM,BlueM);
putpixel(15,19,RedM,GreenM,BlueM);

Size=imagesize(0,0,20,20);
A=farmalloc(Size);
getimage(0,0,20,20,A);
cleardevice();

//Blue Bug With Closed Wings

putpixel(7,4,RedM,GreenM,BlueM);
putpixel(7,5,RedM,GreenM,BlueM);
putpixel(7,6,RedA,GreenA,BlueA);
putpixel(7,7,RedA,GreenA,BlueA);
putpixel(7,8,RedM,GreenM,BlueM);
putpixel(7,9,RedM,GreenM,BlueM);
putpixel(7,10,RedS,GreenS,BlueS);
putpixel(7,11,RedS,GreenS,BlueS);
putpixel(7,12,RedS,GreenS,BlueS);
putpixel(7,13,RedS,GreenS,BlueS);
putpixel(7,14,RedA,GreenA,BlueA);
putpixel(7,15,RedA,GreenA,BlueA);
putpixel(7,18,RedM,GreenM,BlueM);
putpixel(7,19,RedM,GreenM,BlueM);


putpixel(9,4,RedM,GreenM,BlueM);
putpixel(9,5,RedM,GreenM,BlueM);
putpixel(9,6,RedA,GreenA,BlueA);
putpixel(9,7,RedA,GreenA,BlueA);
putpixel(9,8,RedM,GreenM,BlueM);
putpixel(9,9,RedM,GreenM,BlueM);
putpixel(9,10,RedS,GreenS,BlueS);
putpixel(9,11,RedS,GreenS,BlueS);
putpixel(9,12,RedS,GreenS,BlueS);
putpixel(9,13,RedS,GreenS,BlueS);
putpixel(9,14,RedA,GreenA,BlueA);
putpixel(9,15,RedA,GreenA,BlueA);
putpixel(9,18,RedM,GreenM,BlueM);
putpixel(9,19,RedM,GreenM,BlueM);


putpixel(8,5,RedM,GreenM,BlueM);
putpixel(8,6,RedM,GreenM,BlueM);
putpixel(8,7,RedM,GreenM,BlueM);
putpixel(8,8,RedM,GreenM,BlueM);
putpixel(8,9,RedS,GreenS,BlueS);
putpixel(8,10,RedS,GreenS,BlueS);
putpixel(8,11,RedS,GreenS,BlueS);
putpixel(8,12,RedS,GreenS,BlueS);

putpixel(6,6,RedA,GreenA,BlueA);
putpixel(6,7,RedA,GreenA,BlueA);
putpixel(6,8,RedM,GreenM,BlueM);
putpixel(6,9,RedS,GreenS,BlueS);
putpixel(6,10,RedS,GreenS,BlueS);
putpixel(6,11,RedS,GreenS,BlueS);
putpixel(6,12,RedS,GreenS,BlueS);
putpixel(6,13,RedS,GreenS,BlueS);
putpixel(6,17,RedM,GreenM,BlueM);
putpixel(6,18,RedM,GreenM,BlueM);

putpixel(10,6,RedA,GreenA,BlueA);
putpixel(10,7,RedA,GreenA,BlueA);
putpixel(10,8,RedM,GreenM,BlueM);
putpixel(10,9,RedS,GreenS,BlueS);
putpixel(10,10,RedS,GreenS,BlueS);
putpixel(10,11,RedS,GreenS,BlueS);
putpixel(10,12,RedS,GreenS,BlueS);
putpixel(10,13,RedS,GreenS,BlueS);
putpixel(10,17,RedM,GreenM,BlueM);
putpixel(10,18,RedM,GreenM,BlueM);

putpixel(5,6,RedM,GreenM,BlueM);
putpixel(5,7,RedM,GreenM,BlueM);
putpixel(5,9,RedM,GreenM,BlueM);
putpixel(5,10,RedM,GreenM,BlueM);
putpixel(5,11,RedM,GreenM,BlueM);
putpixel(5,15,RedM,GreenM,BlueM);
putpixel(5,16,RedM,GreenM,BlueM);
putpixel(5,17,RedM,GreenM,BlueM);

putpixel(11,6,RedM,GreenM,BlueM);
putpixel(11,7,RedM,GreenM,BlueM);
putpixel(11,9,RedM,GreenM,BlueM);
putpixel(11,10,RedM,GreenM,BlueM);
putpixel(11,11,RedM,GreenM,BlueM);
putpixel(11,15,RedM,GreenM,BlueM);
putpixel(11,16,RedM,GreenM,BlueM);
putpixel(11,17,RedM,GreenM,BlueM);

putpixel(4,6,RedM,GreenM,BlueM);
putpixel(4,10,RedM,GreenM,BlueM);
putpixel(4,11,RedM,GreenM,BlueM);
putpixel(4,12,RedM,GreenM,BlueM);
putpixel(4,13,RedM,GreenM,BlueM);
putpixel(4,14,RedM,GreenM,BlueM);
putpixel(4,15,RedM,GreenM,BlueM);
putpixel(4,16,RedM,GreenM,BlueM);

putpixel(12,6,RedM,GreenM,BlueM);
putpixel(12,10,RedM,GreenM,BlueM);
putpixel(12,11,RedM,GreenM,BlueM);
putpixel(12,12,RedM,GreenM,BlueM);
putpixel(12,13,RedM,GreenM,BlueM);
putpixel(12,14,RedM,GreenM,BlueM);
putpixel(12,15,RedM,GreenM,BlueM);
putpixel(12,16,RedM,GreenM,BlueM);

putpixel(3,10,RedM,GreenM,BlueM);
putpixel(3,11,RedM,GreenM,BlueM);
putpixel(3,12,RedM,GreenM,BlueM);
putpixel(3,13,RedM,GreenM,BlueM);
putpixel(3,14,RedM,GreenM,BlueM);
putpixel(3,15,RedM,GreenM,BlueM);

putpixel(13,10,RedM,GreenM,BlueM);
putpixel(13,11,RedM,GreenM,BlueM);
putpixel(13,12,RedM,GreenM,BlueM);
putpixel(13,13,RedM,GreenM,BlueM);
putpixel(13,14,RedM,GreenM,BlueM);
putpixel(13,15,RedM,GreenM,BlueM);

putpixel(2,11,RedM,GreenM,BlueM);
putpixel(2,12,RedM,GreenM,BlueM);

putpixel(14,11,RedM,GreenM,BlueM);
putpixel(14,12,RedM,GreenM,BlueM);

putpixel(1,11,RedM,GreenM,BlueM);

putpixel(15,11,RedM,GreenM,BlueM);

//Size=imagesize(0,0,20,20);
C=farmalloc(Size);
getimage(0,0,20,20,C);
cleardevice();

//BOTH Arrows


putpixel(5,3,RedA,GreenA,BlueA);
putpixel(5,4,RedA,GreenA,BlueA);
putpixel(5,5,RedA,GreenA,BlueA);
putpixel(4,5,RedA,GreenA,BlueA);
putpixel(6,5,RedA,GreenA,BlueA);
putpixel(4,6,RedA,GreenA,BlueA);
putpixel(6,6,RedA,GreenA,BlueA);
putpixel(5,6,RedS,GreenS,BlueS);
putpixel(5,7,RedM,GreenM,BlueM);
putpixel(5,8,RedM,GreenM,BlueM);
putpixel(5,9,RedM,GreenM,BlueM);
putpixel(5,10,RedM,GreenM,BlueM);
putpixel(5,11,RedM,GreenM,BlueM);
Size=imagesize(0,0,15,15);
E=farmalloc(Size);
getimage(0,0,15,15,E);
cleardevice();


putpixel(4,7,RedM,GreenM,BlueM);
putpixel(4,7,RedM,GreenM,BlueM);
putpixel(4,8,RedM,GreenM,BlueM);
putpixel(4,8,RedM,GreenM,BlueM);
putpixel(6,7,RedM,GreenM,BlueM);
putpixel(6,7,RedM,GreenM,BlueM);
putpixel(6,8,RedM,GreenM,BlueM);
putpixel(6,8,RedM,GreenM,BlueM);
putpixel(5,3,RedS,GreenS,BlueS);
putpixel(5,4,RedS,GreenS,BlueS);
putpixel(5,5,RedS,GreenS,BlueS);
putpixel(5,6,RedS,GreenS,BlueS);
putpixel(5,7,RedS,GreenS,BlueS);
putpixel(5,8,RedM,GreenM,BlueM);
putpixel(5,9,RedM,GreenM,BlueM);
Size=imagesize(0,0,15,15);
F=farmalloc(Size);
getimage(0,0,15,15,F);
cleardevice();

//Green Bug With No Closed Wings



putpixel(7,4,RedM,GreenM,BlueM);
putpixel(9,4,RedM,GreenM,BlueM);
putpixel(7,5,RedM,GreenM,BlueM);
putpixel(9,5,RedM,GreenM,BlueM);
putpixel(7,6,RedA,GreenA,BlueA);
putpixel(7,7,RedA,GreenA,BlueA);
putpixel(9,6,RedA,GreenA,BlueA);
putpixel(9,7,RedA,GreenA,BlueA);
putpixel(7,8,RedM,GreenM,BlueM);
putpixel(7,9,RedM,GreenM,BlueM);
putpixel(9,8,RedM,GreenM,BlueM);
putpixel(9,9,RedM,GreenM,BlueM);
putpixel(7,10,RedS,GreenS,BlueS);
putpixel(7,11,RedS,GreenS,BlueS);
putpixel(7,12,RedS,GreenS,BlueS);
putpixel(7,13,RedS,GreenS,BlueS);
putpixel(9,10,RedS,GreenS,BlueS);
putpixel(9,11,RedS,GreenS,BlueS);
putpixel(9,12,RedS,GreenS,BlueS);
putpixel(9,13,RedS,GreenS,BlueS);
putpixel(7,14,RedA,GreenA,BlueA);
putpixel(7,15,RedA,GreenA,BlueA);
putpixel(9,14,RedA,GreenA,BlueA);
putpixel(9,15,RedA,GreenA,BlueA);


putpixel(8,5,RedM,GreenM,BlueM);
putpixel(8,6,RedM,GreenM,BlueM);
putpixel(8,7,RedM,GreenM,BlueM);
putpixel(8,8,RedM,GreenM,BlueM);
putpixel(8,9,RedS,GreenS,BlueS);
putpixel(8,10,RedS,GreenS,BlueS);
putpixel(8,11,RedS,GreenS,BlueS);
putpixel(8,12,RedS,GreenS,BlueS);

putpixel(6,6,RedA,GreenA,BlueA);
putpixel(6,7,RedA,GreenA,BlueA);
putpixel(6,8,RedM,GreenM,BlueM);
putpixel(6,9,RedS,GreenS,BlueS);
putpixel(6,10,RedS,GreenS,BlueS);
putpixel(6,11,RedS,GreenS,BlueS);
putpixel(6,12,RedS,GreenS,BlueS);
putpixel(6,13,RedS,GreenS,BlueS);

putpixel(10,6,RedA,GreenA,BlueA);
putpixel(10,7,RedA,GreenA,BlueA);
putpixel(10,8,RedM,GreenM,BlueM);
putpixel(10,9,RedS,GreenS,BlueS);
putpixel(10,10,RedS,GreenS,BlueS);
putpixel(10,11,RedS,GreenS,BlueS);
putpixel(10,12,RedS,GreenS,BlueS);
putpixel(10,13,RedS,GreenS,BlueS);

putpixel(5,6,RedM,GreenM,BlueM);
putpixel(5,7,RedM,GreenM,BlueM);
putpixel(5,9,RedM,GreenM,BlueM);
putpixel(5,10,RedM,GreenM,BlueM);
putpixel(5,11,RedM,GreenM,BlueM);
putpixel(5,12,RedM,GreenM,BlueM);
putpixel(5,13,RedM,GreenM,BlueM);
putpixel(5,14,RedM,GreenM,BlueM);

putpixel(11,6,RedM,GreenM,BlueM);
putpixel(11,7,RedM,GreenM,BlueM);
putpixel(11,9,RedM,GreenM,BlueM);
putpixel(11,10,RedM,GreenM,BlueM);
putpixel(11,11,RedM,GreenM,BlueM);
putpixel(11,12,RedM,GreenM,BlueM);
putpixel(11,13,RedM,GreenM,BlueM);
putpixel(11,14,RedM,GreenM,BlueM);

putpixel(4,6,RedM,GreenM,BlueM);
putpixel(4,10,RedM,GreenM,BlueM);
putpixel(4,11,RedM,GreenM,BlueM);
putpixel(4,12,RedM,GreenM,BlueM);
putpixel(4,13,RedM,GreenM,BlueM);
putpixel(4,14,RedM,GreenM,BlueM);
putpixel(4,15,RedM,GreenM,BlueM);
putpixel(4,16,RedM,GreenM,BlueM);
putpixel(4,17,RedM,GreenM,BlueM);
putpixel(4,18,RedM,GreenM,BlueM);
putpixel(4,19,RedM,GreenM,BlueM);

putpixel(12,6,RedM,GreenM,BlueM);
putpixel(12,10,RedM,GreenM,BlueM);
putpixel(12,11,RedM,GreenM,BlueM);
putpixel(12,12,RedM,GreenM,BlueM);
putpixel(12,13,RedM,GreenM,BlueM);
putpixel(12,14,RedM,GreenM,BlueM);
putpixel(12,15,RedM,GreenM,BlueM);
putpixel(12,16,RedM,GreenM,BlueM);
putpixel(12,17,RedM,GreenM,BlueM);
putpixel(12,18,RedM,GreenM,BlueM);
putpixel(12,19,RedM,GreenM,BlueM);

putpixel(3,20,RedM,GreenM,BlueM);
putpixel(3,10,RedM,GreenM,BlueM);
putpixel(3,11,RedM,GreenM,BlueM);
putpixel(3,12,RedM,GreenM,BlueM);
putpixel(3,13,RedA,GreenA,BlueA);
putpixel(3,14,RedA,GreenA,BlueA);
putpixel(3,15,RedM,GreenM,BlueM);
putpixel(3,16,RedA,GreenA,BlueA);
putpixel(3,17,RedA,GreenA,BlueA);
putpixel(3,18,RedM,GreenM,BlueM);
putpixel(3,19,RedM,GreenM,BlueM);

putpixel(13,20,RedM,GreenM,BlueM);
putpixel(13,10,RedM,GreenM,BlueM);
putpixel(13,11,RedM,GreenM,BlueM);
putpixel(13,12,RedM,GreenM,BlueM);
putpixel(13,13,RedA,GreenA,BlueA);
putpixel(13,14,RedA,GreenA,BlueA);
putpixel(13,15,RedM,GreenM,BlueM);
putpixel(13,16,RedA,GreenA,BlueA);
putpixel(13,17,RedA,GreenA,BlueA);
putpixel(13,18,RedM,GreenM,BlueM);
putpixel(13,19,RedM,GreenM,BlueM);

putpixel(2,20,RedM,GreenM,BlueM);
putpixel(2,11,RedM,GreenM,BlueM);
putpixel(2,12,RedM,GreenM,BlueM);
putpixel(2,13,RedM,GreenM,BlueM);
putpixel(2,14,RedM,GreenM,BlueM);
putpixel(2,15,RedA,GreenA,BlueA);
putpixel(2,16,RedA,GreenA,BlueA);
putpixel(2,17,RedA,GreenA,BlueA);
putpixel(2,18,RedM,GreenM,BlueM);
putpixel(2,19,RedM,GreenM,BlueM);

putpixel(14,20,RedM,GreenM,BlueM);
putpixel(14,11,RedM,GreenM,BlueM);
putpixel(14,12,RedM,GreenM,BlueM);
putpixel(14,13,RedM,GreenM,BlueM);
putpixel(14,14,RedM,GreenM,BlueM);
putpixel(14,15,RedA,GreenA,BlueA);
putpixel(14,16,RedA,GreenA,BlueA);
putpixel(14,17,RedA,GreenA,BlueA);
putpixel(14,18,RedM,GreenM,BlueM);
putpixel(14,19,RedM,GreenM,BlueM);

putpixel(1,11,RedM,GreenM,BlueM);
putpixel(1,14,RedM,GreenM,BlueM);
putpixel(1,15,RedM,GreenM,BlueM);
putpixel(1,16,RedM,GreenM,BlueM);
putpixel(1,17,RedM,GreenM,BlueM);
putpixel(1,18,RedM,GreenM,BlueM);
putpixel(1,19,RedM,GreenM,BlueM);

putpixel(15,11,RedM,GreenM,BlueM);
putpixel(15,14,RedM,GreenM,BlueM);
putpixel(15,15,RedM,GreenM,BlueM);
putpixel(15,16,RedM,GreenM,BlueM);
putpixel(15,17,RedM,GreenM,BlueM);
putpixel(15,18,RedM,GreenM,BlueM);
putpixel(15,19,RedM,GreenM,BlueM);

Size=imagesize(0,0,20,20);
B=farmalloc(Size);
getimage(0,0,20,20,B);
cleardevice();

//Green Bug With Closed Wings


putpixel(7,4,RedM,GreenM,BlueM);
putpixel(7,5,RedM,GreenM,BlueM);
putpixel(7,6,RedA,GreenA,BlueA);
putpixel(7,7,RedA,GreenA,BlueA);
putpixel(7,8,RedM,GreenM,BlueM);
putpixel(7,9,RedM,GreenM,BlueM);
putpixel(7,10,RedS,GreenS,BlueS);
putpixel(7,11,RedS,GreenS,BlueS);
putpixel(7,12,RedS,GreenS,BlueS);
putpixel(7,13,RedS,GreenS,BlueS);
putpixel(7,14,RedA,GreenA,BlueA);
putpixel(7,15,RedA,GreenA,BlueA);
putpixel(7,18,RedM,GreenM,BlueM);
putpixel(7,19,RedM,GreenM,BlueM);


putpixel(9,4,RedM,GreenM,BlueM);
putpixel(9,5,RedM,GreenM,BlueM);
putpixel(9,6,RedA,GreenA,BlueA);
putpixel(9,7,RedA,GreenA,BlueA);
putpixel(9,8,RedM,GreenM,BlueM);
putpixel(9,9,RedM,GreenM,BlueM);
putpixel(9,10,RedS,GreenS,BlueS);
putpixel(9,11,RedS,GreenS,BlueS);
putpixel(9,12,RedS,GreenS,BlueS);
putpixel(9,13,RedS,GreenS,BlueS);
putpixel(9,14,RedA,GreenA,BlueA);
putpixel(9,15,RedA,GreenA,BlueA);
putpixel(9,18,RedM,GreenM,BlueM);
putpixel(9,19,RedM,GreenM,BlueM);


putpixel(8,5,RedM,GreenM,BlueM);
putpixel(8,6,RedM,GreenM,BlueM);
putpixel(8,7,RedM,GreenM,BlueM);
putpixel(8,8,RedM,GreenM,BlueM);
putpixel(8,9,RedS,GreenS,BlueS);
putpixel(8,10,RedS,GreenS,BlueS);
putpixel(8,11,RedS,GreenS,BlueS);
putpixel(8,12,RedS,GreenS,BlueS);

putpixel(6,6,RedA,GreenA,BlueA);
putpixel(6,7,RedA,GreenA,BlueA);
putpixel(6,8,RedM,GreenM,BlueM);
putpixel(6,9,RedS,GreenS,BlueS);
putpixel(6,10,RedS,GreenS,BlueS);
putpixel(6,11,RedS,GreenS,BlueS);
putpixel(6,12,RedS,GreenS,BlueS);
putpixel(6,13,RedS,GreenS,BlueS);
putpixel(6,17,RedM,GreenM,BlueM);
putpixel(6,18,RedM,GreenM,BlueM);

putpixel(10,6,RedA,GreenA,BlueA);
putpixel(10,7,RedA,GreenA,BlueA);
putpixel(10,8,RedM,GreenM,BlueM);
putpixel(10,9,RedS,GreenS,BlueS);
putpixel(10,10,RedS,GreenS,BlueS);
putpixel(10,11,RedS,GreenS,BlueS);
putpixel(10,12,RedS,GreenS,BlueS);
putpixel(10,13,RedS,GreenS,BlueS);
putpixel(10,17,RedM,GreenM,BlueM);
putpixel(10,18,RedM,GreenM,BlueM);

putpixel(5,6,RedM,GreenM,BlueM);
putpixel(5,7,RedM,GreenM,BlueM);
putpixel(5,9,RedM,GreenM,BlueM);
putpixel(5,10,RedM,GreenM,BlueM);
putpixel(5,11,RedM,GreenM,BlueM);
putpixel(5,15,RedM,GreenM,BlueM);
putpixel(5,16,RedM,GreenM,BlueM);
putpixel(5,17,RedM,GreenM,BlueM);

putpixel(11,6,RedM,GreenM,BlueM);
putpixel(11,7,RedM,GreenM,BlueM);
putpixel(11,9,RedM,GreenM,BlueM);
putpixel(11,10,RedM,GreenM,BlueM);
putpixel(11,11,RedM,GreenM,BlueM);
putpixel(11,15,RedM,GreenM,BlueM);
putpixel(11,16,RedM,GreenM,BlueM);
putpixel(11,17,RedM,GreenM,BlueM);

putpixel(4,6,RedM,GreenM,BlueM);
putpixel(4,10,RedM,GreenM,BlueM);
putpixel(4,11,RedM,GreenM,BlueM);
putpixel(4,12,RedM,GreenM,BlueM);
putpixel(4,13,RedM,GreenM,BlueM);
putpixel(4,14,RedM,GreenM,BlueM);
putpixel(4,15,RedM,GreenM,BlueM);
putpixel(4,16,RedM,GreenM,BlueM);

putpixel(12,6,RedM,GreenM,BlueM);
putpixel(12,10,RedM,GreenM,BlueM);
putpixel(12,11,RedM,GreenM,BlueM);
putpixel(12,12,RedM,GreenM,BlueM);
putpixel(12,13,RedM,GreenM,BlueM);
putpixel(12,14,RedM,GreenM,BlueM);
putpixel(12,15,RedM,GreenM,BlueM);
putpixel(12,16,RedM,GreenM,BlueM);

putpixel(3,10,RedM,GreenM,BlueM);
putpixel(3,11,RedM,GreenM,BlueM);
putpixel(3,12,RedM,GreenM,BlueM);
putpixel(3,13,RedM,GreenM,BlueM);
putpixel(3,14,RedM,GreenM,BlueM);
putpixel(3,15,RedM,GreenM,BlueM);

putpixel(13,10,RedM,GreenM,BlueM);
putpixel(13,11,RedM,GreenM,BlueM);
putpixel(13,12,RedM,GreenM,BlueM);
putpixel(13,13,RedM,GreenM,BlueM);
putpixel(13,14,RedM,GreenM,BlueM);
putpixel(13,15,RedM,GreenM,BlueM);

putpixel(2,11,RedM,GreenM,BlueM);
putpixel(2,12,RedM,GreenM,BlueM);

putpixel(14,11,RedM,GreenM,BlueM);
putpixel(14,12,RedM,GreenM,BlueM);

putpixel(1,11,RedM,GreenM,BlueM);

putpixel(15,11,RedM,GreenM,BlueM);

Size=imagesize(0,0,20,20);
D=farmalloc(Size);
getimage(0,0,20,20,D);
cleardevice();

 }
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
#include <stdio.h>

//Const Section

//Var Section

//Proto Section

void main()
{ clrscr();
struct find_t ffblk;
	int done;
	printf("Directory listing of *.cpp\n");
	done = _dos_findfirst("c:\\*.cpp",_A_NORMAL,&ffblk);
	while (!done)
	{
		printf("  %s\n", ffblk.name);
		done = _dos_findnext(&ffblk);
	}

	getch();

};

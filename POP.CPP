#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

double pop = .02;
double r = 1.2;
long iter = 0;

void main()
{
 clrscr();
 do
 {
	iter++;
	pop = r*pop*(1-pop);
	cout << "Year #" << iter << ": " << pop << endl;
	getch();
 } while (iter < 400);
}



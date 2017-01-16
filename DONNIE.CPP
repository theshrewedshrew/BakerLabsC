#include <iostream.h>
#include <conio.h>

long start, end, index, sixty, delta, minutes;
double total = 0;

void main()
{
	clrscr();
	cout << "Start: ";
	cin >> start;
	cout << "End: ";
	cin >> end;

	if(start > end) end += 2400;

	sixty = (((int)(start/100))*100)+60-start;

	for(minutes = 0, delta = 0, index = start; index < end; index++, delta++, minutes++)
	{
		if(delta == sixty)
		{
			delta = 0;
			index += 40;
			sixty = 60;
		}

		total += (index >= 800 && index < 1800) ? 0.25 : 0.18;
	}

	cout << endl << "Minutes: " << minutes << endl;
	cout << "Total: $" << total;

	getch();
}


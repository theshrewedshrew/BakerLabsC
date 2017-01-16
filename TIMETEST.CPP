// Program: Fibonacci
// By: Bryan J. Baker

#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>
#include <time.h>
#include <dos.h>


dosdate_t d;
bool cont();
dostime_t T;
void main()
{ clrscr();


 do
 {gotoxy(5,10);
	//T = time(NULL);

//		cout<<T<<endl;
		//cout<ctime(&T).c_str()<<endl;
		_dos_gettime(&T);
//		printf("Current date is %s", ctime(&T));
cout<<"Time is:"<<double(T.hour)-12<<":"<<double(T.minute)<<":"<<int(T.second)<<":"<<int(T.hsecond);

_dos_getdate(&d);
cout<<endl<<int(d.month)<<"/"<<int(d.day)<<"/"<<d.year<<endl;
 }
 while (!kbhit());
 //cont());
} // End of Main

bool cont()
{ char Answer;
	bool Value;
	cout << endl << "Do you want to run the program again? (Y/N):";
	Answer = getche();
	cout<<endl;
	if (Answer == 'Y' || Answer == 'y')
		Value=true;
	else
		Value=false;

	return !Value;
}

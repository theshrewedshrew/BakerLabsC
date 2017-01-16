// Program: Fibonacci
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <apmatrix.h>
#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

bool cont();
int Day;
long I;
void main()
{
 do
 {

	 for (Day =1; Day <13; Day++)
	 { clrscr();
			cout<<"On the ";
			switch(Day)
			{	case 1 : cout <<"first ";
								 break;
				case 2 : cout <<"second ";
								 break;
				case 3 : cout <<"third ";
								 break;
				case 4 : cout <<"fourth ";
								 break;
				case 5 : cout <<"fifth ";
								 break;
				case 6 : cout <<"sixth ";
								 break;
				case 7 : cout <<"seventh ";
								 break;
				case 8 : cout <<"eighth ";
								 break;
				case 9 : cout <<"nineth";
								 break;
				case 10 : cout <<"tenth ";
								 break;
				case 11 : cout <<"eleventh ";
								 break;
				case 12 : cout <<"twelveth ";
								 break;
			 }
			 cout<<"day of Christmas my true love gave to me:"<<endl;

			 switch(Day)
			 { 	case 12: cout<<"Twelve drummers drumming,"<<endl;
					case 11: cout<<"Eleven pipers piping,"<<endl;
					case 10: cout<<"Ten lords-a-leaping,"<<endl;
					case 9: cout<<"Nine ladies waiting,"<<endl;
					case 8: cout<<"Eight maids a-milking,"<<endl;
					case 7: cout<<"Seven swans a-swimming,"<<endl;
					case 6: cout<<"Six geese a-laying,"<<endl;
					case 5: cout<<"Five gold rings,"<<endl;
					case 4: cout<<"Four calling birds,"<<endl;
					case 3: cout<<"Three French hens,"<<endl;
					case 2: cout<<"Two turtledoves,"<<endl;
					case 1: if(Day!=1)
										cout<<"and";
								 cout<<" a partridge in a pair tree."<<endl;
				}

				for(I=0;I<10000000;I++);
	 }




 }
 while (cont());
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

	return Value;
}

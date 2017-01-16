//Cooper Crowell
//5
//Mr. Baker
//Program:

#include <iostream.h>
#include <conio.h>
#include <apstring.h>
#include <iomanip.h>
#include <apmatrix.h>
//constants







//variables
apmatrix <int> Numbers(10,2);
int LCV1;
int LCV2;





void main()
{


//cout<< "Please enter the numbers." << endl;

for(LCV1 = 0; LCV1<10; LCV1++){
	for(LCV2 = 0; LCV2<2; LCV2++){
		cin >> Numbers[LCV1][LCV2];

	}
}



for(LCV1 = 0; LCV1<10; LCV1++){
	for(LCV2 = 0; LCV2<2; LCV2++){
		cout << Numbers[LCV1][LCV2];

	}
}


getch();


};

#include <iostream.h>

int foo ();


int main()
{
    int result;

		 result = foo();//  result always equals 0 if input value is 
									//   not a digit
		 cout<<result;
		 result = foo(); // return value is always 999 if first input 
									 // was not a digit
		 cout<<endl;
		 cout<<result;
		 return 0;
    
}

int foo ()
{
		 int a = 999;

		 do		 // this loop is not  entered in second call
		 {		 // to this function if in first call the value entered 
		 		 // was a non-digit

		 		 cout << "please enter a value from 0 to 9";
		 		 cin >> a;		 // value of a is always 0 if input value 
		 		 		 		 		 // is not a digit
		 }while (a<0 || a>9);
		 return a;

}
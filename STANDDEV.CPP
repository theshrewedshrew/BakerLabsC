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

void main()
{ clrscr();
 do
 {
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

double ppnd7 (double P, int & Ifault)
{
	double A[7], C[6], E[6];
	double Z, O, H, S1, S2, C1, C2, Q, R;
	double Ans;
	Z=0.0;
	O=1.0;
	H=0.5;
	S1= 0.425;
	S2= 5.0;
	C1=0.180625;
	C2=1.6;
	Ans=0.0;

	A[0] = 3.3871327179E+00;
	A[1] = 5.0434271938E+01;
	A[2] = 1.5929113292e+02;
	A[3] = 5.9109374720e+01;
	A[4] = 1.7895169469e+01;//B1
	A[5] = 7.8757757664e+01;//B2
	A[6] = 6.7187563600e+01;//B3
// Sum is 32.3184577772

	C[0] = 1.4234372777e+00;
	C[1] = 2.7568153900e+00;
	C[2] = 1.3067284816e+00;
	C[3] = 1.7023821103e+01;
	C[4] = 7.3700164250e-01;//D1
	C[5] = 1.2021132975e-01;//D2
// Sum is 15.7614929821

	E[0] = 6.6579051150e+00;
	E[1] = 3.0812263860e+00;
	E[2] = 4.2868294337e-01;
	E[3] = 1.7337203997e-02;
	E[4] = 2.4197894225e-01;//E1
	E[5] = 1.2258202635e-02;//E2
// Sum is 19.4052910204

Ifault = 0;
Q=P-H;
if(abs(Q)<=S1)
	{	R= C1 - (Q*Q);
		return double(Q*(((A[3]*R+A[2])*R+A[1])*R+A[0])/(((A[6]*R+A[5])*R+A[4])*R+O));
	}
else
	{
	 if(Q<Z)
		 R=P;
	 else
		 R=O-P;
	 if(R<=Z)
		{	Ifault = 1;
			return Z;
		}
	 R= sqrt(-log(R));
	 if(R<=S2)
		{ R=R-C2;
			return (((C[3]*R+C[2])*R+C[1])*R+C[0])/((D[2]*R+D[1])*R+O);
		}
	 else
		{

		}



	}




	return Ans;
}




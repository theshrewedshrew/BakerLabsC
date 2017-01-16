
/*
  ============================================================================
		Performance Systems II
		Programmed by: Robert James Deadman
		Designed by: Robert James Deadman
		Property of Trading Systems Analysis Group
		Copyright (C) 2000, 2001, 2003  Trading Systems Analysis Group
  ============================================================================
*/

/*
	Project Notes...  Things To Do Before Release

	Initialize ALL variables to 0 (zero)

	Change Detrended EMA System (S26) base code from the Var1-4 to the Var1-7
		setup before publishing manual or help

	Replace BPBP2 (S11) LR Slope with S17 Clope Calculation

	Check All Firstvalids

	Make sure all necessary indicators are included in outputs

	Fix s27 and s28 so that the Parabolic SAR works and then finish systems
	Talk to Jon Debry about getting this working.

	Make system 30 since it depends on the SAR in 28

	System 31, 32, and 33 still need to be encoded. DMI not matching MetaStock
	(DMI in New Technical Trader (Chande/Kroll))
	Talk to Jon Debry about getting this working.

	System 34 needs to have var1 and var3 updated corectly in the documentation

	Check for all minimum calculation sizes

	Make sure no formulas risk a divide by zero error

	Check all minimum periods tests and make sure they're accurate and returning 2 if fail

	System 48 MESA Sine Wave needs to be encoded. Not started yet.

	Make sure all indicators have firstvalids set properly

	System 51 (New RVI) is not a true new RVI (Used 14-period EMA instead if 14-period smoothing).
	This needs to be in the manual.

	Redo ALL calloc arrays with global calloc arrays at beginning of program. Use them in
	functions and subfunctions, and clean them out with "bzero" at the end of each use. If not in
	Visual C++ use below:
				#include <string.h>
				#define bcopy(b1,b2,len) memmove(b2, b1, (size_t)(len))		// copy array
				#define bzero(b,len) memset(b, 0, (size_t)(len))			// clear out array
				#define bcmp(b1,b2,len) memcmp(b1, b2, (size_t)(len))		// compare arrays

	System 74 and 75 (Relative Volatility Index) are made to match Equis' indicator which is a
	true New RVI, not a true RVI. Make note in manual.


	Remove the 'EmptyFunc' default function and all of its components.

	Make a function that Detects the presence of open, high, and low prices, and if absent,
		makes the Close the High, Low, or Open price.



*/


#include <windows.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
//#include "mycustom.h"
#include "psiitest.h" //Test breaking up Program

// TODO: Make sure this include is in your search path or added explicitly to the project.
#include "MSXStruc.h"  // required definitions

// we don't want C++ name-mangling
#ifdef __cplusplus
extern "C" {
#endif

#define OR ||
#define AND &&

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)



//	*******************************
//	System Test Function Prototypes
//	*******************************
// All of the system tests use the exact same structure for its input and output.

int s1(struct datasys *x);									// 10-Day Breakout
int s2(struct datasys *x);									// 2-Day Range Switch
int s3(struct datasys *x);									// 3-Day Range Switch
int s4(struct datasys *x);									// 4-Day Range Switch
int s5(struct datasys *x);									// Adaptive Moving Average
int s6(struct datasys *x);									// Annual Strength/Weakness 1
int s7(struct datasys *x);									// Annual Strength/Weakness 2
int s8(struct datasys *x);									// Aroon
int s9(struct datasys *x);									// Aroon Reversal
int s10(struct datasys *x);									// Bull Power Bear Power 1
int s11(struct datasys *x);									// Bull Power Bear Power 2
int s12(struct datasys *x);									// Bull Power Bear Power 3
int s13(struct datasys *x);									// Bull Power Bear Power 4
int s14(struct datasys *x);									// CCI (Commodity Channel Index)
int s15(struct datasys *x);									// CCI Fibonacci
int s16(struct datasys *x);									// CCI Moving Average Crossover
int s17(struct datasys *x);									// Chande Forecast Oscillator
int s18(struct datasys *x);									// CMO Reinforcement
int s19(struct datasys *x);									// CMO Reversal
int s20(struct datasys *x);									// Congestion Breakout
int s21(struct datasys *x);									// Consolidation Breakout
int s22(struct datasys *x);									// Cooper 1234 Pattern
int s23(struct datasys *x);									// Cycle Progression
int s24(struct datasys *x);									// Day Pattern System
int s25(struct datasys *x);									// Derivative Moving Average
int s26(struct datasys *x);									// Detrended EMA System
int s27(struct datasys *x);									// Directional Movement/SAR 1		***
int s28(struct datasys *x);									// Directional Movement/SAR 2		***
int s29(struct datasys *x);									// Division System
int s30(struct datasys *x);									// DNS Trading System				***
int s31(struct datasys *x);									// Dynamic Momentum Index 1			***
int s32(struct datasys *x);									// Dynamic Momentum Index 2			***
int s33(struct datasys *x);									// Dynamic Momentum Index 3			***
int s34(struct datasys *x);									// Elliott Oscillator System 1
int s35(struct datasys *x);									// Elliott Oscillator System 2
int s36(struct datasys *x);									// Exponential Moving Average
int s37(struct datasys *x);									// Fractal Trading System 1
int s38(struct datasys *x);									// Fractal Trading System 2
int s39(struct datasys *x);									// Fractal Trading System 3
int s40(struct datasys *x);									// Impulse Meter
int s41(struct datasys *x);									// Intraday Momentum Index
int s42(struct datasys *x);									// Landis Reversal
int s43(struct datasys *x);									// Linear Regression Crossover
int s44(struct datasys *x);									// Long Sell Short Sale - 5 Day
int s45(struct datasys *x);									// MACD Histogram 1
int s46(struct datasys *x);									// MACD Histogram 2
int s47(struct datasys *x);									// Meisels Overbought/Oversold
int s48(struct datasys *x);									// MESA Sine Wave					***
int s49(struct datasys *x);									// Modified Momentum
int s50(struct datasys *x);									// Momentum
int s51(struct datasys *x);									// New Relative Volatility Index
int s52(struct datasys *x);									// Oscillator Composite
int s53(struct datasys *x);									// Pattern Trading System 1
int s54(struct datasys *x);									// Pattern Trading System 2
int s55(struct datasys *x);									// Pattern Trading System 3
int s56(struct datasys *x);									// Pattern Trading System 4
int s57(struct datasys *x);									// Pattern Trading System 5
int s58(struct datasys *x);									// Pattern Trading System 6
int s59(struct datasys *x);									// Percentage Crossover 1%
int s60(struct datasys *x);									// Percentage Crossover 2%
int s61(struct datasys *x);									// Percentage Crossover 3%
int s62(struct datasys *x);									// Percentage Crossover 4%
int s63(struct datasys *x);									// Percentage Crossover 5%
int s64(struct datasys *x);									// Percentage Crossover 6%
int s65(struct datasys *x);									// Percentage Crossover 7%
int s66(struct datasys *x);									// Percentage Crossover 8%
int s67(struct datasys *x);									// Percentage Crossover 9%
int s68(struct datasys *x);									// Percentage Crossover 10%
int s69(struct datasys *x);									// Percentage Crossover 20%
int s70(struct datasys *x);									// Polarized Fractal Efficiency
int s71(struct datasys *x);									// Projection Oscillator 1
int s72(struct datasys *x);									// Projection Oscillator 2
int s73(struct datasys *x);									// Relative Momentum Index
int s74(struct datasys *x);									// Relative Volatility Index 1
int s75(struct datasys *x);									// Relative Volatility Index 2
int s76(struct datasys *x);									// RSI Trailing Exit
int s77(struct datasys *x);									// Short Term Range Rejection
int s78(struct datasys *x);									// Small Triangle Breakout
int s79(struct datasys *x);									// StarcBand System
int s80(struct datasys *x);									// Stochastic Oscillator System
int s81(struct datasys *x);									// StochRSI
int s82(struct datasys *x);									// Swing Index
int s83(struct datasys *x);									// Turtle Breakout 1
int s84(struct datasys *x);									// Turtle Breakout 2
int s85(struct datasys *x);									// Ultimate Oscillator
int s86(struct datasys *x);									// Vertical Horizontal Filter
int s87(struct datasys *x);									// Volatility Breakout (Chaikin)
int s88(struct datasys *x);									// Volatility Breakout (Standard)
int s89(struct datasys *x);									// Volatility Stop
int s90(struct datasys *x);									// Volume Trading System



//	*******************************
//	Maintenance Function Prototypes
//	*******************************

void maint_signal_cleanup (struct datasys *x, int type);
															// Signal Cleaning Function





/*
The "datasys" structure is designed to provide a uniform structure for inputs to a system
test as well as outputs from a system test. It is designed so that a translator can be made
when necessary for all of the basic information to pass through to a system test (price information)
and it provides array pointers for information that the system test places in the structure.

*/
struct datasys
{
															// *** Beginning of data supplied by MetaStock ***

	float	*open;											// Opening Prices Array
	float	*high;											// High Prices Array
	float	*low;											// Low Prices Array
	float	*close;											// Closing Prices Array
	float	*volume;										// Trade Volume Array
	float	*oi;											// Open Interest Array

	MSXDateTime	*date;										// Date Array to align with Price Data

	int		firstvalid;										// The first location of data in any price array
															//	(based on the Closing Price Array)
	int		lastvalid;										// The last location of data in any price array
															//	(based on the Closing Price Array)
	double	eValue1;										// A parameter passed into the DLL from MetaStock
	double	eValue2;										// A parameter passed into the DLL from MetaStock

															// *** End of data supplied by MetaStock ***

															// *** Beginning of data supplied by System ***
															// ***  test functions						***

															// The following pointers are for variables and arrays
															//  that the system test functions put their results in.
															//	All destination arrays below have an allocated size
															//	of 65500 cells available. This is the maximum number
															//	of any price type (open, high, low, close, etc.) that
															//	Metastock can have, and therefore is the maximum
															//	number of cells in the assignment.

															// The following 'int' arrays, after being put through
															//	a function, should only contain a 1 or a 0. 1 if
															//	a signal was generated for that day, and a 0 (zero)
															//	if not. (Binary array)

	int		*el;											// Enter Long Position signal array
	int		*cl;											// Close Long Position signal array
	int		*es;											// Enter Short Position signal array
	int		*cs;											// Close Short Position signal array

															// The following 'float' arrays are for indicators
															//	that the System Test uses. The indicators are
															//	placed in these locations so that they can be passed
															//	back to MetaStock for a user to plot (to verify
															//	what the system is doing). There are a maximum of
															//	five indicators available to return to the user.
															//	These indicators are different from system to system.
	
	float	*ind1;											// First Indicator Array
	float	*ind2;											// Second Indicator Array
	float	*ind3;											// Third Indicator Array
	float	*ind4;											// Fourth Indicator Array
	float	*ind5;											// Fifth Indicator Array

															// The following pointers are for variables, NOT arrays.
															//	They are the locations in the arrays of the beginning
															//	of the output arrays. They equate to the FirstValid
															//	(location) of the output arrays.

	int		*elIsValid;										// Enter Long binary array FirstValid location
	int		*clIsValid;										// Close Long binary array FirstValid location
	int		*esIsValid;										// Enter Short binary array FirstValid location
	int		*csIsValid;										// Close Short binary array FirstValid location

	int		*ind1FirstValid;								// First Indicator Array FirstValid location
	int		*ind2FirstValid;								// Second Indicator Array FirstValid location
	int		*ind3FirstValid;								// Third Indicator Array FirstValid location
	int		*ind4FirstValid;								// Fourth Indicator Array FirstValid location
	int		*ind5FirstValid;								// Fifth Indicator Array FirstValid location

	int		*state;											// System Trading State (1=Long, -1=Short, 0=Out of Trade)
};


//	****************
//	Function 'flint'
//	****************
// This function converts a floating point value to an integer value by dropping
//	all remaining values after the decimal point, and then returns the result as
//	a 'float' instead of an 'int'.
float	flint (float i)										// Convert a float to an int and return a float
{int a;	a=(int) i; return (float)a;}


//	****************
//	Function 'round'
//	****************
// This function rounds a floating point value to the closest integer value,
//	and then returns the result as a 'float' instead of an 'int'.
float round (float i)										// Round to nearest whole number and return float
{int a;	a=int(i+.5); return (float)a;}


//	****************************
//	Function 'dow' (Day Of Week)
//	****************************
// This function converts a date in the yyyymmdd format into a value of
//	0 to 6 for the day of the week that the date falls on and returns that number.
//	0=Sunday, 1=Monday,	2=Tuesday, 3=Wednesday, 4=Thursday, 5=Friday, 6=Saturday.
//	While the range of dates this function covers is not known, it does cover all
//	dates between 1900 and 2100 which is the maximum date range that MetaStock
//	can handle.
unsigned dow(unsigned long x)								// Calculate Day-Of-Week
{															// Pass long int as yyyymmdd,
	int y, m, d;											// and returns 0 to 6 (sunday to saturday)
	y=(int)x/10000;
	m=(int)(x%10000)/100;
	d=(int)x%100;

	if (m < 3)
	{ m += 13; y--;	}
	else  m++;
	return (d + 26 * m / 10 + y + y / 4 - y / 100 + y / 400 + 6) % 7;
}

//	***********************************************************
//	Set up array pointers for the systems to use in processing.
//	*********************************************************** 

float *floatarray1, *floatarray2, *floatarray3, *floatarray4, *floatarray5, *floatarray6;
float *floatarray7, *floatarray8, *floatarray9, *floatarray10, *floatarray11, *floatarray12;
float *floatarray13, *floatarray14, *floatarray15, *floatarray16;

int *intarray1, *intarray2, *intarray3, *intarray4;
int *intarray5, *intarray6, *intarray7, *intarray8;


// DLLMain
BOOL WINAPI DllMain( HANDLE a_hModule, 
                     DWORD  a_fdwReason, 
                     LPVOID a_lpReserved
				   )
{
    BOOL   l_bRtrn = TRUE;

	switch (a_fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Code placed here will execute when the DLL is first loaded by MetaStock (or MSXTest).
		// If your DLL requires initialization of global variables or other start-up
		//   processing, do that here.

		floatarray1 = (float *) calloc (65500,sizeof(float));
		if(floatarray1==NULL)
		{
//			strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - System");
			return MSX_ERROR;
		};

		floatarray2 = (float *) calloc (65500,sizeof(float));
		if(floatarray2==NULL)
		{
			free(floatarray1);

			return MSX_ERROR;
		};

		floatarray3 = (float *) calloc (65500,sizeof(float));
		if(floatarray3==NULL)
		{
			free(floatarray1);
			free(floatarray2);

			return MSX_ERROR;
		};

		floatarray4 = (float *) calloc (65500,sizeof(float));
		if(floatarray4==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);

			return MSX_ERROR;
		};

		floatarray5 = (float *) calloc (65500,sizeof(float));
		if(floatarray5==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);

			return MSX_ERROR;
		};

		floatarray6 = (float *) calloc (65500,sizeof(float));
		if(floatarray6==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);

			return MSX_ERROR;
		};

		floatarray7 = (float *) calloc (65500,sizeof(float));
		if(floatarray7==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);

			return MSX_ERROR;
		};

		floatarray8 = (float *) calloc (65500,sizeof(float));
		if(floatarray8==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);

			return MSX_ERROR;
		};

		floatarray9 = (float *) calloc (65500,sizeof(float));
		if(floatarray9==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);

			return MSX_ERROR;
		};

		floatarray10 = (float *) calloc (65500,sizeof(float));
		if(floatarray10==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);

			return MSX_ERROR;
		};

		floatarray11 = (float *) calloc (65500,sizeof(float));
		if(floatarray11==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);

			return MSX_ERROR;
		};

		floatarray12 = (float *) calloc (65500,sizeof(float));
		if(floatarray12==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);

			return MSX_ERROR;
		};

		floatarray13 = (float *) calloc (65500,sizeof(float));
		if(floatarray13==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);

			return MSX_ERROR;
		};

		floatarray14 = (float *) calloc (65500,sizeof(float));
		if(floatarray14==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);

			return MSX_ERROR;
		};

		floatarray15 = (float *) calloc (65500,sizeof(float));
		if(floatarray15==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);

			return MSX_ERROR;
		};

		floatarray16 = (float *) calloc (65500,sizeof(float));
		if(floatarray16==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);

			return MSX_ERROR;
		};



		intarray1 = (int *) calloc (65500,sizeof(int));
		if(intarray1==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			return MSX_ERROR;
		};

		intarray2 = (int *) calloc (65500,sizeof(int));
		if(intarray2==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			free(intarray1);

			return MSX_ERROR;
		};

		intarray3 = (int *) calloc (65500,sizeof(int));
		if(intarray3==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			free(intarray1);
			free(intarray2);

			return MSX_ERROR;
		};

		intarray4 = (int *) calloc (65500,sizeof(int));
		if(intarray4==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			free(intarray1);
			free(intarray2);
			free(intarray3);

			return MSX_ERROR;
		};

		intarray5 = (int *) calloc (65500,sizeof(int));
		if(intarray5==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			free(intarray1);
			free(intarray2);
			free(intarray3);
			free(intarray4);

			return MSX_ERROR;
		};

		intarray6 = (int *) calloc (65500,sizeof(int));
		if(intarray6==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			free(intarray1);
			free(intarray2);
			free(intarray3);
			free(intarray4);
			free(intarray5);

			return MSX_ERROR;
		};

		intarray7 = (int *) calloc (65500,sizeof(int));
		if(intarray7==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			free(intarray1);
			free(intarray2);
			free(intarray3);
			free(intarray4);
			free(intarray5);
			free(intarray6);

			return MSX_ERROR;
		};

		intarray8 = (int *) calloc (65500,sizeof(int));
		if(intarray8==NULL)
		{
			free(floatarray1);
			free(floatarray2);
			free(floatarray3);
			free(floatarray4);
			free(floatarray5);
			free(floatarray6);
			free(floatarray7);
			free(floatarray8);
			free(floatarray9);
			free(floatarray10);
			free(floatarray11);
			free(floatarray12);
			free(floatarray13);
			free(floatarray14);
			free(floatarray15);
			free(floatarray16);

			free(intarray1);
			free(intarray2);
			free(intarray3);
			free(intarray4);
			free(intarray5);
			free(intarray6);
			free(intarray7);

			return MSX_ERROR;
		};
		break;


	case DLL_PROCESS_DETACH:
		// Code placed here will execute when the DLL is unloaded by MetaStock (or MSXTest).
		// If you allocated memory in DLL_PROCESS_ATTACH, deallocate it here.

		free(floatarray1);
		free(floatarray2);
		free(floatarray3);
		free(floatarray4);
		free(floatarray5);
		free(floatarray6);
		free(floatarray7);
		free(floatarray8);
		free(floatarray9);
		free(floatarray10);
		free(floatarray11);
		free(floatarray12);
		free(floatarray13);
		free(floatarray14);
		free(floatarray15);
		free(floatarray16);

		free(intarray1);
		free(intarray2);
		free(intarray3);
		free(intarray4);
		free(intarray5);
		free(intarray6);
		free(intarray7);
		free(intarray8);

		break;
	default:
		break;
	}

	return l_bRtrn;
}


// MSXInfo
BOOL __stdcall MSXInfo (MSXDLLDef *a_psDLLDef)
{
	// TODO: replace with your copyright information...
	strncpy (a_psDLLDef->szCopyright, "TSAGroup Systest1",
			sizeof(a_psDLLDef->szCopyright)-1);
	// TODO: set the number of functions you are exporting
	//       (don't forget to add them to your .def file)
	a_psDLLDef->iNFuncs = 2; // change this if you have more than 1 function to export.
	a_psDLLDef->iVersion = MSX_VERSION;
	return MSX_SUCCESS;
}


// MSXNthFunction
BOOL __stdcall MSXNthFunction (int a_iNthFunc, MSXFuncDef *a_psFuncDef)
{
	int l_bRtrn = MSX_SUCCESS; // no error

	switch (a_iNthFunc)
	{
	case 0:
		strcpy (a_psFuncDef->szFunctionName, "EmptyFunc");
		strcpy (a_psFuncDef->szFunctionDescription, "Empty Sample Function");
		a_psFuncDef->iNArguments = 0;
		break;
	case 1:
		strcpy (a_psFuncDef->szFunctionName, "Systest1");
		strcpy (a_psFuncDef->szFunctionDescription, "System Test 1");
		a_psFuncDef->iNArguments = 2;
		break;
	default:
		l_bRtrn = MSX_ERROR; // This will help MSXTest find errors in your code
		break;
	}
	return l_bRtrn;
}


// MSXNthArg
BOOL __stdcall MSXNthArg (int a_iNthFunc, int a_iNthArg,
                         MSXFuncArgDef *a_psFuncArgDef)
{
	BOOL l_bRtrn = MSX_SUCCESS;

	a_psFuncArgDef->iNCustomStrings = 0; // init just to be nice

   switch (a_iNthFunc)
   {
   case 1: // System Tester
     switch (a_iNthArg)
     {
     case 0: // System Number
       a_psFuncArgDef->iArgType = MSXNumeric; // System Number
       strcpy (a_psFuncArgDef->szArgName, "System #");
       break;
     case 1: // Enter Long, Close Long, Enter Short, Close Short
       a_psFuncArgDef->iArgType = MSXNumeric; // Data Array to Return
       strcpy (a_psFuncArgDef->szArgName, "1=EL, 2=CL, 3=ES, 4=CS");
       break;
     default:
       l_bRtrn = MSX_ERROR; // This will help MSXTest find errors in your code
       break;
     }
     break;
	 default:
		 l_bRtrn = MSX_ERROR; // This will help MSXTest find errors in your code
		 break;
   }
   return l_bRtrn;
}



// MSXNthCustomString
BOOL __stdcall MSXNthCustomString (int a_iNthFunc, int a_iNthArg,
                                   int a_iNthString,
                                   MSXFuncCustomString *a_psCustomString)
{
	BOOL l_bRtrn = MSX_SUCCESS;
	a_psCustomString->szString[0] = '\0';
	a_psCustomString->iID = -1;

	typedef struct
	{
	char *szString;
	int  iID;
	} LocalStringElement;

	// TODO:
	// Uncomment the following two lines and fill in with data similar to
	//   to the example shown in the comment block above this function.
  
	// LocalStringElement l_sStrings[] = 
	// {
	// };

	// TODO: If your functions require custom string arguments, uncomment the
	//       following switch statement and add the appropriate case statements.

	/*
	switch (a_iNthFunc)
	{
	// TODO: create case statements for each function and each custom string
	//       argument as shown in the commented example above.
	default:
		l_bRtrn = MSX_ERROR;
		break;
	}
	*/

	return l_bRtrn;
}

// ************************************************************************
// This local utility function is used to help ensure that no overflows
//   or underflows will occur during calcuations.  The MSXTest program
//   Stress Test function will call your DLL with a wide range of values,
//   including positive and negative values of FLT_MAX and FLT_MIN.
// Perform all intermediate calculations using doubles and then force the
//   results into the range of a float.
// Locally defined macros are used to avoid compiler definition differences.
// ************************************************************************
#define MSXMax(a,b) (((a) > (b)) ? (a) : (b))
#define MSXMin(a,b) (((a) < (b)) ? (a) : (b))
double ForceFloatRange (double a_lfDbl)
{
	if (a_lfDbl > 0.0)
	{
		a_lfDbl = MSXMin (a_lfDbl, double(FLT_MAX)); // make sure pos number <= FLT_MAX
		a_lfDbl = MSXMax (a_lfDbl, double(FLT_MIN)); // make sure pos number >= FLT_MIN
	}
	else
	{
		if (a_lfDbl < 0.0)
		{
			a_lfDbl = MSXMax (a_lfDbl, double(-FLT_MAX)); // make sure neg number >= -FLT_MAX
			a_lfDbl = MSXMin (a_lfDbl, double(-FLT_MIN)); // make sure neg number <= -FLT_MIN
		}
	}

	return a_lfDbl;
}




BOOL __stdcall EmptyFunc (const MSXDataRec *a_psDataRec,
                          const MSXDataInfoRecArgsArray *a_psDataInfoArgs,
                          const MSXNumericArgsArray *a_psNumericArgs,
                          const MSXStringArgsArray *a_psStringArgs,
                          const MSXCustomArgsArray *a_psCustomArgs,
                          MSXResultRec *a_psResultRec)
{
	BOOL l_bRtrn = MSX_SUCCESS;

	// in case you don't flesh this out before running it, we'll invalidate
	//   the return array to prevent potential problems.
	a_psResultRec->psResultArray->iFirstValid = 0;
	a_psResultRec->psResultArray->iLastValid = -1;

	// TODO:
	//  Add your function logic here
	//  Note: Be sure to add your function names to the "PSIITest.def" file.
	//    Without the DEF file entries, the DLL may compile without errors, but MSXTest
	//    and MetaStock will not be able to find or use your functions.

	return l_bRtrn;
}


BOOL __stdcall Systest1 (const MSXDataRec *a_psDataRec,
                          const MSXDataInfoRecArgsArray *a_psDataInfoArgs,
                          const MSXNumericArgsArray *a_psNumericArgs,
                          const MSXStringArgsArray *a_psStringArgs,
                          const MSXCustomArgsArray *a_psCustomArgs,
                          MSXResultRec *a_psResultRec)
{
	BOOL l_bRtrn = MSX_SUCCESS;

	a_psResultRec->psResultArray->iFirstValid = 0;
	a_psResultRec->psResultArray->iLastValid = -1;

	int *el, *cl, *es, *cs, *state, i;
	float *ind1, *ind2, *ind3, *ind4, *ind5;
	int elIsValid, clIsValid, esIsValid, csIsValid;
	int	ind1FirstValid, ind2FirstValid, ind3FirstValid, ind4FirstValid, ind5FirstValid;


	el = (int *) calloc (65500,sizeof(int));
	if(el==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - EL Signal");

		return MSX_ERROR;
	}

	cl = (int *) calloc (65500,sizeof(int));
	if(cl==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - CL Signal");
		free(el);

		return MSX_ERROR;
	}

	es = (int *) calloc (65500,sizeof(int));
	if(es==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - ES Signal");
		free(el);
		free(cl);

		return MSX_ERROR;
	}

	cs = (int *) calloc (65500,sizeof(int));
	if(cs==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - CS Signal");
		free(el);
		free(cl);
		free(es);

		return MSX_ERROR;
	}


	bzero(el,sizeof(int)*65500);
	bzero(cl,sizeof(int)*65500);
	bzero(es,sizeof(int)*65500);
	bzero(cs,sizeof(int)*65500);



	ind1 = (float *) calloc (65500,sizeof(float));
	if(ind1==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - Indicator 1");

		free(el);
		free(cl);
		free(es);
		free(cs);

		return MSX_ERROR;
	}

	ind2 = (float *) calloc (65500,sizeof(float));
	if(ind2==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - Indicator 2");
		free(el);
		free(cl);
		free(es);
		free(cs);
		free(ind1);

		return MSX_ERROR;
	}

	ind3 = (float *) calloc (65500,sizeof(float));
	if(ind3==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - Indicator 3");
		free(el);
		free(cl);
		free(es);
		free(cs);
		free(ind1);
		free(ind2);

		return MSX_ERROR;
	}

	ind4 = (float *) calloc (65500,sizeof(float));
	if(ind4==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - Indicator 4");
		free(el);
		free(cl);
		free(es);
		free(cs);
		free(ind1);
		free(ind2);
		free(ind3);

		return MSX_ERROR;
	}

	ind5 = (float *) calloc (65500,sizeof(float));
	if(ind5==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - Indicator 5");
		free(el);
		free(cl);
		free(es);
		free(cs);
		free(ind1);
		free(ind2);
		free(ind3);
		free(ind4);

		return MSX_ERROR;
	}


	state = (int *) calloc (65500,sizeof(int));
	if(state==NULL)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - State Indicator");
		free(el);
		free(cl);
		free(es);
		free(cs);
		free(ind1);
		free(ind2);
		free(ind3);
		free(ind4);
		free(ind5);

		return MSX_ERROR;
	}

	bzero(ind1,sizeof(float)*65500);
	bzero(ind2,sizeof(float)*65500);
	bzero(ind3,sizeof(float)*65500);
	bzero(ind4,sizeof(float)*65500);
	bzero(ind5,sizeof(float)*65500);


	struct datasys sys1;
	{
		sys1.open = a_psDataRec->sOpen.pfValue;
		sys1.high = a_psDataRec->sHigh.pfValue;
		sys1.low = a_psDataRec->sLow.pfValue;
		sys1.close = a_psDataRec->sClose.pfValue;
		sys1.volume = a_psDataRec->sVol.pfValue;
		sys1.oi = a_psDataRec->sOI.pfValue;

		sys1.firstvalid = a_psDataRec->sClose.iFirstValid;
		sys1.lastvalid = a_psDataRec->sClose.iLastValid;

		sys1.date = a_psDataRec->psDate;

		sys1.eValue1 = 0;
		sys1.eValue2 = 0;

		sys1.el = el;
		sys1.cl = cl;
		sys1.es = es;
		sys1.cs = cs;

		sys1.ind1 = ind1;
		sys1.ind2 = ind2;
		sys1.ind3 = ind3;
		sys1.ind4 = ind4;
		sys1.ind5 = ind5;

		sys1.elIsValid = &elIsValid;
		sys1.clIsValid = &clIsValid;
		sys1.esIsValid = &esIsValid;
		sys1.csIsValid = &csIsValid;

		sys1.ind1FirstValid = &ind1FirstValid;
		sys1.ind2FirstValid = &ind2FirstValid;
		sys1.ind3FirstValid = &ind3FirstValid;
		sys1.ind4FirstValid = &ind4FirstValid;
		sys1.ind5FirstValid = &ind5FirstValid;

		sys1.state = state;

	};

	if(s1(&sys1)==1)
	{
		strcpy (a_psResultRec->szExtendedError,"Not Enough Memory - System");
		return MSX_ERROR;
	};

	maint_signal_cleanup(&sys1, 3);

	a_psResultRec->psResultArray->iFirstValid=a_psDataRec->sClose.iFirstValid;
	a_psResultRec->psResultArray->iLastValid=a_psDataRec->sClose.iLastValid;

	for (i=a_psDataRec->sClose.iFirstValid; i<=a_psDataRec->sClose.iLastValid; i++)
	{
		if (a_psNumericArgs->fNumerics[1]==1)
			a_psResultRec->psResultArray->pfValue[i]= float (ForceFloatRange (sys1.el[i]));
		if (a_psNumericArgs->fNumerics[1]==2)
			a_psResultRec->psResultArray->pfValue[i]= float (ForceFloatRange (sys1.cl[i]));
		if (a_psNumericArgs->fNumerics[1]==3)
			a_psResultRec->psResultArray->pfValue[i]= float (ForceFloatRange (sys1.es[i]));
		if (a_psNumericArgs->fNumerics[1]==4)
			a_psResultRec->psResultArray->pfValue[i]= float (ForceFloatRange (sys1.cs[i]));
		if (a_psNumericArgs->fNumerics[1]==5)
			a_psResultRec->psResultArray->pfValue[i]= float (ForceFloatRange (sys1.state[i]));
	}

	if (a_psNumericArgs->fNumerics[1]==5)
		a_psResultRec->psResultArray->iFirstValid=*sys1.ind1FirstValid;

	free(el);
	free(cl);
	free(es);
	free(cs);

	free(ind1);
	free(ind2);
	free(ind3);
	free(ind4);
	free(ind5);

	free(state);

	return l_bRtrn;
}

#ifdef __cplusplus
}
#endif
/*


//	***************************
//	***** 10-Day Breakout *****
//	***************************
/*
This system looks for a breakout from a 10-day high or low. If a breakout
occurs, it enters in the direction of the breakout and then holds the position
until the first day that the direction changes (based upon the high or low
price, depending upon the direction), exiting on the close of the next trading
day.

Unlike other systems that wait to do a Market-On-Close order (MOC), this type
of system can be entered intraday As soon as a 10-day range has been
determined, a long and short order could be simultaneously placed. (Assuming
that you're trading a stock) If you determine that the low of the week is at a
price of 25 and that the high of the week is at a price of 30, you can then
place a stop order to enter short at 24 7/8 and a stop order to enter long at
30 1/8. If the position were entered that day, then the next day an MOC order
would be placed to exit the position if the previous day's high or low had not
been exceeded. This would allow you to analyze a setup and place your orders
ahead of time for an optimal entry point.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 10-Period Highest High Value of Highs 
	Ind2 = 10-Period Lowest Low Value of Lows

MetaStock Code:
	EL:=H>Ref(HHV(H,10),-1);
	CL:=Ref(H>Ref(HHV(H,10),-1),-1);
	ES:=L<Ref(LLV(L,10),-1);
	CS:=Ref(L<Ref(LLV(L,10),-1),-1);

int s1(struct datasys *x)									// 10-Day Breakout
{
	int i=0, j=0;
	float hhv=0, llv=0;
	float *hhv10, *llv10;

	hhv10=floatarray1;										// 10-Period Highest High Value of Highs
	llv10=floatarray2;										// 10-Period Lowest Low Value of Lows


	if((x->lastvalid - x->firstvalid)<11) return 2;			// Return 2 if not enough data
															//	to calculate.
	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 10-day levels.
		for (j=i-8; j<=i; j++)
		{
			if (j==i-8)
			{
				hhv=x->high[j-1];
				llv=x->low[j-1];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv10[i]=hhv;
		llv10[i]=llv;
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+10; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(x->high[i]>hhv10[i-1])
			x->el[i]=1;

		if(x->low[i]<llv10[i-1]) 
			x->es[i]=1;

		if(x->high[i-1]>hhv10[i-2] AND i!=(x->firstvalid+10)
			AND x->high[i]<=hhv10[i-1])
			x->cl[i]=1;

		if(x->low[i-1]<llv10[i-2] AND i!=(x->firstvalid+10)
			AND x->low[i]>=llv10[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, hhv10, sizeof(float)*65500);			// Ind1 = 10-Period Highest High Value of Highs
	memcpy (x->ind2, llv10, sizeof(float)*65500);			// Ind2 = 10-Period Lowest Low Value of Lows

	*(x->elIsValid) = x->firstvalid+10;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+10;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+10;
	*(x->csIsValid) = x->firstvalid+10;
	*(x->ind1FirstValid) = x->firstvalid+9;
	*(x->ind2FirstValid) = x->firstvalid+9;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}

*/


//	******************************
//	***** 2-Day Range Switch *****
//	******************************
/*
This system is based on defining a trend as prices that continually move away
from a maximum low/high point of the most recent 2 bars. Once the lowest point
of 2 bars is calculated, the system will stay in a long position until that
point is crossed. That point is continually moving up, acting as a trailing
stop. Once a crossing occurs, the system takes a short position and the highest
point of the last 2 days is calculated and follows the position down as a
trailing stop.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 2-Day Range Switch Indicator (d)

MetaStock Code:
	d:=If(C>Ref(Max(H,Ref(H,-1)),-1),Min(L,Ref(L,-1)),
		If(C<Ref(Min(L,Ref(L,-1)),-1),Max(H,Ref(H,-1)),PREV));

	EL:=Cross(C,d)
	ES:=Cross(d,C)
*/
int s2(struct datasys *x)									// 2-Day Range Switch
{
	int i=0;
	float *d;

	d=floatarray1;											// 2-Day Range Switch Indicator


	if((x->lastvalid - (x->firstvalid))<4) return 2;		// Return 2 if not enough data
															//	to calculate.

	for (i=x->firstvalid+3; i<=x->lastvalid; i++)			// Create 2-Day Range Switch
	{														//	indicator.
		if(x->close[i]>__max(x->high[i-1],x->high[i-2]))
			d[i] = __min(x->low[i],x->low[i-1]);
		else if(x->close[i]<__min(x->low[i-1],x->low[i-2]))
			d[i] = __max(x->high[i],x->high[i-1]);
		else d[i]=d[i-1];
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+3; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(x->close[i]>d[i] AND x->close[i-1]<=d[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(x->close[i]<d[i] AND x->close[i-1]>=d[i-1])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, d, sizeof(float)*65500);				// Ind1 = 2-Day Range Switch Indicator

	*(x->elIsValid) = x->firstvalid+3;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+3;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+3;
	*(x->csIsValid) = x->firstvalid+3;
	*(x->ind1FirstValid) = x->firstvalid+3;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Array

	return 0;												// Return NULL for valid system.
}



//	******************************
//	***** 3-Day Range Switch *****
//	******************************
/*
This system is based on defining a trend as prices that continually move away
from a maximum low/high point of the most recent 3 bars. Once the lowest point
of 3 bars is calculated, the system will stay in a long position until that
point is crossed. That point is continually moving up, acting as a trailing
stop. Once a crossing occurs, the system takes a short position and the highest
point of the last 3 days is calculated and follows the position down as a
trailing stop.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 3-Day Range Switch Indicator (d)

MetaStock Code:
	d:=If(C>Ref(Max(H,Max(Ref(H,-1),Ref(H,-2))),-1),Min(L,Min(Ref(L,-1),
		Ref(L,-2))),If(C<Ref(Min(L,Min(Ref(L,-1),Ref(L,-2))),-1),
		Max(H,Max(Ref(H,-1),Ref(H,-2))),PREV));

	EL:=Cross(C,d)
	ES:=Cross(d,C)
*/
int s3(struct datasys *x)									// 3-Day Range Switch
{
	int i=0;
	float *d;

	d=floatarray1;											// 3-Day Range Switch Indicator

	if((x->lastvalid - x->firstvalid)<5) return 2;			// Return 2 if not enough data
															//	to calculate.
	
	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Create 3-Day Range Switch
	{														//	indicator.
		if(x->close[i]>__max(x->high[i-1],__max(x->high[i-2],x->high[i-3])))
			d[i] = __min(x->low[i],__min(x->low[i-1],x->low[i-2]));
		else if(x->close[i]<__min(x->low[i-1],__min(x->low[i-2],x->low[i-3])))
			d[i] = __max(x->high[i],__max(x->high[i-1],x->high[i-2]));
		else d[i]=d[i-1];
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(x->close[i]>d[i] AND x->close[i-1]<=d[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(x->close[i]<d[i] AND x->close[i-1]>=d[i-1])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, d, sizeof(float)*65500);				// Ind1 = 3-Day Range Switch Indicator

	*(x->elIsValid) = x->firstvalid+4;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+4;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+4;
	*(x->csIsValid) = x->firstvalid+4;
	*(x->ind1FirstValid) = x->firstvalid+4;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Array

	return 0;												// Return NULL for valid system.
}


//	******************************
//	***** 4-Day Range Switch *****
//	******************************
/*
This system is based on defining a trend as prices that continually move away
from a maximum low/high point of the most recent 4 bars. Once the lowest point
of 4 bars is calculated, the system will stay in a long position until that
point is crossed. That point is continually moving up, acting as a trailing
stop. Once a crossing occurs, the system takes a short position and the highest
point of the last 4 days is calculated and follows the position down as a
trailing stop.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 4-Day Range Switch Indicator (d)

MetaStock Code:
	d:=If(C>Ref(Max(Max(H,Ref(H,-3)),Max(Ref(H,-1),Ref(H,-2))),-1),
		Min(Min(L,Ref(L,-3)),Min(Ref(L,-1),Ref(L,-2))),
		If(C<Ref(Min(Min(L,Ref(L,-3)),Min(Ref(L,-1),Ref(L,-2))),-1),
		Max(Max(H,Ref(H,-3)),Max(Ref(H,-1),Ref(H,-2))),PREV));

	EL:=Cross(C,d)
	ES:=Cross(d,C)
*/
int s4(struct datasys *x)									// 4-Day Range Switch
{
	int i=0;
	float *d;

	d=floatarray1;											// 4-Day Range Switch Indicator

	if((x->lastvalid - x->firstvalid)<6) return 2;			// Return 2 if not enough data
															//	to calculate.
	
	for (i=x->firstvalid+5; i<=x->lastvalid; i++)			// Create 4-Day Range Switch
	{														//	indicator.
		if(x->close[i]>__max(__max(x->high[i-1],x->high[i-2]),__max(x->high[i-3],x->high[i-4])))
			d[i] = __min(__min(x->low[i],x->low[i-1]),__min(x->low[i-2],x->low[i-3]));
		else if(x->close[i]<__min(__min(x->low[i-1],x->low[i-2]),__min(x->low[i-3],x->low[i-4])))
			d[i] = __max(__max(x->high[i],x->high[i-1]),__max(x->high[i-2],x->high[i-3]));
		else d[i]=d[i-1];
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(x->close[i]>d[i] AND x->close[i-1]<=d[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(x->close[i]<d[i] AND x->close[i-1]>=d[i-1])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, d, sizeof(float)*65500);				// Ind1 = 4-Day Range Switch Indicator

	*(x->elIsValid) = x->firstvalid+5;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+5;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+5;
	*(x->csIsValid) = x->firstvalid+5;
	*(x->ind1FirstValid) = x->firstvalid+5;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Array

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Adaptive Moving Average *****
//	***********************************
/*
The Adaptive Moving Average was designed by Perry Kaufman as a way to change
the speed of a moving average based on the noise level of the market being
analyzed. In a choppy sideways market you want a slower moving average to
reduce whipsaws that occur. In a trending market you want a faster moving
average to lock in profits when a change in trend occurs. The Adaptive Moving
Average accomplishes this and allows a system to be created to trade the
variations in the market.

Unlike standard moving average systems that are based upon the crossing of
different length moving averages, this one is based upon the direction of the
Adaptive Moving Average with no variation in length being necessary.

Further Reading from Perry Kaufman:
	Trading Systems and Methods. (Wiley Trading Advantage Series) John Wiley
		and	Sons, Inc. 1998
	Smarter Trading: Improving Performance in Changing Markets. McGraw-Hill. 1995

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Adaptive Moving Average Indicator (sig)

MetaStock Code:
	Sig:=If(Cum(1)=5,Ref(C,-1)+(Pwr((Abs((C-Ref(C,-4))/
		Sum(Abs(ROC(C,1,$)),4)))*((2/3)-(2/31))+(2/31),2))*
		(C-Ref(C,-1)),PREV+(Pwr((Abs((C-Ref(C,-4))/
		Sum(Abs(ROC(C,1,$)),4)))*((2/3)-(2/31))+(2/31),2))*
		(C-PREV));

	EL:=Sig>Ref(Sig,-1)
	ES:=Sig<Ref(Sig,-1)
*/
int s5(struct datasys *x)									// Adaptive Moving Average
{
	int i=0;
	float op1=0, op2=0, op3=0;								// Define operators for loop
	float *sig;

	sig=floatarray1;										// Adaptive Moving Average Indicator


	if((x->lastvalid - (x->firstvalid))<6) return 2;		// Return 2 if not enough data
															//	to calculate.

	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Create adaptive moving
	{														//	average indicator.

		op1=(x->close[i]-(x->close[i-1]));
		op2=sig[i-1];
		op3=(float)fabs(x->close[i]-(x->close[i-1]))+		
			(float)fabs(x->close[i-1]-(x->close[i-2]))+
			(float)fabs(x->close[i-2]-(x->close[i-3]))+
			(float)fabs(x->close[i-3]-(x->close[i-4]));

		if (i==(x->firstvalid+4))
			sig[i]= x->close[i-1]+(float)pow(fabs((x->close[i]-(x->close[i-4]))/op3)
			*.602151+.064516,2)*op1;
		else sig[i]= sig[i-1]+(float)pow(fabs((x->close[i]-(x->close[i-4]))/op3)
			*.602151+.064516,2) * (x->close[i]-sig[i-1]);
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(sig[i]>sig[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(sig[i]<sig[i-1])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, sig, sizeof(float)*65500);				// Ind1 = Adaptive Moving Average Indicator

	*(x->elIsValid) = x->firstvalid+5;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+5;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+5;
	*(x->csIsValid) = x->firstvalid+5;
	*(x->ind1FirstValid) = x->firstvalid+4;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Array

	return 0;												// Return NULL for valid system.
}




//	**************************************
//	***** Annual Strength/Weakness 1 *****
//	**************************************
/*
This system analyzes the overall strength of the market over the last year by
combining each consecutive 3-month change into a single oscillator. 

The system looks for the oscillator to be positive or negative. If
positive, it takes a long position, if negative, it takes a short position.

Since this system is more long-term in design that most others, a
significant amount of data needs to be loaded for it to function properly.
A minimum of 3 years of data should be loaded. However, the more data loaded,
the more signals will be visible.


Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Annual Strength/Weakness Oscillator (Var1 Indicator)

MetaStock Code:
	var1:=((ROC(C,63,%))+(ROC(Ref(C,-63),63,%))+(ROC(Ref(C,-126),63,%))
		+(ROC(Ref(C,-189),63,%)));

	EL:=var1>0
	ES:=var1<0
*/
int s6(struct datasys *x)									// Annual Strength/Weakness 1
{
	int i=0;
	float *var1;

	var1=floatarray1;										// Var1 Indicator


	if((x->lastvalid - (x->firstvalid))<253) return 2;		// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+252; i<=x->lastvalid; i++)			// Put values in var1 indicator
		var1[i] = ((x->close[i]/x->close[i-63])-1)+
			((x->close[i-63]/x->close[i-126])-1)+
			((x->close[i-126]/x->close[i-189])-1)+
			((x->close[i-189]/x->close[i-252])-1);


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+252; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(var1[i]>0)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(var1[i]<0)
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = Var1 Indicator

	*(x->elIsValid) = x->firstvalid+252;					// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+252;					//	for each output array.
	*(x->esIsValid) = x->firstvalid+252;
	*(x->csIsValid) = x->firstvalid+252;
	*(x->ind1FirstValid) = x->firstvalid+252;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Array

	return 0;												// Return NULL for valid system.
}


//	**************************************
//	***** Annual Strength/Weakness 2 *****
//	**************************************
/*
This system analyzes the overall strength of the market over the last year by
combining each consecutive 3-month change into a single oscillator. 

This system takes a 1-year stochastic of the oscillator and enters long when
the stochastic crosses above its midpoint, and enters short when the oscillator
crosses below its midpoint. This way, it catches the movement of the market
direction as it changes.

Since this system is more long-term in design that most others, a
significant amount of data needs to be loaded for it to function properly.
A minimum of 4 years of data should be loaded. However, the more data loaded,
the more signals will be visible.


Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Annual Strength/Weakness Oscillator (Var1 Indicator)
	Ind1 = 252-Period Stochastic of Var1 with 5-Period Slowing

MetaStock Code:
	var1:=((ROC(C,63,%))+(ROC(Ref(C,-63),63,%))+(ROC(Ref(C,-126),63,%))
		+(ROC(Ref(C,-189),63,%)));
	var2:=Sum((var1-LLV(var1,252)),5)/Sum((HHV(var1,252)-LLV(var1,252)),5);

	EL:=var2>.5
	ES:=var2<.5
*/
int s7(struct datasys *x)									// Annual Strength/Weakness 2
{
	int i=0, j=0;
	float hhvA=0, llvA=0;
	float *var1, *var2, *hhv, *llv;
	
	var1=floatarray1;										// Var1 Indicator
	var2=floatarray2;										// 252-Period Stochastic of Var1 with 5-Period Slowing
	hhv=floatarray3;										// 252-Period Highest High Value of Var1
	llv=floatarray4;										// 252-Period Lowest Low Value of Var1


	if((x->lastvalid - (x->firstvalid))<508) return 2;		// Return 2 if not enough data
															//	to calculate.

	for (i=x->firstvalid+252; i<=x->lastvalid; i++)			// Put values in var1 indicator
		var1[i] = ((x->close[i]/x->close[i-63])-1)+
			((x->close[i-63]/x->close[i-126])-1)+
			((x->close[i-126]/x->close[i-189])-1)+
			((x->close[i-189]/x->close[i-252])-1);


	for (i=x->firstvalid+503; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 252-period levels.
		for (j=i-252; j<=i; j++)
		{
			if (j==i-252)
			{
				hhvA=var1[j-1];
				llvA=var1[j-1];
			}

			if(var1[j]>hhvA) hhvA=var1[j];
			if(var1[j]<llvA) llvA=var1[j];
		}

		hhv[i]=hhvA;
		llv[i]=llvA;
	}


	for(i=x->firstvalid+507; i<=x->lastvalid; i++)			// 252-Period Stochastic of Var1 with 5-Period Slowing
		var2[i]=((var1[i]-llv[i])+
				(var1[i-1]-llv[i-1])+
				(var1[i-2]-llv[i-2])+
				(var1[i-3]-llv[i-3])+
				(var1[i-4]-llv[i-4]))/
				((hhv[i]-llv[i])+
				(hhv[i-1]-llv[i-1])+
				(hhv[i-2]-llv[i-2])+
				(hhv[i-3]-llv[i-3])+
				(hhv[i-4]-llv[i-4]));
		
		

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+507; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(var2[i]>0.5)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(var2[i]<0.5)
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = Var1 Indicator
	memcpy (x->ind2, var2, sizeof(float)*65500);			// Ind1 = 252-Period Stochastic of Var1 with 5-Period Slowing

	*(x->elIsValid) = x->firstvalid+507;					// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+507;					//	for each output array.
	*(x->esIsValid) = x->firstvalid+507;
	*(x->csIsValid) = x->firstvalid+507;
	*(x->ind1FirstValid) = x->firstvalid+252;
	*(x->ind2FirstValid) = x->firstvalid+507;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	*****************
//	***** Aroon *****
//	*****************
/*
The Aroon indicator was created by Tushar Chande as a means of identifying
impending trending action or an impending trading range. 
This system enter when the two Aroon indicators are at extremes from each
other. This is the signal for trending action. The system exits when the
indicator of the entry direction turns to zero strength. 

Further Reading from Tushar Chande:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators (With Stanley Kroll). (Wiley Finance Editions) John Wiley
		and Sons, Inc. 1994
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Aroon Up Indicator
	Ind2 = Aroon Down Indicator

MetaStock Code:
	EL:= AroonUp(14)=100 AND  AroonDown(14)=0
	CL:= AroonUp(14)=0
	ES:= AroonUp(14)=0 AND  AroonDown(14)=100
	CS:= AroonDown(14)=0
*/
int s8(struct datasys *x)									// Aroon
{
	int i=0, j=0;
	float hhvA=0, llvA=0;
	float *hhv, *llv, *AroonUp, *AroonDown;

	hhv=floatarray1;										// 14-Period Highest High Value of Highs
	llv=floatarray2;										// 14-Period Lowest Low Value of Lows
	AroonUp=floatarray3;									// Aroon Up Indicator
	AroonDown=floatarray4;									// Aroon Down Indicator


	if((x->lastvalid - (x->firstvalid))<15) return 2;		// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 14-day levels.
		for (j=i-13; j<=i; j++)
		{
			if (j==i-13)
			{
				hhvA=x->high[j-1];
				llvA=x->low[j-1];
			}

			if(x->high[j]>hhvA) hhvA=x->high[j];
			if(x->low[j]<llvA) llvA=x->low[j];
		}

		hhv[i]=hhvA;
		llv[i]=llvA;
	}


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Create Aroon Up and Aroon Down indicators
		for (j=__max(j-28,0); j<=i; j++)
		{
			if(x->high[j]==hhv[i])
				AroonUp[i]=(float) __max((float)100-((i-j)*((1.0/14.0)*(float)100)),0);
			if(x->low[j]==llv[i])
				AroonDown[i]=(float) __max((float)100-((i-j)*((1.0/14.0)*(float)100)),0);
		}



	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(AroonUp[i]==100 AND AroonDown[i]==0)
			x->el[i]=1;
		if(AroonUp[i]==0)
			x->cl[i]=1;
		if(AroonUp[i]==0 AND AroonDown[i]==100)
			x->es[i]=1;
		if(AroonDown[i]==0)
			x->cs[i]=1;
	}

	memcpy (x->ind1, AroonUp, sizeof(float)*65500);			// Ind1 = Aroon Up Indicator
	memcpy (x->ind2, AroonDown, sizeof(float)*65500);		// Ind2 = Aroon Down Indicator

	*(x->elIsValid) = x->firstvalid+14;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+14;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+14;
	*(x->csIsValid) = x->firstvalid+14;
	*(x->ind1FirstValid) = x->firstvalid+14;
	*(x->ind2FirstValid) = x->firstvalid+14;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}



//	*************************
//	***** Aroon Reversal*****
//	*************************
/*
The Aroon indicator was created by Tushar Chande as a means of identifying
impending trending action or an impending trading range. 
This system enter when the two Aroon indicators are at extremes from each
other. This is the signal for trending action. The system exits when there
is a reversal of conditions.  

Further Reading from Tushar Chande:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators (With Stanley Kroll). (Wiley Finance Editions) John Wiley
		and Sons, Inc. 1994
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Aroon Up Indicator
	Ind2 = Aroon Down Indicator

MetaStock Code:
	EL:=AroonUp(14)=100 AND AroonDown(14)=0
	CL:=AroonUp(14)=0 AND AroonDown(14)=100
	ES:=AroonUp(14)=0 AND AroonDown(14)=100
	CS:=AroonUp(14)=100 AND AroonDown(14)=0
*/
int s9(struct datasys *x)									// Aroon
{
	int i=0, j=0;
	float hhvA, llvA;
	float *hhv, *llv, *AroonUp, *AroonDown;	

	hhv=floatarray1;										// 14-Period Highest High Value of Highs
	llv=floatarray2;										// 14-Period Lowest Low Value of Lows
	AroonUp=floatarray3;									// Aroon Up Indicator
	AroonDown=floatarray4;									// Aroon Down Indicator


	if((x->lastvalid - (x->firstvalid))<15) return 2;		// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 14-day levels.
		for (j=i-13; j<=i; j++)
		{
			if (j==i-13)
			{
				hhvA=x->high[j-1];
				llvA=x->low[j-1];
			}

			if(x->high[j]>hhvA) hhvA=x->high[j];
			if(x->low[j]<llvA) llvA=x->low[j];
		}

		hhv[i]=hhvA;
		llv[i]=llvA;
	}


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Create Aroon Up and Aroon Down indicators
		for (j=__max(j-28,0); j<=i; j++)
		{
			if(x->high[j]==hhv[i])
				AroonUp[i]=(float) __max((float)100-((i-j)*((1.0/14.0)*(float)100)),0);
			if(x->low[j]==llv[i])
				AroonDown[i]=(float) __max((float)100-((i-j)*((1.0/14.0)*(float)100)),0);
		}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(AroonUp[i]==100.0 AND AroonDown[i]==0.0)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(AroonUp[i]==0.0 AND AroonDown[i]==100.0)
		{
			x->es[i]=1;
			x->cl[i]=1;
		}

	}

	memcpy (x->ind1, AroonUp, sizeof(float)*65500);			// Ind1 = Aroon Up Indicator
	memcpy (x->ind2, AroonDown, sizeof(float)*65500);		// Ind2 = Aroon Down Indicator

	*(x->elIsValid) = x->firstvalid+14;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+14;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+14;
	*(x->csIsValid) = x->firstvalid+14;
	*(x->ind1FirstValid) = x->firstvalid+14;
	*(x->ind2FirstValid) = x->firstvalid+14;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Bull Power Bear Power 1 *****
//	***********************************
/*
The concept of Bull Power and Bear Power was developed and introduced by
Alexander Elder. Bull Power is calculated by subtracting a 13-period
exponential moving average from the high price. This is typically displayed as
a histogram oscillating above and below the zero line. A higher reading above
the zero line gives strength to the Bull Power. Bear Power is calculated by
subtracting a 13-period exponential moving average from the low price. This is
also typically displayed as a histogram oscillating above and below the zero
line. A lower reading below the zero line gives strength to the Bear Power. 

This system forces each indicator to use the same scaling method as the other.
As long as the Bull Power is stronger above the zero line than the Bear Power
strength is below the zero line, then a long position is maintained. If Bear
Power strength below the zero line is greater than the Bull Power strength
above the zero line, then a short position is maintained.

Further Reading from Alexander Elder:
	Trading for a Living: Psychology, Trading Tactics, Money Management.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1993
	Study Guide for Trading for a Living: Psychology, Trading Tactics, Money
		Management. (Wiley Finance Editions) John Wiley and Sons, Inc. 1993

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Bull Power Indicator
	Ind2 = Bear Power Indicator

MetaStock Code:
	EL:=(H-Mov(C,13,E))>0-(L-Mov(C,13,E))
	ES:=(L-Mov(C,13,E))<0-(H-Mov(C,13,E))
*/
int s10(struct datasys *x)									// Bull Power Bear Power 1
{
	int i=0;
	float *mov;	

	mov=floatarray1;										// 13 Period Moving Average Array


	if((x->lastvalid - x->firstvalid)<13) return 2;			// Return 2 if not enough data
															//	to calculate.


	mov[x->firstvalid]=x->close[x->firstvalid];				// 13-period exp. moving average first calculation

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 13-period exp. moving average continuous calculation
		mov[i]=(float)((mov[i-1]*(1.0-(2.0/14.0)))+(x->close[i]*(2.0/14.0)));


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+12; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->high[i]-mov[i]>(0.0-(x->low[i]-mov[i])))
		{
			x->el[i]=1;
			x->cs[i]=1;
		}
		else
		{
			x->cl[i]=1;
			x->es[i]=1;
		}

		x->ind1[i]=(x->high[i]-mov[i]);						// Ind1 = Bull Power Indicator
		x->ind2[i]=(x->low[i]-mov[i]);						// Ind2 = Bear Power Indicator
	}



	*(x->elIsValid) = x->firstvalid+12;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+12;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+12;
	*(x->csIsValid) = x->firstvalid+12;
	*(x->ind1FirstValid) = x->firstvalid+12;
	*(x->ind2FirstValid) = x->firstvalid+12;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays

	return 0;												// Return NULL for valid system.
}



//	***********************************
//	***** Bull Power Bear Power 2 *****
//	***********************************
/*
The concept of Bull Power and Bear Power was developed and introduced by
Alexander Elder. Bull Power is calculated by subtracting a 13-period
exponential moving average from the high price. This is typically displayed as
a histogram oscillating above and below the zero line. A higher reading above
the zero line gives strength to the Bull Power. Bear Power is calculated by
subtracting a 13-period exponential moving average from the low price. This is
also typically displayed as a histogram oscillating above and below the zero
line. A lower reading below the zero line gives strength to the Bear Power. 

This system doesn't look at Bull Power/Bear Power directly. Instead, it looks
at the 5-period linear regression slope of Bull Power and Bear Power to
determine which one is gaining strength. Whichever one is showing a gain in
strength is the position that it takes.

Further Reading from Alexander Elder:
	Trading for a Living: Psychology, Trading Tactics, Money Management.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1993
	Study Guide for Trading for a Living: Psychology, Trading Tactics, Money
		Management. (Wiley Finance Editions) John Wiley and Sons, Inc. 1993

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Bull Power Indicator
	Ind2 = Bear Power Indicator

MetaStock Code:
	var1:=LinRegSlope((L-Mov(C,13,E)),5)>Ref(LinRegSlope((L-Mov(C,13,E)),5),-1);
	var2:=LinRegSlope((H-Mov(C,13,E)),5)<Ref(LinRegSlope((H-Mov(C,13,E)),5),-1);

	EL:=If(BarsSince(var1)<BarsSince(var2),1,0)=1
	ES:=If(BarsSince(var1)<BarsSince(var2),1,0)=0
*/
int s11(struct datasys *x)									// Bull Power Bear Power 2
{
	int i=0;
	int	*hcount, *lcount;									// Counting arrays
	float *mov;												// 13 Period Moving Average Array
	float *var1, *var2;										// Variable BPBP Arrys
	float *hslope, *lslope, *a, *b;							// Calculation arrays
	

	hcount=intarray1;										// High count array
	lcount=intarray2;										// Low count array

	mov=floatarray1;										// Exp. Moving Average array
	var1=floatarray2;										// Var1 array
	var2=floatarray3;										// Var2 array
	hslope=floatarray4;										// Linear Regression Slope of Bull Power array
	lslope=floatarray5;										// Linear Regression Slope of Bear Power array
	a=floatarray6;											// Bull Power array
	b=floatarray7;											// Bear Power array


	if((x->lastvalid - x->firstvalid)<18) return 2;			// Return 2 if not enough data
															//	to calculate.


	mov[x->firstvalid]=x->close[x->firstvalid];				// 13-Period Exp. Moving Average First Calculation

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 13-Period Exp. Moving Average Continuous Calculation
	{														// and H-Mov and L-Mov arrays
		mov[i]=(float)((mov[i-1]*(1.0-(2.0/14.0)))+(x->close[i]*(2.0/14.0)));
		if(i>=x->firstvalid+12)
		{
			a[i]=x->high[i]-mov[i];
			b[i]=x->low[i]-mov[i];
		}
	}


	for (i=x->firstvalid+16; i<=x->lastvalid; i++)			// Create LR Slopes of a[] and b[]
	{
		hslope[i]= (float)
			(((((i*a[i])+((i-1)*a[i-1])+((i-2)*a[i-2])+((i-3)*a[i-3])+((i-4)*a[i-4]))) -
			((i+(i-1)+(i-2)+(i-3)+(i-4)) *
			(a[i]+a[i-1]+a[i-2]+a[i-3]+a[i-4])/5))
			/
			((pow(i,2)+pow(i-1,2)+pow(i-2,2)+pow(i-3,2)+pow(i-4,2)) -
			(pow((i+(i-1)+(i-2)+(i-3)+(i-4)),2) / 5.0)));

		lslope[i]= (float)
			(((((i*b[i])+((i-1)*b[i-1])+((i-2)*b[i-2])+((i-3)*b[i-3])+((i-4)*b[i-4]))) -
			((i+(i-1)+(i-2)+(i-3)+(i-4)) *
			(b[i]+b[i-1]+b[i-2]+b[i-3]+b[i-4])/5))
			/
			((pow(i,2)+pow(i-1,2)+pow(i-2,2)+pow(i-3,2)+pow(i-4,2)) -
			(pow((i+(i-1)+(i-2)+(i-3)+(i-4)),2) / 5.0)));
	}

	for (i=x->firstvalid+17; i<=x->lastvalid; i++)
	{
		if(lslope[i]>lslope[i-1]) var1[i]=1;
		else var1[i]=0;

		if(hslope[i]<hslope[i-1]) var2[i]=1;
		else var2[i]=0;

		if(var1[i]==0) lcount[i]=lcount[i-1]+1;
		else lcount[i]=0;

		if(var2[i]==0) hcount[i]=hcount[i-1]+1;
		else hcount[i]=0;
	}


	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+17; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (lcount[i]<hcount[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}
		else
		{
			x->cl[i]=1;
			x->es[i]=1;
		}

		x->ind1[i]=(x->high[i]-mov[i]);						// Ind1 = Bull Power Indicator
		x->ind2[i]=(x->low[i]-mov[i]);						// Ind2 = Bear Power Indicator
	}

	*(x->elIsValid) = x->firstvalid+17;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+17;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+17;
	*(x->csIsValid) = x->firstvalid+17;
	*(x->ind1FirstValid) = x->firstvalid+17;
	*(x->ind2FirstValid) = x->firstvalid+17;

	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays
	bzero(intarray2,sizeof(int)*65500);

	bzero(floatarray1,sizeof(float)*65500);	
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}



//	***********************************
//	***** Bull Power Bear Power 3 *****
//	***********************************
/*
The concept of Bull Power and Bear Power was developed and introduced by
Alexander Elder. Bull Power is calculated by subtracting a 13-period
exponential moving average from the high price. This is typically displayed as
a histogram oscillating above and below the zero line. A higher reading above
the zero line gives strength to the Bull Power. Bear Power is calculated by
subtracting a 13-period exponential moving average from the low price. This is
also typically displayed as a histogram oscillating above and below the zero
line. A lower reading below the zero line gives strength to the Bear Power. 

This system looks at whether Bull Power and Bear Power are able to maintain
strength, and takes a position when that strength fails.

When the Bear Power comes down to a trough and then moves up again, this system
will wait for the next movement down. If the Bear Power fails to come down to
as low as the first trough does, this is viewed as the Bear Power loosing
strength and takes a long (Bullish) position. Both troughs need to occur below
zero for the entry to be valid

When the Bull Power comes up to a peak and then moves down again, this system
will wait for the next movement up. If the Bull Power fails to come up to as
high as the first peak does, this is viewed as the Bull Power loosing strength
and takes a short (Bearish) position. Both peaks need to occur above zero for
the entry to be valid

Further Reading from Alexander Elder:
	Trading for a Living: Psychology, Trading Tactics, Money Management.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1993
	Study Guide for Trading for a Living: Psychology, Trading Tactics, Money
		Management. (Wiley Finance Editions) John Wiley and Sons, Inc. 1993

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Bull Power Indicator
	Ind2 = Bear Power Indicator

MetaStock Code:
	bear1:=(L-Mov(C,13,E))>Ref((L-Mov(C,13,E)),-1) AND 
		Ref((L-Mov(C,13,E)),-1)<Ref((L-Mov(C,13,E)),-2);
	bull1:=(H-Mov(C,13,E))<Ref((H-Mov(C,13,E)),-1) AND 
		Ref((H-Mov(C,13,E)),-1)>Ref((H-Mov(C,13,E)),-2);

	EL:=ValueWhen(1,bear1,Ref((L-Mov(C,13,E)),-1))>
		ValueWhen(2,bear1,Ref((L-Mov(C,13,E)),-1)) AND 
		BarsSince(bear1)<BarsSince(bull1) AND
		(L-Mov(C,13,E))<0

	ES:=ValueWhen(1,bull1,Ref((H-Mov(C,13,E)),-1))<
		ValueWhen(2,bull1,Ref((H-Mov(C,13,E)),-1)) AND
		BarsSince(bear1)>BarsSince(bull1) AND 
		(H-Mov(C,13,E))>0
*/
int s12(struct datasys *x)									// Bull Power Bear Power 3
{
	int i=0;
	int *bull1, *bear1, *bullcount, *bearcount;
	float *mov, *bearback1, *bearback2, *bullback1, *bullback2;

	bull1=intarray1;										// Bull1 array
	bear1=intarray2;										// Bear1 array
	bullcount=intarray3;									// Bull Count array
	bearcount=intarray4;									// Bear Count array

	mov=floatarray1;										// 13-Period Exp. Moving Average array
	bearback1=floatarray2;									// BearBack1 array
	bearback2=floatarray3;									// BearBack2 array
	bullback1=floatarray4;									// BullBack1 array
	bullback2=floatarray5;									// BullBack2 array

	

	if((x->lastvalid - x->firstvalid)<15) return 2;			// Return 2 if not enough data
															//	to calculate.


	mov[x->firstvalid]=x->close[x->firstvalid];				// 13-Period Exp. Moving Average first calculation

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 13-Period Exp. Moving Average continuous calculation
	{
		mov[i]=(float)((mov[i-1]*(1.0-(2.0/14.0)))+(x->close[i]*(2.0/14.0)));

		if(i>=x->firstvalid+14)								// Bear1 and Bear 2 calculation
		{
			if((x->low[i]-mov[i])>(x->low[i-1]-mov[i-1]) AND
				(x->low[i-1]-mov[i-1])<(x->low[i-2]-mov[i-2]))
				bear1[i]=1;
			else bear1[i]=0;

			if((x->high[i]-mov[i])<(x->high[i-1]-mov[i-1]) AND
				(x->high[i-1]-mov[i-1])>(x->high[i-2]-mov[i-2]))
				bull1[i]=1;
			else bull1[i]=0;
		}
	}


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)
	{
		if(bear1[i]==0) bearcount[i]=bearcount[i-1]+1;		// BarsSince Bear1
		else bearcount[i]=0;

		if(bull1[i]==0) bullcount[i]=bullcount[i-1]+1;		// BarsSince Bull1
		else bullcount[i]=0;

		if(i==x->firstvalid+14)
		{
			bearback1[i]=(x->low[i-1]-mov[i-1]);			// ValueWhen Init
			bearback2[i]=(x->low[i-1]-mov[i-1]);
			bullback1[i]=(x->high[i-1]-mov[i-1]);
			bullback1[i]=(x->high[i-1]-mov[i-1]);
		}
		else												// ValueWhen's
		{
			if(bear1[i]==1)
			{
				bearback2[i]=bearback1[i-1];
				bearback1[i]=(x->low[i-1]-mov[i-1]);
			}
			else
			{
				bearback2[i]=bearback2[i-1];
				bearback1[i]=bearback1[i-1];
			}

			if(bull1[i]==1)
			{
				bullback2[i]=bullback1[i-1];
				bullback1[i]=(x->high[i-1]-mov[i-1]);
			}
			else
			{
				bullback2[i]=bullback2[i-1];
				bullback1[i]=bullback1[i-1];
			}
		}
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.

		if (bearback1[i]>bearback2[i] AND bearcount[i]<bullcount[i]
			AND ((x->low[i]-mov[i])<0))
		{
			x->el[i]=1;
			x->cs[i]=1;
		}
		
		if (bullback1[i]<bullback2[i] AND bearcount[i]>bullcount[i]
			AND ((x->high[i]-mov[i])>0))
		{
			x->es[i]=1;
			x->cl[i]=1;
		}

		x->ind1[i]=(x->high[i]-mov[i]);						// Ind1 = Bull Power Indicator
		x->ind2[i]=(x->low[i]-mov[i]);						// Ind2 = Bear Power Indicator
	}



	*(x->elIsValid) = x->firstvalid+14;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+14;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+14;
	*(x->csIsValid) = x->firstvalid+14;
	*(x->ind1FirstValid) = x->firstvalid+14;
	*(x->ind2FirstValid) = x->firstvalid+14;


	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays
	bzero(intarray2,sizeof(int)*65500);
	bzero(intarray3,sizeof(int)*65500);
	bzero(intarray4,sizeof(int)*65500);

	bzero(floatarray1,sizeof(float)*65500);	
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}



//	***********************************
//	***** Bull Power Bear Power 4 *****
//	***********************************
/*
The concept of Bull Power and Bear Power was developed and introduced by
Alexander Elder. Bull Power is calculated by subtracting a 13-period
exponential moving average from the high price. This is typically displayed as
a histogram oscillating above and below the zero line. A higher reading above
the zero line gives strength to the Bull Power. Bear Power is calculated by
subtracting a 13-period exponential moving average from the low price. This is
also typically displayed as a histogram oscillating above and below the zero
line. A lower reading below the zero line gives strength to the Bear Power. 

This system looks at whether Bull Power and Bear Power are able to maintain
strength, and takes a position when that strength fails.

When the Bear Power comes down to a trough and then moves up again, this system
will wait for the next movement down. If the Bear Power fails to come down to
as low as the first trough does, this is viewed as the Bear Power loosing
strength and takes a long (Bullish) position.

When the Bull Power comes up to a peak and then moves down again, this system
will wait for the next movement up. If the Bull Power fails to come up to as
high as the first peak does, this is viewed as the Bull Power loosing strength
and takes a short (Bearish) position.

Further Reading from Alexander Elder:
	Trading for a Living: Psychology, Trading Tactics, Money Management.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1993
	Study Guide for Trading for a Living: Psychology, Trading Tactics, Money
		Management. (Wiley Finance Editions) John Wiley and Sons, Inc. 1993

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Bull Power Indicator
	Ind2 = Bear Power Indicator

MetaStock Code:
	bear1:=(L-Mov(C,13,E))>Ref((L-Mov(C,13,E)),-1) AND
		Ref((L-Mov(C,13,E)),-1)<Ref((L-Mov(C,13,E)),-2);
	bull1:=(H-Mov(C,13,E))<Ref((H-Mov(C,13,E)),-1) AND 
		Ref((H-Mov(C,13,E)),-1)>Ref((H-Mov(C,13,E)),-2);

	EL:=ValueWhen(1,bear1,Ref((L-Mov(C,13,E)),-1))>
		ValueWhen(2,bear1,Ref((L-Mov(C,13,E)),-1)) AND 
		BarsSince(bear1)<BarsSince(bull1)

	ES:=ValueWhen(1,bull1,Ref((H-Mov(C,13,E)),-1))<
		ValueWhen(2,bull1,Ref((H-Mov(C,13,E)),-1)) AND 
		BarsSince(bear1)>BarsSince(bull1)
*/
int s13(struct datasys *x)									// Bull Power Bear Power 4
{
	int i=0;
	int *bull1, *bear1, *bullcount, *bearcount;
	float *mov, *bearback1, *bearback2, *bullback1, *bullback2;// Arrays
	
	bull1=intarray1;										// Bull1 array
	bear1=intarray2;										// Bear1 array
	bullcount=intarray3;									// Bull Count array
	bearcount=intarray4;									// Bear Count array

	mov=floatarray1;										// 13-Period Exp. Moving Average array
	bearback1=floatarray2;									// BearBack1 array
	bearback2=floatarray3;									// BearBack2 array
	bullback1=floatarray4;									// BullBack1 array
	bullback2=floatarray5;									// BullBack2 array

	if((x->lastvalid - x->firstvalid)<15) return 2;			// Return 2 if not enough data
															//	to calculate.


	mov[x->firstvalid]=x->close[x->firstvalid];				// 13-Period Exp. Moving Average first calculation

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 13-Period Exp. Moving Average continuous calculation
	{
		mov[i]=(float)((mov[i-1]*(1.0-(2.0/14.0)))+(x->close[i]*(2.0/14.0)));

		if(i>=x->firstvalid+14)								// Bear1 and Bear 2 calculation
		{
			if((x->low[i]-mov[i])>(x->low[i-1]-mov[i-1]) AND
				(x->low[i-1]-mov[i-1])<(x->low[i-2]-mov[i-2]))
				bear1[i]=1;
			else bear1[i]=0;

			if((x->high[i]-mov[i])<(x->high[i-1]-mov[i-1]) AND
				(x->high[i-1]-mov[i-1])>(x->high[i-2]-mov[i-2]))
				bull1[i]=1;
			else bull1[i]=0;
		}
	}


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)
	{
		if(bear1[i]==0) bearcount[i]=bearcount[i-1]+1;		// BarsSince Bear1
		else bearcount[i]=0;

		if(bull1[i]==0) bullcount[i]=bullcount[i-1]+1;		// BarsSince Bull1
		else bullcount[i]=0;

		if(i==x->firstvalid+14)
		{
			bearback1[i]=(x->low[i-1]-mov[i-1]);			// ValueWhen Init
			bearback2[i]=(x->low[i-1]-mov[i-1]);
			bullback1[i]=(x->high[i-1]-mov[i-1]);
			bullback1[i]=(x->high[i-1]-mov[i-1]);
		}
		else												// ValueWhen's
		{
			if(bear1[i]==1)
			{
				bearback2[i]=bearback1[i-1];
				bearback1[i]=(x->low[i-1]-mov[i-1]);
			}
			else
			{
				bearback2[i]=bearback2[i-1];
				bearback1[i]=bearback1[i-1];
			}

			if(bull1[i]==1)
			{
				bullback2[i]=bullback1[i-1];
				bullback1[i]=(x->high[i-1]-mov[i-1]);
			}
			else
			{
				bullback2[i]=bullback2[i-1];
				bullback1[i]=bullback1[i-1];
			}
		}
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.

		if (bearback1[i]>bearback2[i] AND bearcount[i]<bullcount[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		
		if (bullback1[i]<bullback2[i] AND bearcount[i]>bullcount[i])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}

		x->ind1[i]=(x->high[i]-mov[i]);						// Ind1 = Bull Power Indicator
		x->ind2[i]=(x->low[i]-mov[i]);						// Ind2 = Bear Power Indicator
	}



	*(x->elIsValid) = x->firstvalid+14;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+14;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+14;
	*(x->csIsValid) = x->firstvalid+14;
	*(x->ind1FirstValid) = x->firstvalid+14;
	*(x->ind2FirstValid) = x->firstvalid+14;


	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays
	bzero(intarray2,sizeof(int)*65500);
	bzero(intarray3,sizeof(int)*65500);
	bzero(intarray4,sizeof(int)*65500);

	bzero(floatarray1,sizeof(float)*65500);	
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	*****************************************
//	***** CCI (Commodity Channel Index) *****
//	*****************************************
/*
This system uses the Commodity Channel Index, but it is still suitable for
stock trading.

The CCI was developed by Donald Lambert and introduced in the October 1980
issue of Commodities magazine (which has since become Futures magazine). The
author suggests using the CCI as an overbought/oversold indicator with +100
being overbought and -100 being oversold.

This system is based upon a further analysis determining that +/- 200 produces
a more significant reversal signal and therefore is more ideal.

While it is very good at capturing profits on the majority of trades, no real
protection mechanism has been put into place. Stop-loss orders should be used
to prevent the few failing trades from removing all acquired profits.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 14-Period Commodity Channel Index Indicator

MetaStock Code:
	EL:= CCI(14)<-200
	ES:= CCI(14)>200
*/
int s14(struct datasys *x)									// CCI (Commodity Channel Index)
{
	int i=0, j=0, masize=0;
	float colg=0, colh=0, coli=0, colj=0, matemp=0;
	float *typical, *movavg, *cci;

	typical=floatarray1;									// Typical Price array
	movavg=floatarray2;										// Moving Average array
	cci=floatarray3;										// CCI Indicator

	if((x->lastvalid - x->firstvalid)<14) return 2;			// Return 2 if not enough data
															//	to calculate.

	masize=14;												// Set Moving Average Size
	matemp=0;												// Initialize matemp.


	
	for(i=x->firstvalid; i<=x->lastvalid; i++)				// Begin 14-period CCI calculation
	{
		typical[i]=(x->high[i]+x->low[i]+x->close[i])/3;
		
		if(i==x->firstvalid+(masize-1))
			for(j=i-(masize-1); j<=i; j++)
				matemp=matemp+typical[j];

		if(i>x->firstvalid+(masize-1))
			matemp=matemp-typical[i-masize]+typical[i];

		if(i>=x->firstvalid+(masize-1))
		{
			movavg[i]=matemp/(masize);

			colg=0;
			colh=0;
			coli=0;
			colj=0;


			for(j=i-(masize-1); j<=i; j++)
				colg=colg+(float) fabs(typical[j]-movavg[i]);

			colh=colg/masize;
			coli=colh* (float)0.015;
			colj=typical[i]-movavg[i];
			cci[i]=colj/coli;
		}
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+13; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(cci[i]<(-200))
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(cci[i]>200)
		{
			x->es[i]=1;
			x->cl[i]=1;
		}

	}
	memcpy (x->ind1, cci, sizeof(float)*65500);				// Ind1 = 14-Period Commodity Channel Index Indicator

	*(x->elIsValid) = x->firstvalid+13;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+13;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+13;
	*(x->csIsValid) = x->firstvalid+13;
	*(x->ind1FirstValid) = x->firstvalid+13;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays	
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}


//	*************************
//	***** CCI Fibonacci *****
//	*************************
/*
This system uses the Commodity Channel Index, but it is still suitable for
stock trading.

The CCI was developed by Donald Lambert and introduced in the October 1980
issue of Commodities magazine (which has since become Futures magazine). The
author suggests using the CCI as an overbought/oversold indicator with +100
being overbought and -100 being oversold.

The CCI Fibonacci is identical to the CCI, except that instead of using a
14-period CCI, it uses the average of 3 CCI's calculated at Fibonacci levels
of 8, 13, and 21.

This system is based upon a further analysis determining that +/- 200 produces
a more significant entry signal and therefore is more ideal. Also, instead of
exiting at the opposite 200 level, it exits when the CCI crosses a zero level.

While it is very good at capturing profits on the majority of trades, no real
protection mechanism has been put into place. Stop-loss orders should be used
to prevent the few failing trades from removing all acquired profits.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Fibonacci CCI Indicator
	Ind2 = 8-Period CCI Indicator
	Ind3 = 13-Period CCI Indicator
	Ind4 = 21-Period CCI Indicator

MetaStock Code:
	Var1:=(CCI(8)+CCI(13)+CCI(21))/3;

	EL:=Var1<-200
	CL:= Var1>0
	ES:= Var1>200
	CS:= Var1<0
*/
int s15(struct datasys *x)									// CCI Fibonacci
{
	int i=0, j=0, masize=0;
	float colg=0, colh=0, coli=0, colj=0, matemp=0;
	float *typical, *movavg, *cci8, *cci13, *cci21, *ccifib;

	typical=floatarray1;									// Typical Price array
	movavg=floatarray2;										// Moving Average array
	cci8=floatarray3;										// 8-Period CCI Indicator
	cci13=floatarray4;										// 13-Period CCI Indicator
	cci21=floatarray5;										// 21-Period CCI Indicator
	ccifib=floatarray6;										// CCI Fibonacci Composite array

	if((x->lastvalid - x->firstvalid)<22) return 2;			// Return 2 if not enough data
															//	to calculate.

	masize=8;												// Set Moving Average Size
	matemp=0;												// Initialize matemp.
	
	for(i=x->firstvalid; i<=x->lastvalid; i++)				// Begin 8-period CCI calculation
	{
		typical[i]=(x->high[i]+x->low[i]+x->close[i])/3;
		
		if(i==x->firstvalid+(masize-1))
			for(j=i-(masize-1); j<=i; j++)
				matemp=matemp+typical[j];

		if(i>x->firstvalid+(masize-1))
			matemp=matemp-typical[i-masize]+typical[i];

		if(i>=x->firstvalid+(masize-1))
		{
			movavg[i]=matemp/(masize);

			colg=0;
			colh=0;
			coli=0;
			colj=0;


			for(j=i-(masize-1); j<=i; j++)
				colg=colg+(float) fabs(typical[j]-movavg[i]);

			colh=colg/masize;
			coli=colh* (float)0.015;
			colj=typical[i]-movavg[i];
			cci8[i]=colj/coli;
		}
	}

	masize=13;												// Set Moving Average Size
	matemp=0;												// Initialize matemp.
	
	for(i=x->firstvalid; i<=x->lastvalid; i++)				// Begin 13-period CCI calculation
	{
		typical[i]=(x->high[i]+x->low[i]+x->close[i])/3;
		
		if(i==x->firstvalid+(masize-1))
			for(j=i-(masize-1); j<=i; j++)
				matemp=matemp+typical[j];

		if(i>x->firstvalid+(masize-1))
			matemp=matemp-typical[i-masize]+typical[i];

		if(i>=x->firstvalid+(masize-1))
		{
			movavg[i]=matemp/(masize);

			colg=0;
			colh=0;
			coli=0;
			colj=0;


			for(j=i-(masize-1); j<=i; j++)
				colg=colg+(float) fabs(typical[j]-movavg[i]);

			colh=colg/masize;
			coli=colh* (float)0.015;
			colj=typical[i]-movavg[i];
			cci13[i]=colj/coli;
		}
	}

	masize=21;												// Set Moving Average Size
	matemp=0;												// Initialize matemp.
	
	for(i=x->firstvalid; i<=x->lastvalid; i++)				// Begin 21-period CCI calculation
	{
		typical[i]=(x->high[i]+x->low[i]+x->close[i])/3;
		
		if(i==x->firstvalid+(masize-1))
			for(j=i-(masize-1); j<=i; j++)
				matemp=matemp+typical[j];

		if(i>x->firstvalid+(masize-1))
			matemp=matemp-typical[i-masize]+typical[i];

		if(i>=x->firstvalid+(masize-1))
		{
			movavg[i]=matemp/(masize);

			colg=0;
			colh=0;
			coli=0;
			colj=0;


			for(j=i-(masize-1); j<=i; j++)
				colg=colg+(float) fabs(typical[j]-movavg[i]);

			colh=colg/masize;
			coli=colh* (float)0.015;
			colj=typical[i]-movavg[i];
			cci21[i]=colj/coli;
		}
	}


	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+21; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		ccifib[i]=(cci8[i]+cci13[i]+cci21[i])/3;

		if(ccifib[i]<(-200))
			x->el[i]=1;
		if(ccifib[i]>0)
			x->cl[i]=1;
		if(ccifib[i]>200)
			x->es[i]=1;
		if(ccifib[i]<0)
			x->cs[i]=1;
	}

	memcpy (x->ind1, ccifib, sizeof(float)*65500);			// Ind1 = Fibonacci CCI Indicator
	memcpy (x->ind2, cci8, sizeof(float)*65500);			// Ind2 = 8-Period CCI Indicator
	memcpy (x->ind3, cci13, sizeof(float)*65500);			// Ind3 = 13-Period CCI Indicator
	memcpy (x->ind4, cci21, sizeof(float)*65500);			// Ind4 = 21-Period CCI Indicator


	*(x->elIsValid) = x->firstvalid+21;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+21;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+21;
	*(x->csIsValid) = x->firstvalid+21;
	*(x->ind1FirstValid) = x->firstvalid+20;
	*(x->ind2FirstValid) = x->firstvalid+7;
	*(x->ind3FirstValid) = x->firstvalid+12;
	*(x->ind4FirstValid) = x->firstvalid+20;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays	
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	****************************************
//	***** CCI Moving Average Crossover *****
//	****************************************
/*
This system uses the Commodity Channel Index, but it is still suitable for
stock trading.

The CCI was developed by Donald Lambert and introduced in the October 1980
issue of Commodities magazine (which has since become Futures magazine). The
author suggests using the CCI as an overbought/oversold indicator with +100
being overbought and -100 being oversold.

This system combines three different methods into one trading system. First,
it uses a 34-period CCI indicator. Second, it takes a 200-period stochastic of
the CCI that has 13-periods of smoothing. Third, it uses a 9-period moving
average of the stochastic as a signal generator.

The system enters a long position when the stochastic of the CCI crosses above
its own 9-period moving average. It the exits the long position and takes a
short position when the stochastic of the CCI crosses below its 9-period moving
average.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = CCI stochastic
	Ind2 = 9-Period Exp. Moving Average of CCI Stochastic
	
MetaStock Code:
	var1:=Sum(CCI(34),13)/Sum(HHV(CCI(34),200)-LLV(CCI(34),200),13);

	EL:=Cross(var1,Mov(var1,9,E))
	ES:=Cross(Mov(var1,9,E),var1)
*/
int s16(struct datasys *x)									// CCI Moving Average Crossover
{
	int i=0, j=0, masize=0;
	float colg=0, colh=0, coli=0, colj=0, matemp=0, hhv=0, llv=0;
	float *hhv200, *llv200, *typical, *movavg, *cci, *sumnum, *sumden, *ma9;

	hhv200=floatarray1;										// 200-Period Highest High Value array
	llv200=floatarray2;										// 200-Period Lowest Low Value array
	typical=floatarray3;									// Typical Price array
	movavg=floatarray4;										// Moving Average array
	cci=floatarray5;										// 14-Period CCI array
	sumnum=floatarray6;										// Summed Numerator array (for CCI Smoothed Stochastic)
	sumden=floatarray7;										// Summed Denominator array (for CCI Smoothed Stochastic)
	ma9=floatarray8;										// 9-Period Exp. Moving Average of CCI Stochastic array


	if((x->lastvalid - x->firstvalid)<254) return 2;		// Return 2 if not enough data
															//	to calculate.


	masize=34;												// Set Moving Average Size
	matemp=0;												// Initialize matemp.
	
	for(i=x->firstvalid; i<=x->lastvalid; i++)				// Begin 34-period CCI calculation
	{
		typical[i]=(x->high[i]+x->low[i]+x->close[i])/3;
		
		if(i==x->firstvalid+(masize-1))
			for(j=i-(masize-1); j<=i; j++)
				matemp=matemp+typical[j];

		if(i>x->firstvalid+(masize-1))
			matemp=matemp-typical[i-masize]+typical[i];

		if(i>=x->firstvalid+(masize-1))
		{
			movavg[i]=matemp/(masize);

			colg=0;
			colh=0;
			coli=0;
			colj=0;


			for(j=i-(masize-1); j<=i; j++)
				colg=colg+(float) fabs(typical[j]-movavg[i]);

			colh=colg/masize;
			coli=colh* (float)0.015;
			colj=typical[i]-movavg[i];
			cci[i]=colj/coli;
		}
	}


	
	for (i=x->firstvalid+233; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 200-day levels.
		for (j=i-199; j<=i; j++)
		{
			if (j==i-199)
			{
				hhv=cci[j-1];
				llv=cci[j-1];
			}

			if(cci[j]>hhv) hhv=cci[j];
			if(cci[j]<llv) llv=cci[j];
		}

		hhv200[i]=hhv;
		llv200[i]=llv;
	}

	

	for (i=x->firstvalid+245; i<=x->lastvalid; i++)
	{
		for (j=i-12; j<=i; j++)
		{
			sumnum[i]=sumnum[i]+cci[j];
			sumden[i]=sumden[i]+(hhv200[j]-llv200[j]);
		}

		if (i==x->firstvalid+245)
			ma9[i]=sumnum[i]/sumden[i];
		else if (i>x->firstvalid+245)
			ma9[i]=((sumnum[i]/sumden[i])*(float)0.2)+(ma9[i-1]*(float)0.8);
	}


	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+245; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if((sumnum[i]/sumden[i])>ma9[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if((sumnum[i]/sumden[i])<ma9[i])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}

		x->ind1[i]=(sumnum[i]/sumden[i]);					// Ind1 = CCI stochastic
		x->ind2[i]=ma9[i];									// Ind2 = 9-Period EMA of CCI Stochastic
	}


	*(x->elIsValid) = x->firstvalid+245;					// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+245;					//	for each output array.
	*(x->esIsValid) = x->firstvalid+245;
	*(x->csIsValid) = x->firstvalid+245;
	*(x->ind1FirstValid) = x->firstvalid+245;
	*(x->ind2FirstValid) = x->firstvalid+245;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays	
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	**************************************
//	***** Chande Forecast Oscillator *****
//	**************************************
/*
The Forecast Oscillator was designed by Tushar Chande and is calculated by
subtracting the closing price from the linear regression of closing prices and
then displays that as a percentage. The author recommends the Forecast
Oscillator crossing a 3-period moving average of itself as a signal that a
trend in the direction of oscillator movement may be eminent. The forecast
oscillator being positive or negative when this occurs has been added so as to
prevent late entry.

Further Reading from Tushar Chande:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators (With Stanley Kroll). (Wiley Finance Editions) John Wiley
		and Sons, Inc. 1994
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 14-Period Chande Forecast Oscillator Indicator
	
MetaStock Code:
	EL:= ForecastOsc(C,14)<0 AND 
		Cross(ForecastOsc(C,14),Mov(ForecastOsc(C,14),3,S))
	ES:= ForecastOsc(C,14)>0 AND 
		Cross(Mov(ForecastOsc(C,14),3,S),ForecastOsc(C,14))
*/
int s17(struct datasys *x)									// Chande Forecast Oscillator
{
	int i=0, j=0;
	float sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0;
	float *linreg, *lrslope, *cfo;

	linreg=floatarray1;										// 14-Period Linear Regression array
	lrslope=floatarray2;									// 14-Period Linear Regression Slope array
	cfo=floatarray3;										// 14-Period Chande Forecast Oscillator


	if((x->lastvalid - x->firstvalid)<18) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+13; i<=x->lastvalid; i++)			// 14-Period Linear Regression and Slope
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-13; j<=i; j++)
		{
			sum1=sum1+((float)j*x->close[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->close[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+13)
			{
				movc=movc+x->close[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+13)
		{
			movc=movc-x->close[i-14]+x->close[i];
			movcum=movcum-(i-14)+i;
		}

		lrslope[i]=
			(sum1-((sum2*sum3)/14))/(sum4-(((float)pow(sum2,2))/(float)14));

		linreg[i]=			
			(14*sum1-sum2*sum3)/
			(14*sum4-(float)pow(sum2,2))*i+((movc/14)-(movcum/14)*
			(14*sum1-sum2*sum3)/
			(14*sum4-(float)pow(sum2,2)));

		if(i>x->firstvalid+14)								// Chande Forecast Oscillator
			cfo[i]=((x->close[i]-(linreg[i-1]+lrslope[i-1]))/x->close[i])*100;

	}


	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+17; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (cfo[i]<0 AND cfo[i]>((cfo[i]+cfo[i-1]+cfo[i-2])/3) AND
			cfo[i-1]<((cfo[i-1]+cfo[i-2]+cfo[i-3])/3))
		{
			x->el[i]=1;
			x->cs[i]=1;
		}
		if (cfo[i]>0 AND cfo[i]<((cfo[i]+cfo[i-1]+cfo[i-2])/3) AND
			cfo[i-1]>((cfo[i-1]+cfo[i-2]+cfo[i-3])/3))
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, cfo, sizeof(float)*65500);				// Ind1 = 14-Period Chande Forecast Oscillator Indicator

	*(x->elIsValid) = x->firstvalid+17;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+17;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+17;
	*(x->csIsValid) = x->firstvalid+17;
	*(x->ind1FirstValid) = x->firstvalid+13;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays	
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}



//	*****************************
//	***** CMO Reinforcement *****
//	*****************************
/*
The CMO (Chande Momentum Oscillator) was created by Tushar Chande as a
stand-alone momentum indicator to replace all of the other momentum indicators
that show too much correlation with one another.

This system works on the principle of positive reinforcement. It uses two
different period CMO indicators, a 13-period and a 34-period. The 13-period
being the faster one, it looks for this CMO to have a pullback and then resume
its original direction. The longer period CMO (the 34-period) cannot have had
the same pullback. This way, a small cycle pulls back and then resumes in the
direction of the longer-term momentum. The system then exits when the 13-period
CMO has another change if direction.

Further Reading from Tushar Chande:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators (With Stanley Kroll). (Wiley Finance Editions) John Wiley
		and Sons, Inc. 1994
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 13-Period Chande Momentum Oscillator
	Ind2 = 34-Period Chande Momentum Oscillator
	
MetaStock Code:
	EL:= CMO(C,13)>Ref(CMO(C,13),-1) AND Ref(CMO(C,13),-1)<Ref(CMO(C,13),-2)
		AND CMO(C,34)>Ref(CMO(C,34),-1) AND Ref(CMO(C,34),-1)>Ref(CMO(C,34),-2)

	CL:=CMO(C,13)<Ref(CMO(C,13),-1)

	ES:= CMO(C,13)<Ref(CMO(C,13),-1) AND Ref(CMO(C,13),-1)>Ref(CMO(C,13),-2)
		AND CMO(C,34)<Ref(CMO(C,34),-1) AND Ref(CMO(C,34),-1)<Ref(CMO(C,34),-2)

	CS:=CMO(C,13)>Ref(CMO(C,13),-1)
*/
int s18(struct datasys *x)									// CMO Reinforcement
{
	int i=0, j=0;
	float up=0, down=0;
	float *cmo13, *cmo34;

	cmo13=floatarray1;										// 13=Period Chande Momentum Oscillator array
	cmo34=floatarray2;										// 34=Period Chande Momentum Oscillator array


	if((x->lastvalid - x->firstvalid)<37) return 2;			// Return 2 if not enough data
															//	to calculate.


	for(i=x->firstvalid+13; i<=x->lastvalid; i++)			// Create 13-Period Chande
	{														//	Momentum Oscillator
		up=0;
		down=0;

		for(j=i-12; j<=i; j++)
		{
			if(x->close[j]>x->close[j-1])
				up=up+(x->close[j]-x->close[j-1]);
			if(x->close[j]<x->close[j-1])
				down=down+(x->close[j-1]-x->close[j]);
		}

		cmo13[i]=((up-down)/(up+down))*100;
	}

	for(i=x->firstvalid+34; i<=x->lastvalid; i++)			// Create 34-Period Chande
	{														//	Momentum Oscillator
		up=0;
		down=0;

		for(j=i-33; j<=i; j++)
		{
			if(x->close[j]>x->close[j-1])
				up=up+(x->close[j]-x->close[j-1]);
			if(x->close[j]<x->close[j-1])
				down=down+(x->close[j-1]-x->close[j]);
		}

		cmo34[i]=((up-down)/(up+down))*100;
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+36; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(cmo13[i]>cmo13[i-1] AND cmo13[i-1]<cmo13[i-2] AND
			cmo34[i]>cmo34[i-1] AND cmo34[i-1]>cmo34[i-2])
			x->el[i]=1;

		if(cmo13[i]<cmo13[i-1])
			x->cl[i]=1;

		if(cmo13[i]<cmo13[i-1] AND cmo13[i-1]>cmo13[i-2] AND
			cmo34[i]<cmo34[i-1] AND cmo34[i-1]<cmo34[i-2])
			x->es[i]=1;

		if(cmo13[i]>cmo13[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, cmo13, sizeof(float)*65500);			// Ind1 = 13-Period Chande Momentum Oscillator
	memcpy (x->ind2, cmo34, sizeof(float)*65500);			// Ind2 = 34-Period Chande Momentum Oscillator

	*(x->elIsValid) = x->firstvalid+36;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+36;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+36;
	*(x->csIsValid) = x->firstvalid+36;
	*(x->ind1FirstValid) = x->firstvalid+13;
	*(x->ind2FirstValid) = x->firstvalid+34;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays	
	bzero(floatarray2,sizeof(float)*65500);


	return 0;												// Return NULL for valid system.
}




//	************************
//	***** CMO Reversal *****
//	************************
/*
The CMO (Chande Momentum Oscillator) was created by Tushar Chande as a
stand-alone momentum indicator to replace all of the other momentum indicators
that show too much correlation with one another.

This system looks specifically for the CMO to turn up from  down-trending
momentum to enter a long position. As soon as the CMO reverses, the long
position is exited and a short position entered. This way a position is always
in the direction of the momentum of the security (except for the initial day of
the reversal of the CMO). 

Further Reading from Tushar Chande:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators (With Stanley Kroll). (Wiley Finance Editions) John Wiley
		and Sons, Inc. 1994
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 13-Period Chande Momentum Oscillator
	
MetaStock Code:
	EL:= CMO(C,13)>Ref(CMO(C,13),-1) AND Ref(CMO(C,13),-1)<Ref(CMO(C,13),-2)
	ES:= CMO(C,13)<Ref(CMO(C,13),-1) AND Ref(CMO(C,13),-1)>Ref(CMO(C,13),-2)
*/
int s19(struct datasys *x)									// CMO Reversal
{
	int i=0, j=0;
	float up=0, down=0;
	float *cmo13;

	cmo13=floatarray1;										// 13-Period Chande Momentum Oscillator


	if((x->lastvalid - x->firstvalid)<16) return 2;			// Return 2 if not enough data
															//	to calculate.


	for(i=x->firstvalid+13; i<=x->lastvalid; i++)			// Create 13-Period Chande
	{														//	Momentum Oscillator
		up=0;
		down=0;

		for(j=i-12; j<=i; j++)
		{
			if(x->close[j]>x->close[j-1])
				up=up+(x->close[j]-x->close[j-1]);
			if(x->close[j]<x->close[j-1])
				down=down+(x->close[j-1]-x->close[j]);
		}

		cmo13[i]=((up-down)/(up+down))*100;
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+15; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(cmo13[i]>cmo13[i-1] AND cmo13[i-1]<cmo13[i-2])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(cmo13[i]<cmo13[i-1] AND cmo13[i-1]>cmo13[i-2])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, cmo13, sizeof(float)*65500);			// Ind1 = 13-Period Chande Momentum Oscillator

	*(x->elIsValid) = x->firstvalid+15;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+15;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+15;
	*(x->csIsValid) = x->firstvalid+15;
	*(x->ind1FirstValid) = x->firstvalid+13;

	bzero(floatarray1,sizeof(float)*65500);					// Clean array

	return 0;												// Return NULL for valid system.
}




//	*******************************
//	***** Congestion Breakout *****
//	*******************************
/*
This system looks for a 3-month market congestion where the market has been in
a 10% trading range. The security then needs to break out of that congestion
range on high volume. If it breaks out of the top of the range, it takes a long
position. If it breaks out of the bottom of the range, it takes a short
position. It stays in the position until the market consolidates back into a
10% congestion range.

Note that since these types of congestion breakouts can be rare, it is not
uncommon for a security to go for years without ever seeing one. When testing
using this type of system a minimum of 5 years of data should be used, and 10
years would be even better.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 63-Period Highest High Value of Close
	Ind2 = 63-Period Lowest Low Value of Close
	Ind3 = 5-Period Moving Average of Volume
	Ind4 = 20-Period Moving Average of Volume
	Ind5 = Congestion Breakout Indicator
	
MetaStock Code:
	cg:=((HHV(C,63)-LLV(C,63))/LLV(C,63))*100;

	EL:=Ref(cg,-5)<10 AND cg>=10 AND C>Ref(HHV(C,63),-5) AND
		Mov(V,5,S)>=1.5*(Ref(Mov(V,20,S),-5))

	CL:= cg<=10

	ES:= Ref(cg,-5)<10 AND cg>=10 AND C<Ref(LLV(C,63),-5) AND
		Mov(V,5,S)>=1.5*(Ref(Mov(V,20,S),-5))

	CS:= cg<=10

*/
int s20(struct datasys *x)									// Congestion Breakout
{
	int i=0, j=0;
	float hhv=0, llv=0, movstor=0;
	float *hhv63, *llv63, *movV5, *movV20, *cg;

	hhv63=floatarray1;										// 63-Period Highest High Value of Close
	llv63=floatarray2;										// 63-Period Lowest Low Value of Close
	movV5=floatarray3;										// 5-Period Moving Average of Volume
	movV20=floatarray4;										// 20-Period Moving Average of Volume
	cg=floatarray5;											// Congestion Breakout Indicator

	if((x->lastvalid - x->firstvalid)<68) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+62; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 63-day levels.
		for (j=i-61; j<=i; j++)
		{
			if (j==i-61)
			{
				hhv=x->close[j-1];
				llv=x->close[j-1];
			}

			if(x->close[j]>hhv) hhv=x->close[j];
			if(x->close[j]<llv) llv=x->close[j];
		}

		hhv63[i]=hhv;
		llv63[i]=llv;
	}


	for (i=x->firstvalid+4; i>=x->firstvalid; i--)			// 5-Period Moving Average of Volume
	{
		movstor=movstor+x->volume[i];
	}

	movV5[x->firstvalid+4]=(float)(movstor/5.0);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->volume[i] - x->volume[i-5];
		movV5[i] = (float)(movstor / 5.0);
	}



	movstor=0;

	for (i=x->firstvalid+19; i>=x->firstvalid; i--)			// 20-Period Moving Average of Volume
	{
		movstor=movstor+x->volume[i];
	}

	movV20[x->firstvalid+19]=(float)(movstor/20.0);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->volume[i] - x->volume[i-20];
		movV20[i] = (float)(movstor / 20.0);
	}


	for (i=x->firstvalid+62; i<=x->lastvalid; i++)			// Calculate Congestion Indicator
	{
		cg[i]=((hhv63[i]-llv63[i])/llv63[i])*(float)100.0;
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+67; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(cg[i-5]<10.0 AND cg[i]>=10.0 AND x->close[i]>hhv63[i-5] 
			AND movV5[i]>=(movV20[i-5]*(float)1.5))
			x->el[i]=1;
			else x->el[i]=0;

		if(cg[i]<=10.0)
			x->cl[i]=1;
			else x->cl[i]=0;
		
		if(cg[i-5]<10.0 AND cg[i]>=10.0 AND x->close[i]<llv63[i-5] 
			AND movV5[i]>=(movV20[i-5]*(float)1.5))
			x->es[i]=1;
			else x->es[i]=0;

		if(cg[i]<=10.0)
			x->cs[i]=1;
			else x->cs[i]=0;
	}

	memcpy (x->ind1, hhv63, sizeof(float)*65500);			// Ind1 = 63-Period Highest High Value of Close
	memcpy (x->ind2, llv63, sizeof(float)*65500);			// Ind2 = 63-Period Lowest Low Value of Close
	memcpy (x->ind3, movV5, sizeof(float)*65500);			// Ind3 = 5-Period Moving Average of Volume
	memcpy (x->ind4, movV20, sizeof(float)*65500);			// Ind4 = 20-Period Moving Average of Volume
	memcpy (x->ind5, cg, sizeof(float)*65500);				// Ind5 = Congestion Breakout Indicator

	*(x->elIsValid) = x->firstvalid+67;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+67;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+67;
	*(x->csIsValid) = x->firstvalid+67;
	*(x->ind1FirstValid) = x->firstvalid+62;
	*(x->ind2FirstValid) = x->firstvalid+62;
	*(x->ind3FirstValid) = x->firstvalid+4;
	*(x->ind4FirstValid) = x->firstvalid+19;
	*(x->ind5FirstValid) = x->firstvalid+62;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.												// Return NULL for valid system.
}




//	**********************************
//	***** Consolidation Breakout *****
//	**********************************
/*
While this system uses John Bollinger's Bollinger Bands and Welles Wilder's
Average True Range indicator, it has no associations to the methods of either
one. It's based upon the Bollinger Band width compressing around the prices
until the distance between the upper and lower bands is less than 1 ¾ times the
1 period average true range. It then looks for a breakout in either direction
of the Bollinger Bands to capture the movement of the breakout. Once a position
is entered, it looks to cross the 20-period simple moving average to exit the
position

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 20-Period Simple Moving Average of Close
	Ind2 = Bollinger Band Top
	Ind3 = Bollinger Band Bottom
	Ind4 = 1-Period Average True Range
	
MetaStock Code:
	var1:=If(((BBandTop(C,20,S,2)-BBandBot(C,20,S,2))<(1.75*ATR(1))) AND
		Cross(H,BBandTop(C,20,S,2)),1,If(ATR(1) AND 
		Cross(BBandBot(C,20,S,2),L),-1,0));

	EL:=var1=1
	CL:= Cross(Mov(C,20,S),L)
	ES:= var1=-1
	CS:= Cross(H,Mov(C,20,S))
*/
int s21(struct datasys *x)									// Consolidation Breakout
{

	int i=0, j=0;
	int *var1;
	float movstor=0, stdstor=0, th=0, tl=0;
	float *mov20, *stdev, *atr1, *bbtop, *bbbot;

	var1=intarray1;											// Var1 array

	mov20=floatarray1;										// 20-Period Simple Moving Average of Close
	stdev=floatarray2;										// 20-Period Standard Deviation
	atr1=floatarray3;										// 1-Period Average True Range
	bbtop=floatarray4;										// Top Bollinger Band
	bbbot=floatarray5;										// Bottom Bollinger Band
	
	
	if((x->lastvalid - x->firstvalid)<22) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+19; i>=x->firstvalid; i--)			// 20-Period Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov20[x->firstvalid+19]=(float)(movstor/20.0);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-20];
		mov20[i] = (float)(movstor / 20.0);
	}

	
	for (i=x->firstvalid+19; i<=x->lastvalid; i++)			// 20-Period Standard Deviation of Close
	{
		stdstor=0.0;
		for (j=i-19; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->close[j]-mov20[i],2);
		}

		stdev[i]= (float)sqrt(stdstor/20.0);

		bbtop[i]=mov20[i]+(stdev[i]*(float)2.0);
		bbbot[i]=mov20[i]-(stdev[i]*(float)2.0);

	}
	
	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 1-Day Average True Range
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1[i]=th-tl;
	}

	for (i=x->firstvalid+21; i<=x->lastvalid; i++)			// Create Var1 Indicator
	{
		if(((bbtop[i]-bbbot[i])<(atr1[i]*1.75)) AND ((x->high[i]>bbtop[i]) AND (x->high[i-1]<bbtop[i-1])))
			var1[i]=1;
		else if(atr1[i]>0.0 AND((x->low[i]<bbbot[i]) AND (x->low[i-1]>bbbot[i-1])))
			var1[i]=-1;
		else var1[i]=0;
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+21; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (var1[i]==1)
			x->el[i]=1;

		if(mov20[i]>x->low[i] AND mov20[i-1]<x->low[i-1])
			x->cl[i]=1;
		
		if(var1[i]==-1)
			x->es[i]=1;

		if(mov20[i]<x->high[i] AND mov20[i-1]>x->high[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, mov20, sizeof(float)*65500);			// Ind1 = 20-Period Simple Moving Average of Close
	memcpy (x->ind2, bbtop, sizeof(float)*65500);			// Ind2 = Bollinger Band Top
	memcpy (x->ind3, bbbot, sizeof(float)*65500);			// Ind3 = Bollinger Band Bottom
	memcpy (x->ind4, atr1, sizeof(float)*65500);			// Ind4 = 1-Period Average True Range

	*(x->elIsValid) = x->firstvalid+21;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+21;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+21;
	*(x->csIsValid) = x->firstvalid+21;
	*(x->ind1FirstValid) = x->firstvalid+19;
	*(x->ind2FirstValid) = x->firstvalid+19;
	*(x->ind3FirstValid) = x->firstvalid+19;
	*(x->ind4FirstValid) = x->firstvalid+1;


	bzero(intarray1,sizeof(int)*65500);						// Clean arrays

	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.												// Return NULL for valid system.
}




//	*******************************
//	***** Cooper 1234 Pattern *****
//	*******************************
/*
This system is based on Jeff Cooper's 1-2-3-4's trading system. It establishes
that a trend exists and then waits for a pullback so that it can take a
position for a trend continuation. While the setup is the same as the 
1-2-3-4's, this system differs in that the entry is immediate (since the trend
has already been identified). Also, the trailing stop has been designated (for
long positions) by the price crossing below the previous days low (assuming
that the position moved in the favor of the trade). The reverse would be for
short positions.

While it can be very good at capturing profits on the majority of trades, no
real protection mechanism has been put into place if the trade immediately
moves against you. Stop-loss orders should be used to prevent the few failing
trades from removing all acquired profits.

Further Reading from Jeff Cooper:
	Hit and Run Trading: The Short-Term Stock Traders' Bible. M. Gordon 
		Publishing Group. 1996
	Hit and Run Trading II: Capturing Explosive Short-Term Moves in Stocks.
		M. Gordon Publishing Group. 1998
	Hit and Run Lessons: Mastering the Trading Strategies. M. Gordon
		Publishing Group. 1999
	The 5 Day Momentum Method. M. Gordon Publishing Group. 1999

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 14-Period Plus Directional Index
	Ind2 = 14-Period Minus Directional Index
	Ind3 = 14-PeriodAverage Directional Index
	
MetaStock Code:
	var1:=(ADX(14)>30) AND (PDI(14)>MDI(14)) AND ((L<Ref(L,-1) AND 
		Ref(L,-1)<Ref(L,-2) AND Ref(L,-2)<Ref(L,-3)) OR ((L<Ref(L,-1) AND
		Ref(L,-1)<Ref(L,-2) AND Ref(H,-2)<Ref(H,-3) AND Ref(L,-2)>Ref(L,-3)) OR
		(L<Ref(L,-1) AND Ref(L,-2)<Ref(L,-3) AND Ref(H,-1)<Ref(H,-2) AND 
		Ref(L,-1)>Ref(L,-2)) OR (Ref(L,-1)<Ref(L,-2) AND Ref(L,-2)<Ref(L,-3) AND
		H<Ref(H,-1) AND L>Ref(L,-1))));

	var2:=Cross(Ref(L,-1),L);

	var3:=(ADX(14)>30) AND (PDI(14)<MDI(14)) AND ((H>Ref(H,-1) AND
		Ref(H,-1)>Ref(H,-2) AND Ref(H,-2)>Ref(H,-3)) OR ((H>Ref(H,-1) AND
		Ref(H,-1)>Ref(H,-2) AND Ref(H,-2)<Ref(H,-3) AND Ref(L,-2)>Ref(L,-3)) OR
		(H>Ref(H,-1) AND Ref(H,-2)>Ref(H,-3) AND Ref(H,-1)<Ref(H,-2) AND
		Ref(L,-1)>Ref(L,-2)) OR (Ref(H,-1)>Ref(H,-2) AND Ref(H,-2)>Ref(H,-3) AND
		H<Ref(H,-1) AND L>Ref(L,-1))));

	var4:=Cross(H,Ref(H,-1));

	EL:= If(BarsSince(var1)<BarsSince(var2),1,0)=1
	CL:= If(BarsSince(var1)<BarsSince(var2),1,0)=0
	ES:= If(BarsSince(var3)<BarsSince(var4),1,0)=1
	CS:= If(BarsSince(var3)<BarsSince(var4),1,0)=0
*/
int s22(struct datasys *x)									// Cooper 1234 Pattern
{

	int i=0;
	int *var1, *var2, *var3, *var4, *bsvar1, *bsvar2, *bsvar3, *bsvar4;
	float th=0, tl=0, atr1=0, dmp=0, dmm=0, pdmcount=0, mdmcount=0, adxcount=0;
	float *atr14, *pdm, *mdm, *pdi, *mdi, *dx, *adx, *pdmfinal, *mdmfinal;

	var1=intarray1;											// Var1 Status (1 or 0) array
	var2=intarray2;											// Var2 Status (1 or 0) array
	var3=intarray3;											// Var3 Status (1 or 0) array
	var4=intarray4;											// Var4 Status (1 or 0) array
	bsvar1=intarray5;										// BarsSince Var1 Event array
	bsvar2=intarray6;										// BarsSince Var2 Event array
	bsvar3=intarray7;										// BarsSince Var3 Event array
	bsvar4=intarray8;										// BarsSince Var4 Event array

	atr14=floatarray1;										// 14-Period Average True Range array
	pdm=floatarray2;										// 14-Period Plus Directional Movement array
	mdm=floatarray3;										// 14-Period Minus Directional Movement array
	pdi=floatarray4;										// 14-Period Plus Directional Indicator array
	mdi=floatarray5;										// 14-Period Minus Directional Indicator array
	dx=floatarray6;											// 14-Period Directional Index array
	adx=floatarray7;										// 14-Period Average Directional Index array
	pdmfinal=floatarray8;									// 14-Period Plus Directional Movement (Final) array
	mdmfinal=floatarray9;									// 14-Period Minus Directional Movement (Final) array
	
	
	
	if((x->lastvalid - x->firstvalid)<28) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->firstvalid+14; i++)		// 14-Day Average True Range 1st calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=atr1+(th-tl);
	}
	atr14[x->firstvalid+14]=(atr1/(float)14.0);


	for (i=x->firstvalid+15; i<=x->lastvalid; i++)			// 14-Day Average True Range continuous calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=th-tl;
		atr14[i]=(((atr14[i-1]*(float)13.0)+atr1)/(float)14.0);
	}

	
	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 14-day PDI and MDI calculation
	{
		if (x->high[i]>x->high[i-1]) dmp=(x->high[i]-x->high[i-1]);
			else dmp=0;
		if (x->low[i]<x->low[i-1]) dmm=(x->low[i-1]-x->low[i]);
			else dmm=0;
		if(dmp>dmm) pdm[i]=dmp;
			else pdm[i]=0;
		if(dmp<dmm) mdm[i]=dmm;
			else mdm[i]=0;
	}

	for (i=x->firstvalid+1; i<=x->firstvalid+14; i++)
	{
		pdmcount=pdmcount+pdm[i];
		mdmcount=mdmcount+mdm[i];
	}

	pdmfinal[x->firstvalid+14]=pdmcount/(float)14.0;
	mdmfinal[x->firstvalid+14]=mdmcount/(float)14.0;

	for (i=x->firstvalid+15; i<=x->lastvalid; i++)
	{
		pdmfinal[i]=((pdmfinal[i-1]*13)+pdm[i])/(float)14.0;
		mdmfinal[i]=((mdmfinal[i-1]*13)+mdm[i])/(float)14.0;
	}

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)
	{
		pdi[i]=round((pdmfinal[i]/atr14[i])*(float)100.0);	// 14-day PDI
		mdi[i]=round((mdmfinal[i]/atr14[i])*(float)100.0);	// 14-day MDI
		dx[i]=round(((float)fabs(pdi[i]-mdi[i])/(pdi[i]+mdi[i]))*(float)100.0);	// Directional Index
	}


															// Average Directional Index Calculation
	for (i=x->firstvalid+14; i<=x->firstvalid+27; i++) adxcount=adxcount+dx[i];

	adx[x->firstvalid+27]=adxcount/(float)14.0;

	for (i=x->firstvalid+28; i<=x->lastvalid; i++)
	{
		adx[i]=round(((adx[i-1]*13)+dx[i])/(float)14.0);
	}


	for (i=x->firstvalid+27; i<=x->lastvalid; i++)			// Set up var 1-4 arrays, and set up BarsSince var 1-4 arrays
	{
		if(adx[i]>30.0 AND pdi[i]>mdi[i] AND
			((x->low[i]<x->low[i-1] AND x->low[i-1]<x->low[i-2] AND x->low[i-2]<x->low[i-3])	OR
			(x->low[i]<x->low[i-1] AND x->low[i-1]<x->low[i-2] AND x->high[i-2]<x->high[i-3] AND x->low[i-2]>x->low[i-3]) OR
			(x->low[i]<x->low[i-1] AND x->low[i-1]>x->low[i-2] AND x->low[i-2]<x->low[i-3] AND x->high[i-1]<x->high[i-2]) OR
			(x->low[i]>x->low[i-1] AND x->low[i-1]<x->low[i-2] AND x->low[i-2]<x->low[i-3] AND x->high[i]<x->high[i-1])))
			var1[i]=1;

		if (x->low[i]<x->low[i-1] AND x->low[i-1]>x->low[i-2]) 
			var2[i]=1;

		if(adx[i]>30.0 AND pdi[i]<mdi[i] AND
			((x->high[i]>x->high[i-1] AND x->high[i-1]>x->high[i-2] AND x->high[i-2]>x->high[i-3]) OR
			(x->high[i]>x->high[i-1] AND x->high[i-1]>x->high[i-2] AND x->low[i-2]>x->low[i-3] AND x->high[i-2]<x->high[i-3]) OR
			(x->high[i]>x->high[i-1] AND x->high[i-1]<x->high[i-2] AND x->high[i-2]>x->high[i-3] AND x->low[i-1]>x->low[i-2]) OR
			(x->high[i]<x->high[i-1] AND x->high[i-1]>x->high[i-2] AND x->high[i-2]>x->high[i-3] AND x->low[i]>x->low[i-1]))) 
			var3[i]=1;

		if (x->high[i]>x->high[i-1] AND x->high[i-1]<x->high[i-2])
			var4[i]=1;



		if (var1[i]==1) bsvar1[i] = 0;
		else bsvar1[i] = bsvar1[i-1]+1;

		if (var2[i]==1) bsvar2[i] = 0;
		else bsvar2[i] = bsvar2[i-1]+1;

		if (var3[i]==1) bsvar3[i] = 0;
		else bsvar3[i] = bsvar3[i-1]+1;

		if (var4[i]==1) bsvar4[i] = 0;
		else bsvar4[i] = bsvar4[i-1]+1;

	}



	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+27; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (bsvar1[i]<bsvar2[i]) x->el[i]=1;
			else x->el[i]=0;

		if(bsvar1[i]>=bsvar2[i])	x->cl[i]=1;
			else x->cl[i]=0;
		
		if(bsvar3[i]<bsvar4[i]) x->es[i]=1;
			else x->es[i]=0;

		if(bsvar3[i]>=bsvar4[i])
			x->cs[i]=1;
			else x->cs[i]=0;
	}

	memcpy (x->ind1, pdi, sizeof(float)*65500);			// Ind1 = 14-Period Plus Directional Index
	memcpy (x->ind2, mdi, sizeof(float)*65500);			// Ind2 = 14-Period Minus Directional Index
	memcpy (x->ind3, adx, sizeof(float)*65500);			// Ind3 = 14-PeriodAverage Directional Index

	*(x->elIsValid) = x->firstvalid+27;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+27;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+27;
	*(x->csIsValid) = x->firstvalid+27;
	*(x->ind1FirstValid) = x->firstvalid+14;
	*(x->ind2FirstValid) = x->firstvalid+14;
	*(x->ind3FirstValid) = x->firstvalid+27;


	bzero(intarray1,sizeof(int)*65500);						// Clean arrays
	bzero(intarray2,sizeof(int)*65500);
	bzero(intarray3,sizeof(int)*65500);
	bzero(intarray4,sizeof(int)*65500);
	bzero(intarray5,sizeof(int)*65500);
	bzero(intarray6,sizeof(int)*65500);
	bzero(intarray7,sizeof(int)*65500);
	bzero(intarray8,sizeof(int)*65500);

	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.												// Return NULL for valid system.
}




//	*****************************
//	***** Cycle Progression *****
//	*****************************
/*
This system is designed to anticipate short term swings in price activity. It
identifies when there is more downmoves than upmoves in the last 5 periods and
then enters a long position. It then exits and enters a short position on the
reverse condition.

This system is designed to capture very short-term cycles and should be used
with caution. While it is very good at capturing profits on the majority of
trades, no real protection mechanism has been put into place. Stop-loss orders
should be used to prevent the few failing trades from removing all acquired
profits.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Up Cycle Progression
	Ind2 = Down Cycle Progression
	
MetaStock Code:
	EL:= Sum(If(C>Ref(C,-1),1,0),5)<Sum(If(C<Ref(C,-1),1,0),5)
	ES:= Sum(If(C>Ref(C,-1),1,0),5)>Sum(If(C<Ref(C,-1),1,0),5)
*/
int s23(struct datasys *x)									// Cycle Progression
{
	int i=0;
	float up=0, down=0;										// Note: Float's used instead of int's because they are
	float *uparray, *downarray;								//	ultimately used in output indicator arrays.

	uparray=floatarray1;									// Up array
	downarray=floatarray2;									// Down array

	if((x->lastvalid - x->firstvalid)<6) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->firstvalid+5; i++)		// Create 5-period Cycle Progressions
	{
		if (x->close[i]>x->close[i-1]) up=up+1;
		if (x->close[i]<x->close[i-1]) down=down+1;
	}

	uparray[x->firstvalid+5]=up;
	downarray[x->firstvalid+5]=down;

	if (x->close[x->firstvalid+1]>x->close[x->firstvalid]) up=1;
	else up=0;

	if (x->close[x->firstvalid+1]<x->close[x->firstvalid]) down=1;
	else down=0;

	for (i=x->firstvalid+6; i<=x->lastvalid; i++)
	{
		if (x->close[i]>x->close[i-1])
		{
			uparray[i]=uparray[i-1]+1-up;
			downarray[i]=downarray[i-1]-down;
		}
		if (x->close[i]<x->close[i-1])
		{
			uparray[i]=uparray[i-1]-up;
			downarray[i]=downarray[i-1]+1-down;
		}
		if (x->close[i]==x->close[i-1])
		{
			uparray[i]=uparray[i-1]-up;
			downarray[i]=downarray[i-1]-down;
		}

		if (x->close[i-4]>x->close[i-5]) up=1;
		else up=0;

		if (x->close[i-4]<x->close[i-5]) down=1;
		else down=0;
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+5; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(uparray[i]<downarray[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(uparray[i]>downarray[i])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, uparray, sizeof(float)*65500);			// Ind1 = Up Cycle Progression
	memcpy (x->ind2, downarray, sizeof(float)*65500);		// Ind2 = Down Cycle Progression

	*(x->elIsValid) = x->firstvalid+5;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+5;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+5;
	*(x->csIsValid) = x->firstvalid+5;
	*(x->ind1FirstValid) = x->firstvalid+5;
	*(x->ind2FirstValid) = x->firstvalid+5;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}



//	******************************
//	***** Day Pattern System *****
//	******************************
/*
This system was not designed to be traded as much as it was an example of how
to write a trading system based upon specific conditions for a day of the week.
However, the trading results have made it a viable trading system overall.
This type of system would be used with a security that would exhibit a specific
known behavior for a day of the week, like on a Friday or a Monday. It would
also be a good system for tracking down a security that exhibits this type of
behavior (by running the performance exploration).

The rules for this specific system are fairly simple: If the last trading day
was Friday, and Friday closed higher than both the opening of Thursday and the
opening of the previous Monday, then buy today (assuming that today is Monday).
Exit the opening of the next trading day (Tuesday or Wednesday). This system
would be a long only system, and would be tested on the opening prices with no
trade delay. It can also be adjusted for different days as well as different
entry conditions.

Trade Type:
	Long Positions Only

Indicator Output: 
	None
	
MetaStock Code:
	EL:=DayOfWeek()=1 AND Ref(DayOfWeek(),-1)=5 AND Ref(C,-1)>Ref(O,-5) AND
		Ref(C,-1)>Ref(O,-2)

	CL:= DayOfWeek()=2 OR DayOfWeek()=3
*/
int s24(struct datasys *x)									// Day Pattern System
{
	int i=0;

	if((x->lastvalid - x->firstvalid)<7) return 2;			// Return 2 if not enough data
															//	to calculate.


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+6; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(dow(x->date[i].lDate)==1 AND dow(x->date[i-1].lDate)==5 AND
			x->close[i-1]>x->open[i-5] AND x->close[i-1]>x->open[i-2])
		{
			x->el[i]=1;
		}

		if(dow(x->date[i].lDate)==2 OR dow(x->date[i].lDate)==3)
		{
			x->cl[i]=1;
		}
	}

	*(x->elIsValid) = x->firstvalid+6;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+6;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+6;
	*(x->csIsValid) = x->firstvalid+6;

	return 0;												// Return NULL for valid system.
}




//	*************************************
//	***** Derivative Moving Average *****
//	*************************************
/*
The original Derivative Moving Average System was developed by Adam White and
published in the June 1996 issue of Technical Analysis of Stocks and
Commodities magazine. 

The original system enters when a 28-period moving average reaches it's 4-day
low and then turns up. The exit occurs when the Trade Analysis Index (TAI)
reaches below a level of .4.

This system has been modified from the original by exiting when the TAI crosses
below 4 instead of .4. This allows it to exit a position sooner and typically
results in an increase in profit retention.

Trade Type:
	Long Positions Only

Indicator Output: 
	Ind1 = 28-Period Simple Moving Average of Close
	Ind2 = 4-Period Lowest Low Value of Moving Average
	Ind3 = TAI Indicator (Derivative Moving Average)
	
MetaStock Code:
	tai:=((HHV(Mov(C,28,S),5)-LLV(Mov(C,28,S),5))/C)*100;

	EL:= Ref(Mov(C,28,S),-1)=LLV(Mov(C,28,S),4)
	CL:=tai<4 AND Ref(tai,-1)>=4
*/
int s25(struct datasys *x)									// Derivative Moving Average
{
	int i=0, j=0;
	float movstor=0, hhv=0, llv=0;
	float *hhv5, *llv5, *llv4, *mov28, *tai;

	hhv5=floatarray1;										// 5-Period Highest High Value of Moving Average
	llv5=floatarray2;										// 5-Period Lowest Low Value of Moving Average
	llv4=floatarray3;										// 4-Period Lowest Low Value of Moving Average
	mov28=floatarray4;										// 28-Period Simple Moving Average of Close
	tai=floatarray5;										// tai Indicator


	if((x->lastvalid - x->firstvalid)<32) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+27; i>=x->firstvalid; i--)			// 28-Period Simple Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov28[x->firstvalid+27]=(float)(movstor/28.0);

	for (i=x->firstvalid+28; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-28];
		mov28[i] = (float)(movstor / 28.0);
	}


	for (i=x->firstvalid+31; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 5-day levels of Moving Average.
		for (j=i-3; j<=i; j++)
		{
			if (j==i-3)
			{
				hhv=mov28[j-1];
				llv=mov28[j-1];
			}

			if(mov28[j]>hhv) hhv=mov28[j];
			if(mov28[j]<llv) llv=mov28[j];
		}

		hhv5[i]=hhv;
		llv5[i]=llv;

		tai[i]=((hhv5[i]-llv5[i])/x->close[i])*(float)100.0;// Set up "tai" indicator
	}

	llv=0;

	for (i=x->firstvalid+30; i<=x->lastvalid; i++)			// Set up LLV array based
	{														//	on 4-day levels of Moving Average.
		for (j=i-2; j<=i; j++)
		{
			if (j==i-2)
			{

				llv=mov28[j-1];
			}
			if(mov28[j]<llv) llv=mov28[j];
		}

		llv4[i]=llv;
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+31; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(mov28[i-1]==llv4[i])
		{
			x->el[i]=1;
		}

		if(tai[i]<4 AND tai[i-1]>=4)
		{
			x->cl[i]=1;
		}

	}

	memcpy (x->ind1, mov28, sizeof(float)*65500);			// Ind1 = 28-Period Simple Moving Average of Close
	memcpy (x->ind2, llv4, sizeof(float)*65500);			// Ind2 = 4-Period Lowest Low Value of Moving Average
	memcpy (x->ind3, tai, sizeof(float)*65500);				// Ind3 = TAI Indicator (Derivative Moving Average)


	*(x->elIsValid) = x->firstvalid+31;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+31;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+31;
	*(x->csIsValid) = x->firstvalid+31;
	*(x->ind1FirstValid) = x->firstvalid+27;
	*(x->ind2FirstValid) = x->firstvalid+30;
	*(x->ind3FirstValid) = x->firstvalid+31;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	********************************
//	***** Detrended EMA System *****
//	********************************
/*
While most methods of detrending a moving average involve shifting the data
series backwards, John F. Ehlers implemented a method that shows the detrended
moving average up through the current price data. These detrended moving
averages were originally introduced in the July 2000 issue of Technical
Analysis of Stocks and Commodities magazine, and are used here to create a
trading system. The system follows a basic moving average crossover design,
using a 55-period detrended moving average crossing a 55-period detrended
moving average of itself. Since the detrending factor can bring the two moving
averages so close together for long periods of time, the system also requires
that the two moving averages be greater than 5% apart in the direction of the
trade to enter.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Var3 Detrended Indicator
	Ind2 = Var6 Detrended Indicator
	
MetaStock Code:
	Var1:= Mov(CLOSE,55,E);
	Var2:= Mov(var1,55,E);
	Var3:= (var1-var2)+var1;
	Var4:= Mov(var3,55,E);
	Var5:= Mov(var4,55,E);
	Var6:= (var4-var5)+var4;
	Var7:=var3/var6;

	EL:=Var3>var6 AND var7>1.05
	CL:= Var3<var6 AND var7<.95
	ES:= Var3<var6 AND var7<.95
	CS:= Var3>var6 AND var7>1.05
*/
int s26(struct datasys *x)									// Detrended EMA System
{
	int i=0;
	float movstor=0;
	float *var1, *var2, *var3, *var4, *var5, *var6, *var7;

	var1=floatarray1;										// Var1 array (55-Period Exponential Moving Average of Close)
	var2=floatarray2;										// Var2 array (55-Period Exponential Moving Average of Var1)
	var3=floatarray3;										// Var3 array ( (Var1-Var2)+Var1 )
	var4=floatarray4;										// Var4 array (55-Period Exponential Moving Average of Var3)
	var5=floatarray5;										// Var5 array (55-Period Exponential Moving Average of Var4)
	var6=floatarray6;										// Var6 array ( (Var4-Var5)+Var4 )
	var7=floatarray7;										// Var7 array ( Var3/Var6 )


	if((x->lastvalid - x->firstvalid)<217) return 2;		// Return 2 if not enough data
															//	to calculate.


	var1[x->firstvalid]=x->close[x->firstvalid];			// 55-Period Exponential Moving Average of Close

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		var1[i] = (float)(x->close[i] * (2.0/56.0)) + (float)(var1[i-1] * (1.0-(2.0/56.0)));
	}

	var2[x->firstvalid+54]=var1[x->firstvalid+54];			// 55-Period Exponential Moving Average of Var1

	for (i=x->firstvalid+55; i<=x->lastvalid; i++)
	{
		var2[i] = (float)(var1[i] * (2.0/56.0)) + (float)(var2[i-1] * (1.0-(2.0/56.0)));
	}

	for (i=x->firstvalid+108; i<=x->lastvalid; i++)			// (Var1-Var2)+Var1
	{
		var3[i]=(var1[i]-var2[i])+var1[i];
	}

	var4[x->firstvalid+108]=var3[x->firstvalid+108];		// 55-Period Exponential Moving Average of Var3

	for (i=x->firstvalid+109; i<=x->lastvalid; i++)
	{
		var4[i] = (float)(var3[i] * (2.0/56.0)) + (float)(var4[i-1] * (1.0-(2.0/56.0)));
	}	

	var5[x->firstvalid+162]=var4[x->firstvalid+162];		// 55-Period Exponential Moving Average of Var4

	for (i=x->firstvalid+163; i<=x->lastvalid; i++)
	{
		var5[i] = (float)(var4[i] * (2.0/56.0)) + (float)(var5[i-1] * (1.0-(2.0/56.0)));
	}	

	for (i=x->firstvalid+216; i<=x->lastvalid; i++)
	{
		var6[i]=(var4[i]-var5[i])+var4[i];					// (Var4-Var5)+Var4
		var7[i]=var3[i]/var6[i];							// Var3/Var6
	}



	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+216; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(var3[i]>var6[i] AND var7[i]>1.05)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if(var3[i]<var6[i] AND var7[i]<.95)
		{
			x->cl[i]=1;
			x->es[i]=1;
		}

	}

	memcpy (x->ind1, var3, sizeof(float)*65500);			// Ind1 = Var3 Detrended Indicator
	memcpy (x->ind2, var6, sizeof(float)*65500);			// Ind2 = Var6 Detrended Indicator

	*(x->elIsValid) = x->firstvalid+216;					// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+216;					//	for each output array.
	*(x->esIsValid) = x->firstvalid+216;
	*(x->csIsValid) = x->firstvalid+216;
	*(x->ind1FirstValid) = x->firstvalid+108;
	*(x->ind2FirstValid) = x->firstvalid+216;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}







//	**************************************
//	***** Directional Movement/SAR 1 *****
//	**************************************
/*
This system is based upon indicators developed by Welles Wilder. It uses the
Average Directional Movement Index, the Plus Directional Indicator, the Minus
Directional Indicator, and the Parabolic SAR indicator. The Plus Directional
Indicator and the Minus Directional Indicator are used to determine the
significant direction of price movement, and the ADX is used to determine the
strength of a trend. The Parabolic SAR, which is typically used as a Stop and
Reverse system, is only used as a trailing stop or a confirmation for entry but
not as the actual entry signal.

This system requires that a positive trend be lightly established for entering,
and exits when the price crosses below the Parabolic SAR. The opposite would be
the rules for a short position. Very few trades with a usually low drawdown.
Little profit produced, but can be somewhat safer than other trading systems
because of the typically low drawdown.

Further Reading from Welles Wilder:
	New Concepts in Technical Trading Systems.  Trend research. 1978
	The Adam Theory of Markets or What Matters Is Profit. Trend Research. 1987

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Not Yet Available
	
MetaStock Code:
	EL:= Cross(ADX(18),15) AND PDI(18)>MDI(18)
	CL:= C<SAR(.02,.2)
	ES:= Cross(ADX(18),15) AND PDI(18)<MDI(18)
	CS:= C>SAR(.02,.2)
*/
int s27(struct datasys *x)									// Directional Movement/SAR 1
{

//	Set up new memory usage here.!!!***

	int i, count=0, prelimcount=0;
	int *direction, *test;
	float high=0, low=0, acc=(float).02, maxaf=(float).2, af=0;
	float *sar;


	if((x->lastvalid - x->firstvalid)<18) return 2;			// Return 2 if not enough data
															//	to calculate.

	sar = (float *) calloc (65500,sizeof(float));			// Create Arrays
	direction = (int *) calloc (65500,sizeof(int));
	test = (int *) calloc (65500,sizeof(int));

	if(sar==NULL OR direction==NULL OR test==NULL)
	{
		free(sar);
		free(direction);
		free (test);

		return 1;
	}

/*


	high=x->high[x->firstvalid];
	low=x->low[x->firstvalid];
	test[x->firstvalid]=0;
	sar[x->firstvalid]=low;

	

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if (test[i-1]==0)
		{












	test[x->firstvalid]=1;

	do
	{
		if (x->high[x->firstvalid+1+prelimcount]>x->high[x->firstvalid+prelimcount])
			high=x->high[x->firstvalid+1+prelimcount];

		if (x->low[x->firstvalid+1+prelimcount]<x->low[x->firstvalid+prelimcount])
			low=x->low[x->firstvalid+1+prelimcount];

		if (x->low[x->firstvalid+1+prelimcount]<x->low[x->firstvalid+prelimcount] AND
			x->low[x->firstvalid+1+prelimcount]<x->low[x->firstvalid+prelimcount])
		{
			high=0;
			low=0;
		}

		if(high>0 AND low==0)
			direction[x->firstvalid+1+prelimcount]=-1;

		if(high==0 AND low>0)
			direction[x->firstvalid+1+prelimcount]=1;

		if(direction[x->firstvalid+1+prelimcount]==0) prelimcount=prelimcount+1;
		
		count=count+1;

		test[x->firstvalid+prelimcount+1]=1;

	}
	while (direction[x->firstvalid+1+prelimcount]==0);



	for (i=x->firstvalid+1+prelimcount; i<=x->lastvalid; i++)
	{
		if(direction[i-1]==0) direction[i-1]=1;
		if(direction[i-1]==1)
		{
			if(direction[i]==1 AND (direction[i-1]==-1 OR  direction[i-1]==0))
			{
				sar[i]=low;
				af=0;
				high=x->high[i];
			}
			else
			{
				if(x->high[i]>x->high[i-1])
					af=__min(af+acc,maxaf);
				sar[i]=((x->high[i-1]-sar[i-1])*af)+sar[i-1];
				high=__max(high,x->high[i]);
			}

			if(x->low[i]<sar[i-1]) direction[i]=-1;
		}

		if(direction[i-1]==-1)
		{
			if(direction[i]==-1 AND (direction[i-1]==1 OR  direction[i-1]==0))
			{
				sar[i]=high;
				af=0;
				low=x->low[i];
			}
			else
			{
				if(x->low[i]<x->low[i-1])
					af=__min(af+acc,maxaf);
				sar[i]=sar[i-1]-((sar[i-1]-x->low[i-1])*af);
				low=__min(low,x->low[i]);
			}

			if(x->high[i]>sar[i-1]) direction[i]=1;
		}

		test[i]=i;

	}

*/











	// *** For Testing Output Indicator Only ***
	for (i=x->firstvalid; i<=x->lastvalid; i++) x->ind1[i]=(float)direction[i];							
	*(x->ind1FirstValid) = x->firstvalid;
	// *** End Indicator Test ***



	free(sar);
	free(direction);
	free(test);

	return 0;

	
/*	
	


	for (i=x->firstvalid; i<=x->firstvalid+216; i++)		// Set up zeros for beginning
	{														//	of output arrays.
		x->el[i]=0;
		x->cl[i]=0;
		x->es[i]=0;
		x->cs[i]=0;
		x->cl[i+1]=0;
		x->cs[i+1]=0;
	}

	for (i=x->firstvalid+216; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(var3[i]>var6[i] AND var7[i]>1.05)
		{
			x->el[i]=1;
			x->cl[i]=0;
			x->es[i]=0;
			x->cs[i]=1;
		}

		if(var3[i]<var6[i] AND var7[i]<.95)
		{
			x->el[i]=0;
			x->cl[i]=1;
			x->es[i]=1;
			x->cs[i]=0;
		}

	}

	*(x->elIsValid) = x->firstvalid+216;					// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+216;					//	for each output array.
	*(x->esIsValid) = x->firstvalid+216;
	*(x->csIsValid) = x->firstvalid+216;
//	*(x->ind1FirstValid) = x->firstvalid+5;


//	***************************************************
//	***** Put vars here after choosing which ones *****
//	***************************************************


	// *** For Testing Output Indicator Only ***
	for (i=x->firstvalid+216; i<=x->lastvalid; i++) x->ind1[i]=var7[i];							
	*(x->ind1FirstValid) = x->firstvalid+216;
	// *** End Indicator Test ***

	free(var1);												// Free memory.
	free(var2);
	free(var3);
	free(var4);
	free(var5);
	free(var6);
	free(var7);

	return 0;												// Return NULL for valid system.



*/
}




//	**************************************
//	***** Directional Movement/SAR 2 *****
//	**************************************
/*
This system is based upon indicators developed by Welles Wilder. It uses the
Average Directional Movement Index, the Plus Directional Indicator, the Minus
Directional Indicator, and the Parabolic SAR indicator. The Plus Directional
Indicator and the Minus Directional Indicator are used to determine the
significant direction of price movement, and the ADX is used to determine the
strength of a trend. The Parabolic SAR, which is typically used as a Stop and
Reverse system, is only used as a trailing stop or a confirmation for entry but
not as the actual entry signal.

This system requires that a positive trend be starting and the price be above
the Parabolic SAR to enter, and exits when the price crosses below the
Parabolic SAR. The opposite would be the rules for a short position. It has a
fair amount of trades with a lower drawdown than many other types of systems.

Further Reading from Welles Wilder:
	New Concepts in Technical Trading Systems.  Trend research. 1978
	The Adam Theory of Markets or What Matters Is Profit. Trend Research. 1987

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Not Yet Available
	
MetaStock Code:
	EL:= ADX(18)>Ref(ADX(18),-1) AND PDI(18)>MDI(18) AND C>SAR(.02,.2)
	CL:= C<SAR(.02,.2)
	ES:= ADX(18)>Ref(ADX(18),-1) AND PDI(18)<MDI(18) AND C<SAR(.02,.2)
	CS:= C>SAR(.02,.2)
*/


//	Still needs to be encoded...

int s28(struct datasys *x)									// Directional Movement/SAR 2
{
	return 0;
}



//	***************************
//	***** Division System *****
//	***************************
/*
This simple system creates a smooth indicator by dividing a 3-month linear
regression by the closing prices of the security. This indicator follows the
general direction of the prices. The system enters when the indicator is above
a 13-period moving average of itself. It then exits and takes a short position
when it crosses below that same moving average. Since the indicator is so
smooth, there typically isn't much whipsawing. While in a trend, this system
usually has excellent results.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 63-Period Linear Regression Slope Divided by Close (Var1)
	Ind2 = 13-Period Simple Moving Average of Var1
	
MetaStock Code:
	var1:=LinRegSlope(C,63)/C;

	EL:=var1>Mov(var1,13,S)
	ES:=var1<Mov(var1,13,S)
*/
int s29(struct datasys *x)									// Division System
{
	int i=0, j=0;
	float sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0, movstor=0;
	float *lrslope, *var1, *mov13;

	lrslope=floatarray1;									// 63-Period Linear Regression Slope
	var1=floatarray2;										// Linear Regression Slope Divided by Close
	mov13=floatarray3;										// 13-Period Simple Moving Average of Var1
	

	if((x->lastvalid - x->firstvalid)<75) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+62; i<=x->lastvalid; i++)			// 63-Period Linear Regression Slope
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-62; j<=i; j++)
		{
			sum1=sum1+((float)j*x->close[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->close[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+62)
			{
				movc=movc+x->close[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+62)
		{
			movc=movc-x->close[i-63]+x->close[i];
			movcum=movcum-(i-63)+i;
		}

		lrslope[i]=
			(sum1-((sum2*sum3)/63))/(sum4-(((float)pow(sum2,2))/(float)63));

		var1[i]=lrslope[i]/x->close[i];						// Linear Regression Slope Divided by Close
	}

	for (i=x->firstvalid+74; i>=x->firstvalid+62; i--)		// 13-Period Moving Average of Var1
	{
		movstor=movstor+var1[i];
	}

	mov13[x->firstvalid+74]=(float)(movstor/13.0);

	for (i=x->firstvalid+75; i<=x->lastvalid; i++)
	{
		movstor = movstor + var1[i] - var1[i-13];
		mov13[i] = (float)(movstor / 13.0);
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+74; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (var1[i]>mov13[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}
		if (var1[i]<mov13[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 63-Period Linear Regression Slope Divided by Close
	memcpy (x->ind2, mov13, sizeof(float)*65500);			// Ind2 = 13-Period Simple Moving Average of Var1

	*(x->elIsValid) = x->firstvalid+74;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+74;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+74;
	*(x->csIsValid) = x->firstvalid+74;
	*(x->ind1FirstValid) = x->firstvalid+62;
	*(x->ind2FirstValid) = x->firstvalid+74;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);


	return 0;												// Return NULL for valid system.
}



//	******************************
//	***** DNS Trading System *****
//	******************************
/*
The DNS (Dave's New System) indicator was designed by Dave  R. Evans and is
based on 'confirmation' of indicators (looking for different indicators
pointing to the same signal or to be moving in the same direction). While not
technically a binary indicator, it sums the various conditions of the
indicators to create a composite value between 0 and 8.

Unlike most other systems, this one is designed as a 'contrarian' system.
Rather than take a long position when all of the indicators suggest a bullish
position should be taken, the system takes a short position. As soon as all of
the indicators agree on a bearish condition, a long position is taken. This is
similar to a sentiment indicator is that typically when all parties agree that
it is a bullish moment, all the bull traders are already in the market and all
that is left to take is a bearish position. The reverse would be true to take a
bullish position.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Not Yet Available
	
MetaStock Code:
	var1:=If(SAR(.02,.2)<C,1,0)+
		If((Mov(C,5,E)>Mov(C,13,E)),1,0)+
		If((Mov(C,13,E)>Mov(C,40,E)),1,0)+
		If((Mov(C,8,E)-Mov(C,17,E))>(Mov((Mov(C,8,E)-Mov(C,17,E)),9,E)),1,0)+
		If((Mov(C,50,S)-Ref(Mov(C,50,S),-15)>0),1,0)+
		If((Mov(ROC(C,12,%),3,E)>=-6 OR ROC(C,12,%)>0),1,0)+
		If(OBV()>Mov(OBV(),40,S),1,0)+
		If((V>Mov(V,120,S)),1,0);

	EL:=var1=0
	ES:= var1=8
*/


//	Still needs to be encoded...

int s30(struct datasys *x)									// DNS Trading System
{
	return 0;
}




//	************************************
//	***** Dynamic Momentum Index 1 *****
//	************************************
/*
The Dynamic Momentum Index is basically an RSI that automatically adjusts its
own time period length as needed. The Dynamic Momentum Index was developed by
Tushar Chande and Stanley Kroll. 

For a long position, the system enters by crossing below the 30 mark. However,
rather than a typical exit rising above 70 and crossing below, a different
approach is taken. If at any point in the trade the price crosses below the
5-period simple moving average (acting as a trailing stop), then the position
is exited. The problem with this is that when the entry signal is given, the
price is typically already below the 5-period simple moving average, so a
protective measure is needed that exits the position before too many losses
can occur but also gives enough time to cross above the moving average setting
up a potential exit signal. This is accomplished by doing a price check. If in
the third day of the position it is at a loss, then the position is exited.

Further Reading from Tushar Chande and Stanley Kroll:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators. (Wiley Finance Editions) John Wiley and Sons, Inc. 1994

Further Reading from Tushar Chande:
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Further Reading from Stanley Kroll
	The Business One Irwin Guide to the Futures Markets. Irwin Professional
		Publishing. 1992
	The Professional Commodity Trader. Traders Press. 1995

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Not Yet Available
	
MetaStock Code:
	EL:=Cross(30,DMI(C))
	CL:= Cross(Mov(C,5,S),C) OR (BarsSince(Cross(30,DMI(C)))=3 AND
		ROC(C,3,%)<0)
	ES:= Cross(DMI(C),70)
	CS:= Cross(C,Mov(C,5,S)) OR (BarsSince(Cross(DMI(C),70))=3 AND
		ROC(C,3,%)>0)
*/

int s31(struct datasys *x)									// DNS Trading System
{

	int i=0, j=0;
	int *stdevind;
	float ups=0, downs=0, movstor=0, stdstor=0;
	float *stdev,  *dmi, *mov5, *mov10;

	stdevind=intarray1;										// stdevind (Not working yet)

	stdev=floatarray1;										// 5-Period Standard Deviation of Close
	dmi=floatarray2;										// Dynamic Momentum Index (Not working yet)
	mov5=floatarray3;										// 5-Period Simple Moving Average of Close
	mov10=floatarray4;										// 10-Period Simple Moving Average of Standard Deviation



	if((x->lastvalid - x->firstvalid)<14) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+4; i>=x->firstvalid; i--)			// 5-Period Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov5[x->firstvalid+4]=(float)(movstor/5.0);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-5];
		mov5[i] = (float)(movstor / 5.0);
	}

	
	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// 5-Period Standard Deviation of Close
	{
		stdstor=0.0;
		for (j=i-4; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->close[j]-mov5[i],2);
		}

		stdev[i]= (float)sqrt(stdstor/5.0);
	}


	movstor=0;

	for (i=x->firstvalid+13; i>=x->firstvalid+4; i--)		// 10-Period Moving Average of Standard Deviation
	{
		movstor=movstor+stdev[i];
	}

	mov10[x->firstvalid+13]=(float)(movstor/10.0);

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)
	{
		movstor = movstor + stdev[i] - stdev[i-10];
		mov10[i] = (float)(movstor / 10.0);

		stdevind[i]=max(5,__min(30,(int)(14/(stdev[i]/mov10[i]))));
	}



//	*****************************************
//	Everything above works. DMI below doesn't
//	*****************************************
	for (i=x->firstvalid+29; i<=x->lastvalid; i++)			// Dynamic Momentum Index
	{
		ups=0;
		downs=0;

		for(j=i; j>=(i-stdevind[i]+1); j--)
		{
			if (x->close[j]>x->close[j-1]) ups=ups+(x->close[j]-x->close[j-1]);
			if (x->close[j]<x->close[j-1]) downs=downs+(x->close[j-1]-x->close[j]);
		}

		ups=__max((float).0001,ups);
		downs=__max((float).0001,downs);

		dmi[i]=100-(100/(1+(ups/downs)));
	}

	bzero(intarray1,sizeof(int)*65500);						// Clean arrays
	
	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;
}




//	************************************
//	***** Dynamic Momentum Index 2 *****
//	************************************
/*
The Dynamic Momentum Index is basically an RSI that automatically adjusts its
own time period length as needed. The Dynamic Momentum Index was developed by
Tushar Chande and Stanley Kroll. 

This system is of a reversal type. It enters a long position when the DMI
crosses above 20, moving out of an oversold condition. It then exits the long
position when the DMI rises and then crosses below 80, moving out of an
overbought condition. The reverse is for short positions.

Further Reading from Tushar Chande and Stanley Kroll:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators. (Wiley Finance Editions) John Wiley and Sons, Inc. 1994

Further Reading from Tushar Chande:
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Further Reading from Stanley Kroll
	The Business One Irwin Guide to the Futures Markets. Irwin Professional
		Publishing. 1992
	The Professional Commodity Trader. Traders Press. 1995

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Not Yet Available
	
MetaStock Code:
	EL:= Cross(DMI(C),20)
	ES:= Cross(80,DMI(C))
*/

//	Still needs to be encoded...

int s32(struct datasys *x)									// Dynamic Momentum Index 2
{
	return 0;
}




//	************************************
//	***** Dynamic Momentum Index 3 *****
//	************************************
/*
The Dynamic Momentum Index is basically an RSI that automatically adjusts its
own time period length as needed. The Dynamic Momentum Index was developed by
Tushar Chande and Stanley Kroll. 

This system enters long when the DMI crosses above 30, moving out of a less
restrictive oversold condition. It then exits the long position when the DMI
rises and then crosses below 80, moving out of an overbought condition, but
will also exit if the price was above the 200-period moving average when
entered and then crosses below the 200-period moving average. The reverse is
for the short positions, except that 80 is used for an overbought condition
instead of 70.

Further Reading from Tushar Chande and Stanley Kroll:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators. (Wiley Finance Editions) John Wiley and Sons, Inc. 1994

Further Reading from Tushar Chande:
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Further Reading from Stanley Kroll
	The Business One Irwin Guide to the Futures Markets. Irwin Professional
		Publishing. 1992
	The Professional Commodity Trader. Traders Press. 1995

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Not Yet Available
	
MetaStock Code:
	EL:= Cross(DMI(C),30)
	CL:= Cross(80,DMI(C)) OR If(ValueWhen(1,Cross(DMI(C),30),C)>Mov(C,200,S),
		Cross(Mov(C,200,S),C),0)
	ES:= Cross(80,DMI(C))
	CS:= Cross(DMI(C),30) OR If(ValueWhen(1,Cross(80,DMI(C)),C)<Mov(C,200,S),
		Cross(C,Mov(C,200,S)),0)
*/


//	Still needs to be encoded...

int s33(struct datasys *x)									// Dynamic Momentum Index 3
{
	return 0;
}




//	***************************************
//	***** Elliott Oscillator System 1 *****
//	***************************************
/*
Tom Joseph originated the concept of an 'Elliott Oscillator'. He used a
5-period moving average and subtracted a 35-period moving average from it to
create a 5/35 MACD oscillator. This was then used to analyze Elliott Waves. 
Later, Bill Williams came along and modified it by using a 5/34 MACD oscillator
so as to retain a Fibonacci relationship. He also started using the midpoint of
a bar instead of the closing prices. These systems use the Bill Williams
version (which he calls the Awesome Oscillator).

This system looks for momentum by analyzing the troughs in the 5/34 MACD. To
enter long, it identifies 2 troughs, the more recent one being a higher value
than the previous one. The peak in between the two troughs also needs to be
below zero. This insures that all of the oscillator action has been below zero.
As the oscillator starts to rise, a long position is taken. The system exits at
the occurrence of the first peak of the 5/34 MACD. The reverse of all of these
conditions is for a short position.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 5-Period Moving Average of Midpoint
	Ind2 = 34-Period Moving Average of Midpoint
	Ind3 = Elliott Oscillator (Mov5 - Mov34)
	
MetaStock Code:
	var1:=Mov((H+L)/2,5,S)-Mov((H+L)/2,34,S);
	var2:=var1>Ref(var1,-1) AND Ref(var1,-1)<Ref(var1,-2);
	var3:=Mov((H+L)/2,5,S)-Mov((H+L)/2,34,S);
	var4:=var3<Ref(var3,-1) AND Ref(var3,-1)>Ref(var3,-2);

	EL:=ValueWhen(1,var2,Ref(var1,-1))>ValueWhen(2,var2,Ref(var1,-1)) AND
		BarsSince(var2)<BarsSince(var4) AND var1<0 AND 
		ValueWhen(1,var4,Ref(var3,-1))<0
	CL:= var4
	ES:= ValueWhen(1,var4,Ref(var3,-1))<ValueWhen(2,var4,Ref(var3,-1)) AND
		BarsSince(var4)<BarsSince(var2) AND var3>0 AND 
		ValueWhen(1,var2,Ref(var1,-1))>0
	CS:= var2
*/
int s34(struct datasys *x)									// Elliott Oscillator System 1
{
	int i;
	int *var2, *var4, *bsvar2, *bsvar4;
	float movstor=0;
	float *mov5, *mov34, *var1, *var3;
	float *var2_vw1, *var2_vw2, *var4_vw1, *var4_vw2;

	var2=intarray1;											// Signal array for Up Fractal of Var1 (technically not used)
	var4=intarray2;											// Signal array for Down Fractal of Var3 (technically not used)
	bsvar2=intarray3;										// BarsSince Var2 Event
	bsvar4=intarray4;										// BarsSince Var4 Event

	mov5=floatarray1;										// 5-Period Moving Average of Midpoint
	mov34=floatarray2;										// 34-Period Moving Average of Midpoint
	var1=floatarray3;										// Mov5 - Mov34
	var3=floatarray4;										// Mov5 - Mov34
	var2_vw1=floatarray5;									// First (most recent) ValueWhen of Var1[i-1] when Var2 occurs
	var2_vw2=floatarray6;									// Second (next most recent) ValueWhen of Var1[i-1] when Var2 occurs
	var4_vw1=floatarray7;									// First (most recent) ValueWhen of Var3[i-1] when Var4 occurs
	var4_vw2=floatarray8;									// Second (next most recent) ValueWhen of Var3[i-1] when Var4 occurs


	if((x->lastvalid - x->firstvalid)<36) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+4; i>=x->firstvalid; i--)			// 5-Period Moving Average of Midpoint
	{
		movstor=movstor+((x->high[i]+x->low[i])/2);
	}

	mov5[x->firstvalid+4]=(float)(movstor/5.0);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)
	{
		movstor = movstor + ((x->high[i]+x->low[i])/2) - ((x->high[i-5]+x->low[i-5])/2);
		mov5[i] = (float)(movstor / 5.0);
	}

	movstor=0;

	for (i=x->firstvalid+33; i>=x->firstvalid; i--)			// 34-Period Moving Average of Midpoint
	{
		movstor=movstor+((x->high[i]+x->low[i])/2);
	}

	mov34[x->firstvalid+33]=(float)(movstor/34.0);

	for (i=x->firstvalid+34; i<=x->lastvalid; i++)
	{
		movstor = movstor + ((x->high[i]+x->low[i])/2) - ((x->high[i-34]+x->low[i-34])/2);
		mov34[i] = (float)(movstor / 34.0);
	}

															// Create Var1-Var4 Arrays
	var1[x->firstvalid+33]=mov5[x->firstvalid+33]-mov34[x->firstvalid+33];
	var1[x->firstvalid+34]=mov5[x->firstvalid+34]-mov34[x->firstvalid+34];
	var3[x->firstvalid+33]=mov5[x->firstvalid+33]-mov34[x->firstvalid+33];
	var3[x->firstvalid+34]=mov5[x->firstvalid+34]-mov34[x->firstvalid+34];

	for (i=x->firstvalid+35; i<=x->lastvalid; i++)
	{
		var1[i]=mov5[i]-mov34[i];
		var3[i]=mov5[i]-mov34[i];

		if(var1[i]>var1[i-1] AND var1[i-1]<var1[i-2])
		{
			var2[i]=1;
			bsvar2[i]=0;
			var2_vw2[i]=var2_vw1[i-1];
			var2_vw1[i]=var1[i-1];
		}

		else
		{
			var2[i]=0;
			bsvar2[i]=bsvar2[i-1]+1;
			var2_vw2[i]=var2_vw2[i-1];
			var2_vw1[i]=var2_vw1[i-1];
		}

		if(var3[i]<var3[i-1] AND var3[i-1]>var3[i-2])
		{
			var4[i]=1;
			bsvar4[i]=0;
			var4_vw2[i]=var4_vw1[i-1];
			var4_vw1[i]=var3[i-1];
		}

		else
		{
			var4[i]=0;
			bsvar4[i]=bsvar4[i-1]+1;
			var4_vw2[i]=var4_vw2[i-1];
			var4_vw1[i]=var4_vw1[i-1];
		}
	}



	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+35; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(var2_vw1[i]>var2_vw2[i] AND bsvar2[i]<bsvar4[i] AND var1[i]<0 AND var4_vw1[i]<0)
			x->el[i]=1;

		if(var4[i]==1)
			x->cl[i]=1;

		if(var4_vw1[i]<var4_vw2[i] AND bsvar4[i]<bsvar2[i] AND var3[i]>0 AND var2_vw1[i]>0)
			x->es[i]=1;

		if(var2[i]==1)
			x->cs[i]=1;

	}

	memcpy (x->ind1, mov5, sizeof(float)*65500);			// Ind1 = 5-Period Moving Average of Midpoint
	memcpy (x->ind2, mov34, sizeof(float)*65500);			// Ind2 = 34-Period Moving Average of Midpoint
	memcpy (x->ind3, var1, sizeof(float)*65500);			// Ind3 = Elliott Oscillator (Mov5 - Mov34)

	*(x->elIsValid) = x->firstvalid+35;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+35;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+35;
	*(x->csIsValid) = x->firstvalid+35;
	*(x->ind1FirstValid) = x->firstvalid+4;
	*(x->ind2FirstValid) = x->firstvalid+33;
	*(x->ind3FirstValid) = x->firstvalid+33;

	bzero(intarray1,sizeof(int)*65500);						// Clean arrays
	bzero(intarray2,sizeof(int)*65500);
	bzero(intarray3,sizeof(int)*65500);
	bzero(intarray4,sizeof(int)*65500);
	
	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***************************************
//	***** Elliott Oscillator System 2 *****
//	***************************************
/*
Tom Joseph originated the concept of an 'Elliott Oscillator'. He used a
5-period moving average and subtracted a 35-period moving average from it to
create a 5/35 MACD oscillator. This was then used to analyze Elliott Waves. 
Later, Bill Williams came along and modified it by using a 5/34 MACD oscillator
so as to retain a Fibonacci relationship. He also started using the midpoint of
a bar instead of the closing prices. These systems use the Bill Williams
version (which he calls the Awesome Oscillator).

This system is almost identical to the "Elliott Oscillator System 1" except for
one major addition. When the MACD has a second trough higher than the first
trough, the security price has to be lower at this time than it was when the
first trough occurred. This shows a 'divergence' from the MACD and then enters
a long condition to follow the direction of the impending trend change. The 
reverse of all these conditions is for a short position.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 5-Period Moving Average of Midpoint
	Ind2 = 34-Period Moving Average of Midpoint
	Ind3 = Elliott Oscillator (Mov5 - Mov34)
	
MetaStock Code:
	var1:=Mov((H+L)/2,5,S)-Mov((H+L)/2,34,S);
	var2:=var1>Ref(var1,-1) AND Ref(var1,-1)<Ref(var1,-2);
	var3:=Mov((H+L)/2,5,S)-Mov((H+L)/2,34,S);
	var4:=var3<Ref(var3,-1) AND Ref(var3,-1)>Ref(var3,-2);

	EL:=ValueWhen(1,var2,Ref(var1,-1))>ValueWhen(2,var2,Ref(var1,-1)) AND
		BarsSince(var2)<BarsSince(var4)  AND ValueWhen(1,var2,Ref(C,-1))<
		ValueWhen(2,var2,Ref(C,-1)) AND var1<0 AND 
		ValueWhen(1,var4,Ref(var3,-1))<0;
	CL:= var4
	ES:= ValueWhen(1,var4,Ref(var3,-1))<ValueWhen(2,var4,Ref(var3,-1)) AND
		BarsSince(var4)<BarsSince(var2)  AND ValueWhen(1,var4,Ref(C,-1))>
		ValueWhen(2,var4,Ref(C,-1)) AND var3>0 AND 
		ValueWhen(1,var2,Ref(var1,-1))>0;
	CS:= var2
*/
int s35(struct datasys *x)									// Elliott Oscillator System 2
{
	int i=0;
	int *var2, *var4, *bsvar2, *bsvar4;
	float movstor=0;
	float *mov5, *mov34, *var1, *var3;
	float *var2_vw1, *var2_vw2, *var4_vw1, *var4_vw2;
	float *var2_vwclose1, *var2_vwclose2, *var4_vwclose1, *var4_vwclose2;


	var2=intarray1;											// Signal array for Up Fractal of Var1 (technically not used)
	var4=intarray2;											// Signal array for Down Fractal of Var3 (technically not used)
	bsvar2=intarray3;										// BarsSince Var2 Event
	bsvar4=intarray4;										// BarsSince Var4 Event

	mov5=floatarray1;										// 5-Period Moving Average of Midpoint
	mov34=floatarray2;										// 34-Period Moving Average of Midpoint
	var1=floatarray3;										// Mov5 - Mov34
	var3=floatarray4;										// Mov5 - Mov34
	var2_vw1=floatarray5;									// First (most recent) ValueWhen of Var1[i-1] when Var2 occurs
	var2_vw2=floatarray6;									// Second (next most recent) ValueWhen of Var1[i-1] when Var2 occurs
	var4_vw1=floatarray7;									// First (most recent) ValueWhen of Var3[i-1] when Var4 occurs
	var4_vw2=floatarray8;									// Second (next most recent) ValueWhen of Var3[i-1] when Var4 occurs
	var2_vwclose1=floatarray9;								// First (most recent) ValueWhen of Close[i-1] when Var2 occurs
	var2_vwclose2=floatarray10;								// Second (next most recent) ValueWhen of Close[i-1] when Var2 occurs
	var4_vwclose1=floatarray11;								// First (most recent) ValueWhen of Close[i-1] when Var4 occurs
	var4_vwclose2=floatarray12;								// Second (next most recent) ValueWhen of Close[i-1] when Var4 occurs


	if((x->lastvalid - x->firstvalid)<36) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+4; i>=x->firstvalid; i--)			// 5-Period Moving Average of Midpoint
	{
		movstor=movstor+((x->high[i]+x->low[i])/2);
	}

	mov5[x->firstvalid+4]=(float)(movstor/5.0);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)
	{
		movstor = movstor + ((x->high[i]+x->low[i])/2) - ((x->high[i-5]+x->low[i-5])/2);
		mov5[i] = (float)(movstor / 5.0);
	}

	movstor=0;

	for (i=x->firstvalid+33; i>=x->firstvalid; i--)			// 34-Period Moving Average of Midpoint
	{
		movstor=movstor+((x->high[i]+x->low[i])/2);
	}

	mov34[x->firstvalid+33]=(float)(movstor/34.0);

	for (i=x->firstvalid+34; i<=x->lastvalid; i++)
	{
		movstor = movstor + ((x->high[i]+x->low[i])/2) - ((x->high[i-34]+x->low[i-34])/2);
		mov34[i] = (float)(movstor / 34.0);
	}

															// Create Var1-Var4 Arrays
	var1[x->firstvalid+33]=mov5[x->firstvalid+33]-mov34[x->firstvalid+33];
	var1[x->firstvalid+34]=mov5[x->firstvalid+34]-mov34[x->firstvalid+34];
	var3[x->firstvalid+33]=mov5[x->firstvalid+33]-mov34[x->firstvalid+33];
	var3[x->firstvalid+34]=mov5[x->firstvalid+34]-mov34[x->firstvalid+34];

	for (i=x->firstvalid+35; i<=x->lastvalid; i++)
	{
		var1[i]=mov5[i]-mov34[i];
		var3[i]=mov5[i]-mov34[i];

		if(var1[i]>var1[i-1] AND var1[i-1]<var1[i-2])
		{
			var2[i]=1;
			bsvar2[i]=0;
			var2_vw2[i]=var2_vw1[i-1];
			var2_vw1[i]=var1[i-1];
			var2_vwclose2[i]=var2_vwclose1[i-1];
			var2_vwclose1[i]=x->close[i-1];
		}

		else
		{
			var2[i]=0;
			bsvar2[i]=bsvar2[i-1]+1;
			var2_vw2[i]=var2_vw2[i-1];
			var2_vw1[i]=var2_vw1[i-1];
			var2_vwclose2[i]=var2_vwclose2[i-1];
			var2_vwclose1[i]=var2_vwclose1[i-1];
		}

		if(var3[i]<var3[i-1] AND var3[i-1]>var3[i-2])
		{
			var4[i]=1;
			bsvar4[i]=0;
			var4_vw2[i]=var4_vw1[i-1];
			var4_vw1[i]=var3[i-1];
			var4_vwclose2[i]=var4_vwclose1[i-1];
			var4_vwclose1[i]=x->close[i-1];
		}

		else
		{
			var4[i]=0;
			bsvar4[i]=bsvar4[i-1]+1;
			var4_vw2[i]=var4_vw2[i-1];
			var4_vw1[i]=var4_vw1[i-1];
			var4_vwclose2[i]=var4_vwclose2[i-1];
			var4_vwclose1[i]=var4_vwclose1[i-1];
		}
	}



	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+35; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if(var2_vw1[i]>var2_vw2[i] AND bsvar2[i]<bsvar4[i] AND var1[i]<0 AND
			var4_vw1[i]<0 AND var2_vwclose1[i]<var2_vwclose2[i])
			x->el[i]=1;

		if(var4[i]==1)
			x->cl[i]=1;

		if(var4_vw1[i]<var4_vw2[i] AND bsvar4[i]<bsvar2[i] AND var3[i]>0 AND
			var2_vw1[i]>0 AND var4_vwclose1[i]>var4_vwclose2[i])
			x->es[i]=1;

		if(var2[i]==1)
			x->cs[i]=1;

	}

	memcpy (x->ind1, mov5, sizeof(float)*65500);			// Ind1 = 5-Period Moving Average of Midpoint
	memcpy (x->ind2, mov34, sizeof(float)*65500);			// Ind2 = 34-Period Moving Average of Midpoint
	memcpy (x->ind3, var1, sizeof(float)*65500);			// Ind3 = Elliott Oscillator (Mov5 - Mov34)

	*(x->elIsValid) = x->firstvalid+35;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+35;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+35;
	*(x->csIsValid) = x->firstvalid+35;
	*(x->ind1FirstValid) = x->firstvalid+4;
	*(x->ind2FirstValid) = x->firstvalid+33;
	*(x->ind3FirstValid) = x->firstvalid+33;


	bzero(intarray1,sizeof(int)*65500);						// Clean arrays
	bzero(intarray2,sizeof(int)*65500);
	bzero(intarray3,sizeof(int)*65500);
	bzero(intarray4,sizeof(int)*65500);
	
	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);
	bzero(floatarray10,sizeof(float)*65500);
	bzero(floatarray11,sizeof(float)*65500);
	bzero(floatarray12,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	**************************************
//	***** Exponential Moving Average *****
//	**************************************
/*
This system is an extremely fast follower of direction. Rather than try to
determine a single optimum-length moving average crossover approach, it simply
looks to see if a 2-period exponential moving average is moving upward or
downward. If the 2-period EMA is greater than yesterdays 2-period EMA, then it
enters long. If the 2-period EMA is less than yesterdays 2-period EMA, then it
enters a short position.

A good way to work with this type of fast moving system is to use protective
stops. For this particular system, using the previous days low as a stop point
(or previous days high if short) can help to prevent unnecessary losses.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 2-Period Exponential Moving Average of Close
	
MetaStock Code:
	EL:=Mov(C,2,E)>Ref(Mov(C,2,E),-1)
	ES:=Mov(C,2,E)<Ref(Mov(C,2,E),-1)
*/
int s36(struct datasys *x)									// Exponential Moving Average
{
	int i=0;
	float up=0, down=0;
	float *ema2;

	ema2=floatarray1;										// 2-Period Exponential Moving Average of Close

	if((x->lastvalid - x->firstvalid)<3) return 2;			// Return 2 if not enough data
															//	to calculate.

	ema2[x->firstvalid]=x->close[x->firstvalid];			// 2-Period Exponential Moving Average of Close

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		ema2[i] = (float)(x->close[i] * (2.0/3.0)) + (float)(ema2[i-1] * (1.0-(2.0/3.0)));
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+2; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (ema2[i]>ema2[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}
		if (ema2[i]<ema2[i-1])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, ema2, sizeof(float)*65500);			// Ind1 = 2-Period Exponential Moving Average of Close

	*(x->elIsValid) = x->firstvalid+2;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+2;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+2;
	*(x->csIsValid) = x->firstvalid+2;
	*(x->ind1FirstValid) = x->firstvalid+1;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Array

	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Fractal Trading System 1 *****
//	************************************
/*
While there are many definitions for a fractal in securities trading, the
definition used in these systems is a minor version of the type defined by Bill
Williams, Ph.D., and his chaos based trading methods. According to Bill
Williams, an up fractal is defined as a middle bar with two lower highs on each
side of it. A down fractal would be the reverse being a middle bar with two
higher lows on each side of it. 

This system is based on a very small fraction of Bill Williams' complete
trading system. It enters a long position when a price crosses above the most
recent up fractal. The position would be exited and a short position entered
when the price crosses below the most recent down fractal.

Further Reading from Bill Williams, Ph.D.:
	Trading Chaos: Applying Expert Techniques to Maximize Your Profits.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1995
	New Trading Dimensions: How to Profit from Chaos in Stocks, Bonds, and
		Commodities. (Wiley Trading Advantage) John Wiley and Sons, Inc. 1998

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	None
	
MetaStock Code:
	F1:=ValueWhen(1,H<Ref(H,-2) AND Ref(H,-1)<Ref(H,-2) AND Ref(H,-3)<Ref(H,-2)
		AND Ref(H,-4)<Ref(H,-2),Ref(H,-2));
	F2:=ValueWhen(1,L>Ref(L,-2) AND Ref(L,-1)>Ref(L,-2) AND Ref(L,-3)>Ref(L,-2)
		AND Ref(L,-4)>Ref(L,-2),Ref(L,-2));

	EL:=Cross(H,F1)
	ES:=Cross(F2,L)
*/
int s37(struct datasys *x)									// Fractal Trading System 1
{
	int i=0;
	float *vwhigh, *vwlow;

	vwhigh=floatarray1;										// Value of most recent fractal high
	vwlow=floatarray2;										// Value of most recent fractal low

	if((x->lastvalid - x->firstvalid)<5) return 2;			// Return 2 if not enough data
															//	to calculate.


	for(i=x->firstvalid+4; i<=x->lastvalid; i++)
	{
		if(x->high[i-2]>x->high[i] AND x->high[i-2]>x->high[i-1]
			AND x->high[i-2]>x->high[i-3] AND x->high[i-2]>x->high[i-4])
			vwhigh[i]=x->high[i-2];
		else vwhigh[i]=vwhigh[i-1];

		if(x->low[i-2]<x->low[i] AND x->low[i-2]<x->low[i-1]
			AND x->low[i-2]<x->low[i-3] AND x->low[i-2]<x->low[i-4])
			vwlow[i]=x->low[i-2];
		else vwlow[i]=vwlow[i-1];
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);


	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->high[i]>vwhigh[i] AND (x->high[i-1]<vwhigh[i-1] OR
			(x->high[i-1]==vwhigh[i-1] AND x->high[i-2]<vwhigh[i-1])))
		{
			x->el[i]=1;
			x->cs[i]=1;
		}
		if (x->low[i]<vwlow[i] AND (x->low[i-1]>vwlow[i-1] OR
			(x->low[i-1]==vwlow[i-1] AND x->low[i-2]>vwlow[i-1])))
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}


	*(x->elIsValid) = x->firstvalid+4;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+4;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+4;
	*(x->csIsValid) = x->firstvalid+4;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);


	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Fractal Trading System 2 *****
//	************************************
/*
While there are many definitions for a fractal in securities trading, the
definition used in these systems is a minor version of the type defined by Bill
Williams, Ph.D., and his chaos based trading methods. According to Bill
Williams, an up fractal is defined as a middle bar with two lower highs on each
side of it. A down fractal would be the reverse being a middle bar with two
higher lows on each side of it. 

This system is based on a very small fraction of Bill Williams' complete
trading system. It is identical to "Fractal Trading System 1" except that rather
than reversing a position upon the price crossing below the most recent down
fractal, it exits upon crossing the low of the second most recent fractal back
(no short positions are taken).

Further Reading from Bill Williams, Ph.D.:
	Trading Chaos: Applying Expert Techniques to Maximize Your Profits.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1995
	New Trading Dimensions: How to Profit from Chaos in Stocks, Bonds, and
		Commodities. (Wiley Trading Advantage) John Wiley and Sons, Inc. 1998

Trade Type:
	Long Positions Only

Indicator Output: 
	None
	
MetaStock Code:
	F1:=ValueWhen(1,H<Ref(H,-2) AND Ref(H,-1)<Ref(H,-2) AND Ref(H,-3)<Ref(H,-2)
		AND Ref(H,-4)<Ref(H,-2),Ref(H,-2));
	F2:=ValueWhen(2,L>Ref(L,-2) AND Ref(L,-1)>Ref(L,-2) AND Ref(L,-3)>Ref(L,-2)
		AND Ref(L,-4)>Ref(L,-2),Ref(L,-2));

	EL:=Cross(H,F1)
	ES:=Cross(F2,L)
*/
int s38(struct datasys *x)									// Fractal Trading System 2
{
	int i=0;
	float *vwhigh, *vwlow, *vwlow2;

	vwhigh=floatarray1;										// Value of most recent fractal high
	vwlow=floatarray2;										// Value of most recent fractal low
	vwlow2=floatarray3;										// Value of second most recent fractal low


	if((x->lastvalid - x->firstvalid)<5) return 2;			// Return 2 if not enough data
															//	to calculate.

	for(i=x->firstvalid+4; i<=x->lastvalid; i++)
	{
		if(x->high[i-2]>x->high[i] AND x->high[i-2]>x->high[i-1]
			AND x->high[i-2]>x->high[i-3] AND x->high[i-2]>x->high[i-4])
			vwhigh[i]=x->high[i-2];

		else vwhigh[i]=vwhigh[i-1];
		
		if(x->low[i-2]<x->low[i] AND x->low[i-2]<x->low[i-1]
			AND x->low[i-2]<x->low[i-3] AND x->low[i-2]<x->low[i-4])
		{
			vwlow2[i]=vwlow[i-1];
			vwlow[i]=x->low[i-2];
		}

		else 
		{
			vwlow2[i]=vwlow2[i-1];
			vwlow[i]=vwlow[i-1];
		}
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->high[i]>vwhigh[i] AND (x->high[i-1]<vwhigh[i-1] OR
			(x->high[i-1]==vwhigh[i-1] AND x->high[i-2]<vwhigh[i-1])))
			x->el[i]=1;

		if (x->low[i]<vwlow2[i] AND (x->low[i-1]>vwlow2[i-1] OR
			(x->low[i-1]==vwlow2[i-1] AND x->low[i-2]>vwlow2[i-1])))
			x->cl[i]=1;
	}


	*(x->elIsValid) = x->firstvalid+4;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+4;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+4;
	*(x->csIsValid) = x->firstvalid+4;
	*(x->ind1FirstValid) = x->firstvalid+4;
	*(x->ind2FirstValid) = x->firstvalid+4;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);


	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Fractal Trading System 3 *****
//	************************************
/*
While there are many definitions for a fractal in securities trading, the
definition used in these systems is a minor version of the type defined by Bill
Williams, Ph.D., and his chaos based trading methods. According to Bill
Williams, an up fractal is defined as a middle bar with two lower highs on each
side of it. A down fractal would be the reverse being a middle bar with two
higher lows on each side of it. 

This system is based on a very small fraction of Bill Williams' complete
trading system. It is identical to "Fractal Trading System 2" except that rather
than reversing a position upon the price crossing below the most recent down
fractal, it exits upon crossing the lowest of the most recent fractal or the
second most recent fractal back, depending on which is lower.
(no short positions are taken)

Further Reading from Bill Williams, Ph.D.:
	Trading Chaos: Applying Expert Techniques to Maximize Your Profits.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1995
	New Trading Dimensions: How to Profit from Chaos in Stocks, Bonds, and
		Commodities. (Wiley Trading Advantage) John Wiley and Sons, Inc. 1998

Trade Type:
	Long Positions Only

Indicator Output: 
	None
	
MetaStock Code:
	F1:=ValueWhen(1,H<Ref(H,-2) AND Ref(H,-1)<Ref(H,-2) AND Ref(H,-3)<Ref(H,-2)
		AND Ref(H,-4)<Ref(H,-2),Ref(H,-2));
	F2:=ValueWhen(2,L>Ref(L,-2) AND Ref(L,-1)>Ref(L,-2) AND Ref(L,-3)>Ref(L,-2)
		AND Ref(L,-4)>Ref(L,-2),Ref(L,-2));

	EL:=Cross(H,F1)
	ES:=Cross(F2,L)
*/
int s39(struct datasys *x)									// Fractal Trading System 3
{
	int i;
	float tlow, tlow2;
	float *vwhigh, *vwlow, *vwlow2;

	vwhigh=floatarray1;										// Value of most recent fractal high
	vwlow=floatarray2;										// Value of most recent fractal low
	vwlow2=floatarray3;										// Value of second most recent fractal low


	if((x->lastvalid - x->firstvalid)<5) return 2;			// Return 2 if not enough data
															//	to calculate.

	for(i=x->firstvalid+4; i<=x->lastvalid; i++)
	{
		if(x->high[i-2]>x->high[i] AND x->high[i-2]>x->high[i-1]
			AND x->high[i-2]>x->high[i-3] AND x->high[i-2]>x->high[i-4])
			vwhigh[i]=x->high[i-2];

		else vwhigh[i]=vwhigh[i-1];
		
		if(x->low[i-2]<x->low[i] AND x->low[i-2]<x->low[i-1]
			AND x->low[i-2]<x->low[i-3] AND x->low[i-2]<x->low[i-4])
		{
			vwlow2[i]=vwlow[i-1];
			vwlow[i]=x->low[i-2];
		}

		else 
		{
			vwlow2[i]=vwlow2[i-1];
			vwlow[i]=vwlow[i-1];
		}
	}

	
	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->high[i]>vwhigh[i] AND (x->high[i-1]<vwhigh[i-1] OR
			(x->high[i-1]==vwhigh[i-1] AND x->high[i-2]<vwhigh[i-1])))
			x->el[i]=1;

		tlow=__min(vwlow[i],vwlow2[i]);
		tlow2=__min(vwlow[i-1],vwlow2[i-1]);
		if (x->low[i]<tlow AND (x->low[i-1]>tlow2 OR
			(x->low[i-1]==tlow2 AND x->low[i-2]>tlow2)))
			x->cl[i]=1;

	}


	*(x->elIsValid) = x->firstvalid+4;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+4;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+4;
	*(x->csIsValid) = x->firstvalid+4;
	*(x->ind1FirstValid) = x->firstvalid+4;
	*(x->ind2FirstValid) = x->firstvalid+4;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	*************************
//	***** Impulse Meter *****
//	*************************
/*
Linda Bradford Raschke developed the Impulse Meter, an indicator comprised of
multiple momentum calculations. This system trades the same way that the RSI
does acting as an overbought/oversold indicator. Except rather than trading the
RSI of closing prices, it trades the RSI of the Impulse Meter indicator.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Impulse Meter Indicator (b1)
	
MetaStock Code:
	var1:=If(Max(Mo(2),Max(Mo(3),Max(Mo(4),Max(Mo(5),Max(Mo(6),Max(Mo(7),
		Max(Mo(8),Max(Mo(9),Max(Mo(10),Max(Mo(11),Mo(12)))))))))))-Min(Mo(2),
		Min(Mo(3),Min(Mo(4),Min(Mo(5),Min(Mo(6),Min(Mo(7),Min(Mo(8),Min(Mo(9),
		Min(Mo(10),Min(Mo(11),Mo(12)))))))))))<>0,Stdev(C,10)/(Max(Mo(2),
		Max(Mo(3),Max(Mo(4),Max(Mo(5),Max(Mo(6),Max(Mo(7),Max(Mo(8),Max(Mo(9),
		Max(Mo(10),Max(Mo(11),Mo(12)))))))))))-Min(Mo(2),Min(Mo(3),Min(Mo(4),
		Min(Mo(5),Min(Mo(6),Min(Mo(7),Min(Mo(8),Min(Mo(9),Min(Mo(10),Min(Mo(11),
		Mo(12)))))))))))),PREV);
	Z1:=Wilders(If(ROC(var1,1,$)>0,ROC(var1,1,$),0),7); 
	Y1:=Wilders(If(ROC(var1,1,$)<0,Abs(ROC(var1,1,$)),0),7); 
	RS:=Z1/Y1; 
	b1:=100-(100/(1+RS));

	EL:=Cross(b1,30)
	ES:= Cross(70,b1)
*/
int s40(struct datasys *x)									// Impulse Meter
{
	
	int i=0, j=0;
	float mo2=0, mo3=0, mo4=0, mo5=0, mo6=0, mo7=0, mo8=0;
	float mo9=0, mo10=0, mo11=0, mo12=0, movstor=0, stdstor=0;
	float *im1, *var1, *y, *z, *b1, *mov10, *stdev;

	im1=floatarray1;										// Impulse Meter indicator
	var1=floatarray2;										// Standard Deviation/Impulse Meter Calculation Indicator
	y=floatarray3;											// Numerator for RSI-like function
	z=floatarray4;											// Denominator for RSI-like function
	b1=floatarray5;											// RSI of Impulse Meter
	mov10=floatarray6;										// 10-Period Simple Moving Average of Close
	stdev=floatarray7;										// 10-Period Standard Deviation of Close


	if((x->lastvalid - x->firstvalid)<15) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+9; i>=x->firstvalid; i--)			// 10-Period Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov10[x->firstvalid+9]=(float)(movstor/10.0);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-10];
		mov10[i] = (float)(movstor / 10.0);
	}

	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Close
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->close[j]-mov10[i],2);
		}

		stdev[i]= (float)sqrt(stdstor/10.0);
	}

	im1[x->firstvalid+11]=(float).0001;

	for (i=x->firstvalid+12; i<=x->lastvalid; i++)			// Impulse Meter (b1)
	{
		mo2=x->close[i]/x->close[i-2];
		mo3=x->close[i]/x->close[i-3];
		mo4=x->close[i]/x->close[i-4];
		mo5=x->close[i]/x->close[i-5];
		mo6=x->close[i]/x->close[i-6];
		mo7=x->close[i]/x->close[i-7];
		mo8=x->close[i]/x->close[i-8];
		mo9=x->close[i]/x->close[i-9];
		mo10=x->close[i]/x->close[i-10];
		mo11=x->close[i]/x->close[i-11];
		mo12=x->close[i]/x->close[i-12];

		im1[i]=__max(mo2,__max(mo3,__max(mo4,__max(mo5,__max(mo6,__max(mo7
			,__max(mo8,__max(mo9,__max(mo10,__max(mo11,mo12))))))))))-
			__min(mo2,__min(mo3,__min(mo4,__min(mo5,__min(mo6,__min(mo7
			,__min(mo8,__min(mo9,__min(mo10,__min(mo11,mo12))))))))));


		if(im1[i]!=0)
			var1[i]=stdev[i]/im1[i];
		else var1[i]=var1[i-1];


		if(var1[i]>var1[i-1])
			y[i]=((var1[i]-var1[i-1])*((float)1/(float)7))+(y[i-1]*((float)6/(float)7));
		else
			y[i]=(0*((float)1/(float)7))+(y[i-1]*((float)6/(float)7));

		if(var1[i]<var1[i-1])
			z[i]=((var1[i-1]-var1[i])*((float)1/(float)7))+(z[i-1]*((float)6/(float)7));
		else
			z[i]=(0*((float)1/(float)7))+(z[i-1]*((float)6/(float)7));
	
		if(i>=x->firstvalid+13)
			b1[i]=100-(100/(1+(y[i]/z[i])));
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (b1[i-1]<30 AND b1[i]>30)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (b1[i-1]>70 AND b1[i]<70)

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, b1, sizeof(float)*65500);				// Ind1 = Impulse Meter Indicator

	*(x->elIsValid) = x->firstvalid+14;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+14;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+14;
	*(x->csIsValid) = x->firstvalid+14;
	*(x->ind1FirstValid) = x->firstvalid+13;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);


	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Intraday Momentum Index *****
//	***********************************
/*
Tushar Chande designed the Intraday Momentum Index (IMI). It is similar to an
RSI calculation except that it uses a close-open relationship instead of a
close-previous close relationship, and it is not smoothed the way that the RSI
is.

The system is traded the same way that an RSI is typically traded. It enters a
long position when the IMI crosses above 30, moving out of an oversold condition.
It then exits the long position when the IMI rises and then crosses below 70,
moving out of an overbought condition. The reverse is for short positions.

Further Reading from Tushar Chande:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators (With Stanley Kroll). (Wiley Finance Editions) John Wiley
		and Sons, Inc. 1994
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Intraday Momentum Index Indicator
	
MetaStock Code:
	EL:= Cross(IMI(14),30)
	CL:= Cross(70,IMI(14))
*/
int s41(struct datasys *x)									// Intraday Momentum Index
{
	
	int i=0, j=0;
	float upstor=0, downstor=0;
	float *ups, *downs, *imi;

	ups=floatarray1;										// Up moves in Open/Close relationship
	downs=floatarray2;										// Down moves in Open/Close relationship
	imi=floatarray3;										// Intraday Momentum Index


	if((x->lastvalid - x->firstvalid)<15) return 2;			// Return 2 if not enough data
															//	to calculate.

	for (i=x->firstvalid+13; i<=x->lastvalid; i++)
	{
		upstor=0;
		downstor=0;

		for (j=i-13; j<=i; j++)
		{
			if(x->close[j]>x->open[j]) upstor=upstor+(x->close[j]-x->open[j]);
			if(x->close[j]<x->open[j]) downstor=downstor+(x->open[j]-x->close[j]);
		}

		ups[i]=upstor;
		downs[i]=downstor;

		imi[i]=100-(100/(1+(ups[i]/downs[i])));
	}




	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (imi[i-1]<30 AND imi[i]>30)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (imi[i-1]>70 AND imi[i]<70)

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, imi, sizeof(float)*65500);				// Ind1 = Intraday Momentum Index Indicator

	*(x->elIsValid) = x->firstvalid+14;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+14;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+14;
	*(x->csIsValid) = x->firstvalid+14;
	*(x->ind1FirstValid) = x->firstvalid+13;

	
	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***************************
//	***** Landis Reversal *****
//	***************************
/*
The Landis indicator was developed by Jack Landis, and is basically a
combination of 5 different Stochastic Oscillator indicators comprised of
different periods, smoothings, and weightings. These combine into a single new
Stochastic Oscillator indicator that is uncannily more useful than the basic
Stochastic Oscillator indicator.

Rather than trade the same method as a regular Stochastic overbought/oversold
system, it instead buys and sells with the direction of the Landis indicator,
turning it into a trend based momentum oscillator.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Landis Stochastic
	
MetaStock Code:
	var1:=((Stoch(8,3)*.05)+(Stoch(89,21)*.43)+(Stoch(55,13)*.26)+
		(Stoch(34,8)*.16)+(Stoch(21,5)*.1));

	EL:=var1>Ref(var1,-1)
	ES:=var1<Ref(var1,-1)
*/
int s42(struct datasys *x)									// Landis Reversal
{
	
	int i=0, j=0;

	float hhv=0, llv=0, sumnum=0, sumden=0; 
	float *hhv8, *llv8, *hhv89, *llv89, *hhv55, *llv55, *hhv34, *llv34, *hhv21, *llv21;
	float *stoch8, *stoch89, *stoch55, *stoch34, *stoch21, *landis;

	hhv8=floatarray1;										// 8-Period Highest High value of Highs
	llv8=floatarray2;										// 8-Period Lowest Low Value of Lows
	hhv89=floatarray3;										// 89-Period Highest High value of Highs
	llv89=floatarray4;										// 89-Period Lowest Low Value of Lows
	hhv55=floatarray5;										// 55-Period Highest High value of Highs
	llv55=floatarray6;										// 55-Period Lowest Low Value of Lows
	hhv34=floatarray7;										// 34-Period Highest High value of Highs
	llv34=floatarray8;										// 34-Period Lowest Low Value of Lows
	hhv21=floatarray9;										// 21-Period Highest High value of Highs
	llv21=floatarray10;										// 21-Period Lowest Low Value of Lows
	stoch8=floatarray11;									// 8-Period Stochastic Oscillator with 3-Period Slowing
	stoch89=floatarray12;									// 89-Period Stochastic Oscillator with 21-Period Slowing
	stoch55=floatarray13;									// 55-Period Stochastic Oscillator with 13-Period Slowing
	stoch34=floatarray14;									// 34-Period Stochastic Oscillator with 8-Period Slowing
	stoch21=floatarray15;									// 21-Period Stochastic Oscillator with 5-Period Slowing
	landis=floatarray16;									// Landis Combined Stochastic Oscillator



	if((x->lastvalid - x->firstvalid)<110) return 2;		// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+7; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 8-day levels.
		for (j=i-7; j<=i; j++)
		{
			if (j==i-7)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv8[i]=hhv;
		llv8[i]=llv;
	}

	for (i=x->firstvalid+88; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 89-day levels.
		for (j=i-88; j<=i; j++)
		{
			if (j==i-88)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv89[i]=hhv;
		llv89[i]=llv;
	}

	for (i=x->firstvalid+54; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 55-day levels.
		for (j=i-54; j<=i; j++)
		{
			if (j==i-54)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv55[i]=hhv;
		llv55[i]=llv;
	}

	for (i=x->firstvalid+33; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 34-day levels.
		for (j=i-33; j<=i; j++)
		{
			if (j==i-33)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv34[i]=hhv;
		llv34[i]=llv;
	}

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 21-day levels.
		for (j=i-20; j<=i; j++)
		{
			if (j==i-20)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv21[i]=hhv;
		llv21[i]=llv;
	}

	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 8-Period Stochastid with 3-period slowing.
	{
		sumnum=0;											// Summed Numerator
		sumden=0;											// Summed Denominator

		for (j=i-2; j<=i; j++)								// 3-period slowing.
		{
			sumnum=sumnum+(x->close[j]-llv8[j]);
			sumden=sumden+(hhv8[j]-llv8[j]);
		}

		stoch8[i]=sumnum/sumden;
	}

	for (i=x->firstvalid+88+20; i<=x->lastvalid; i++)		// 89-Period Stochastid with 21-period slowing.
	{
		sumnum=0;											// Summed Numerator
		sumden=0;											// Summed Denominator

		for (j=i-20; j<=i; j++)								// 21-period slowing.
		{
			sumnum=sumnum+(x->close[j]-llv89[j]);
			sumden=sumden+(hhv89[j]-llv89[j]);
		}

		stoch89[i]=sumnum/sumden;
	}

	for (i=x->firstvalid+54+12; i<=x->lastvalid; i++)		// 55-Period Stochastid with 13-period slowing.
	{
		sumnum=0;											// Summed Numerator
		sumden=0;											// Summed Denominator

		for (j=i-12; j<=i; j++)								// 13-period slowing.
		{
			sumnum=sumnum+(x->close[j]-llv55[j]);
			sumden=sumden+(hhv55[j]-llv55[j]);
		}

		stoch55[i]=sumnum/sumden;
	}

	for (i=x->firstvalid+33+7; i<=x->lastvalid; i++)		// 34-Period Stochastid with 8-period slowing.
	{
		sumnum=0;											// Summed Numerator
		sumden=0;											// Summed Denominator

		for (j=i-7; j<=i; j++)								// 8-period slowing.
		{
			sumnum=sumnum+(x->close[j]-llv34[j]);
			sumden=sumden+(hhv34[j]-llv34[j]);
		}

		stoch34[i]=sumnum/sumden;
	}

	for (i=x->firstvalid+20+4; i<=x->lastvalid; i++)		// 21-Period Stochastid with 5-period slowing.
	{
		sumnum=0;											// Summed Numerator
		sumden=0;											// Summed Denominator

		for (j=i-4; j<=i; j++)								// 5-period slowing.
		{
			sumnum=sumnum+(x->close[j]-llv21[j]);
			sumden=sumden+(hhv21[j]-llv21[j]);
		}

		stoch21[i]=sumnum/sumden;
	}

	for(i=x->firstvalid+88+20; i<=x->lastvalid; i++)
		landis[i]=((stoch8[i]*(float).05)+(stoch89[i]*(float).43)+
			(stoch55[i]*(float).26)+(stoch34[i]*(float).16)
			+(stoch21[i]*(float).1))*100;

	


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+109; i<=x->lastvalid; i++)		// Calculate system signals and
	{														//	copy to output arrays.
		if (landis[i]>landis[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (landis[i]<landis[i-1])

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, landis, sizeof(float)*65500);			// Ind1 = Landis Stochastic

	*(x->elIsValid) = x->firstvalid+109;					// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+109;					//	for each output array.
	*(x->esIsValid) = x->firstvalid+109;
	*(x->csIsValid) = x->firstvalid+109;
	*(x->ind1FirstValid) = x->firstvalid+108;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);
	bzero(floatarray10,sizeof(float)*65500);
	bzero(floatarray11,sizeof(float)*65500);
	bzero(floatarray12,sizeof(float)*65500);
	bzero(floatarray13,sizeof(float)*65500);
	bzero(floatarray14,sizeof(float)*65500);
	bzero(floatarray15,sizeof(float)*65500);
	bzero(floatarray16,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***************************************
//	***** Linear Regression Crossover *****
//	***************************************
/*
A variation on a moving average crossover, this system enters when an end-point
linear regression crosses above an equal length moving average (21 period) and
exits when the linear regression crosses below the moving average. Significant
trading with a significant drawdown. Still profitable in the long run. This
system catches every major trend.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 21-Period Linear Regression of Close
	Ind2 = 21-Period Moving Average of Close
	
MetaStock Code:
	EL:= LinearReg(C,21)>Mov(C,21,S)
	ES:= LinearReg(C,21)<Mov(C,21,S)
*/
int s43(struct datasys *x)									// Linear Regression Crossover
{

	int i=0, j=0;
	float movstor=0, sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0;
	float *mov21, *linreg;

	mov21=floatarray1;										// 21-Period Moving Average of Close
	linreg=floatarray2;										// 21-Period Linear Regression of Close


	if((x->lastvalid - x->firstvalid)<21) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+20; i>=x->firstvalid; i--)			// 21-Period Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov21[x->firstvalid+20]=(float)(movstor/21.0);

	for (i=x->firstvalid+21; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-21];
		mov21[i] = (float)(movstor / 21.0);
	}

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// 21-Period Linear Regression
	{
		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-20; j<=i; j++)
		{
			sum1=sum1+((float)j*x->close[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->close[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+20)
			{
				movc=movc+x->close[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+20)
		{
			movc=movc-x->close[i-21]+x->close[i];
			movcum=movcum-(i-21)+i;
		}

		linreg[i]=			
			(21*sum1-sum2*sum3)/
			(21*sum4-(float)pow(sum2,2))*i+((movc/21)-(movcum/21)*
			(21*sum1-sum2*sum3)/
			(21*sum4-(float)pow(sum2,2)));
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (linreg[i]>mov21[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (linreg[i]<mov21[i])

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, linreg, sizeof(float)*65500);			// Ind1 = 21-Period Linear Regression of Close
	memcpy (x->ind2, mov21, sizeof(float)*65500);			// Ind2 = 21-Period Moving Average of Close

	*(x->elIsValid) = x->firstvalid+20;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+20;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+20;
	*(x->csIsValid) = x->firstvalid+20;
	*(x->ind1FirstValid) = x->firstvalid+20;
	*(x->ind2FirstValid) = x->firstvalid+20;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	****************************************
//	***** Long Sell Short Sale - 5 Day *****
//	****************************************
/*
The 'long','sell','short sale' (LSS) indicator was developed by George Angell.
It was designed as 3-period indicator for day trading purposes only, but here
it is used as a 5-period indicator suitable for end-of-day (near end-of-day)
purposes. Here it is treated as an overbought/oversold indicator. When the LSS
indicator moves below .3, it is viewed as oversold. When it moves above .7, it
is viewed as overbought. In general, this indicator (dependent what mode it is
in at any given time) can be a leading/lagging indicator in reference to a
same-period stochastic and if desired could be used with the same trading
techniques.

While it can be very good at capturing profits on a large number of trades, no
real protection mechanism has been put into place if the trade immediately
moves against you. Stop-loss orders should be used to prevent the failing
trades from removing all acquired profits.

Further reading by George Angell:
	Sure-Thing Options Trading: A Money-Making Guide to the New Listed Stock
		and Commodity Options Markets. New American Library Trade. 1984
	Winning in the Futures Markets: A Money-Making Guige to Trading, Hedging
		and Speculating. Probus Publishing Co. 1990
	How to Triple Your Money Every Year With Stock Index Futures. Windsor
		Books. 1984
	Real Time Proven Commodity Spreads: The 20 Most Consistently Profitable
		Low-Risk Trades. 1985

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 5-Period 'Long Sell Short Sale' Indicator
	
MetaStock Code:
	EL:= (((HHV(H,5)-Ref(O,-4))+(C-LLV(L,5)))/(2*(HHV(H,5)-LLV(L,5))))<.3
	ES:= (((HHV(H,5)-Ref(O,-4))+(C-LLV(L,5)))/(2*(HHV(H,5)-LLV(L,5))))>.7
*/
int s44(struct datasys *x)									// Long Sell Short Sale - 5 Day
{
	
	int i=0, j=0;
	float hhv=0, llv=0;
	float *hhv5, *llv5, *lsss5;

	hhv5=floatarray1;										// 5-Period Highest High Value of Highs
	llv5=floatarray2;										// 5-Period Lowest Low Value of Lows
	lsss5=floatarray3;										// 5-Period 'Long Sell Short Sale' Indicator


	if((x->lastvalid - x->firstvalid)<5) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 5-day levels.
		for (j=i-4; j<=i; j++)
		{
			if (j==i-4)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv5[i]=hhv;
		llv5[i]=llv;

		lsss5[i]=(((hhv5[i]-x->open[i-4])+(x->close[i]-llv5[i]))/(2*(hhv5[i]-llv5[i])));
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (lsss5[i]<(float).3)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (lsss5[i]>(float).7)

		{
			x->cl[i]=1;
			x->es[i]=1;
		}

		x->ind1[i]=lsss5[i];								// Long Sell Short Sale - 5 Day Indicator
	}

	memcpy (x->ind1, lsss5, sizeof(float)*65500);			// Ind1 = 5-Period 'Long Sell Short Sale' Indicator

	
	*(x->elIsValid) = x->firstvalid+4;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+4;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+4;
	*(x->csIsValid) = x->firstvalid+4;
	*(x->ind1FirstValid) = x->firstvalid+4;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	****************************
//	***** MACD Histogram 1 *****
//	****************************
/*
This system uses the MACD Histogram indicator popularized by Alexander Elder.
It uses it in a way that has been popularized for use by the regular MACD; it
looks for divergences between the indicator and price. The MACD Histogram is
calculated by subtracting the 9-period exponential moving average of the MACD
from the MACD itself. A divergence in price is then detected against this
indicator and a trade is entered in the direction of indicator movement with
the belief that the price will shortly follow.

Even though it is displayed here as a complete system and is functional as
such, it is primarily designed as an entry method. A favorite stop-loss and
exit strategy should be considered when using this system.

Further Reading from Alexander Elder:
	Trading for a Living: Psychology, Trading Tactics, Money Management.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1993
	Study Guide for Trading for a Living: Psychology, Trading Tactics,
		Money Management. (Wiley Finance Editions) John Wiley and Sons,
		Inc. 1993

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = MACD Histogram Indicator
	
MetaStock Code:
	a1:=MACD()-Mov(MACD(),9,E)>Ref(MACD()-Mov(MACD(),9,E),-1) AND
		Ref(MACD()-Mov(MACD(),9,E),-1)<Ref(MACD()-Mov(MACD(),9,E),-2);
	a2:=MACD()-Mov(MACD(),9,E)<Ref(MACD()-Mov(MACD(),9,E),-1) AND
		Ref(MACD()-Mov(MACD(),9,E),-1)>Ref(MACD()-Mov(MACD(),9,E),-2);
	b1:=ValueWhen(1,a1,Ref(MACD()-Mov(MACD(),9,E),-1))>
		ValueWhen(2,a1,Ref(MACD()-Mov(MACD(),9,E),-1)) AND
		ValueWhen(1,a1,C)<ValueWhen(2,a1,C);
	b2:=ValueWhen(1,a2,Ref(MACD()-Mov(MACD(),9,E),-1))<
		ValueWhen(2,a2,Ref(MACD()-Mov(MACD(),9,E),-1)) AND
		ValueWhen(1,a2,C)>ValueWhen(2,a2,C);
	state1:=If(BarsSince(b1)<BarsSince(b2),1,0);

	EL:=state1>Ref(state1,-1)
	ES:= state1<Ref(state1,-1)
*/
int s45(struct datasys *x)									// MACD Histogram 1
{
	
	int i=0;
	int *bslong, *bsshort;
	float vwhigh1=0, vwhigh2=0, vwhclose1=0, vwhclose2=0, vwlow1=0, vwlow2=0, vwlclose1=0, vwlclose2=0;
	float *mov12, *mov26, *mov9, *macd, *macdhist, *state;

	bslong=intarray1;										// BarsSince Long Signal
	bsshort=intarray2;										// BarsSince Short Signal

	mov12=floatarray1;										// 15 Percent (Approx 12-period) exp. moving average
	mov26=floatarray2;										// 7.5 Percent (Approx 26-period) exp. moving average
	mov9=floatarray3;										// 20 Percent (Approx 9-period) exp. moving average of MACD
	macd=floatarray4;										// Moving Average Convergence/Divergence (MACD) Indicator
	macdhist=floatarray5;									// MACD Histogram Indicator
	state=floatarray6;										// State of Trade (Long or Short)


	if((x->lastvalid - x->firstvalid)<37) return 2;			// Return 2 if not enough data
															//	to calculate.


	mov12[x->firstvalid]=x->close[x->firstvalid];			// 15 Percent (Approx 12-period) exp. moving average
	mov26[x->firstvalid]=x->close[x->firstvalid];			// 7.5 Percent (Approx 26-period) exp. moving average
	macd[x->firstvalid]=									// MACD Calculation
		mov12[x->firstvalid]-mov26[x->firstvalid];
	mov9[x->firstvalid]=macd[x->firstvalid];				// 20 Percent (Approx 9-period) exp. moving average
	macdhist[x->firstvalid]=								// MACD Histogram
		macd[x->firstvalid]-mov9[x->firstvalid];			

															// Day 2 calculations
	mov12[x->firstvalid+1]=(float)((mov12[x->firstvalid]*(float).85)+(x->close[x->firstvalid+1]*(float).15));
	mov26[x->firstvalid+1]=(float)((mov26[x->firstvalid]*(float).925)+(x->close[x->firstvalid+1]*(float).075));
	macd[x->firstvalid+1]=mov12[x->firstvalid+1]-mov26[x->firstvalid+1];
	mov9[x->firstvalid+1]=(float)((mov9[x->firstvalid]*(float).8)+(macd[x->firstvalid+1]*(float).2));
	macdhist[x->firstvalid+1]=macd[x->firstvalid+1]-mov9[x->firstvalid+1];


	for (i=x->firstvalid+2; i<=x->lastvalid; i++)			// Day 3 calculations forward
	{
		mov12[i]=(float)((mov12[i-1]*(float).85)+(x->close[i]*(float).15));
		mov26[i]=(float)((mov26[i-1]*(float).925)+(x->close[i]*(float).075));
		macd[i]=mov12[i]-mov26[i];
		mov9[i]=(float)((mov9[i-1]*(float).8)+(macd[i]*(float).2));
		macdhist[i]=macd[i]-mov9[i];

		if(macdhist[i]>macdhist[i-1] AND macdhist[i-1]<macdhist[i-2])
		{
			vwhigh2=vwhigh1;
			vwhigh1=macdhist[i-1];

			vwhclose2=vwhclose1;
			vwhclose1=x->close[i];
		}

		if(vwhigh1>vwhigh2 AND vwhclose1<vwhclose2)	bslong[i]=0;
		else bslong[i]=bslong[i-1]+1;
		
		if(macdhist[i]<macdhist[i-1] AND macdhist[i-1]>macdhist[i-2])
		{
			vwlow2=vwlow1;
			vwlow1=macdhist[i-1];

			vwlclose2=vwlclose1;
			vwlclose1=x->close[i];
		}

		if(vwlow1<vwlow2 AND vwlclose1>vwlclose2) bsshort[i]=0;
		else bsshort[i]=bsshort[i-1]+1;

		if(bslong[i]<bsshort[i]) state[i]=1;
		else state[i]=0;
	}

	
  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+36; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (state[i]>state[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (state[i]<state[i-1])

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, macdhist, sizeof(float)*65500);		// Ind1 = MACD Histogram Indicator

	*(x->elIsValid) = x->firstvalid+36;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+36;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+36;
	*(x->csIsValid) = x->firstvalid+36;
	*(x->ind1FirstValid) = x->firstvalid+33;


	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays
	bzero(intarray2,sizeof(int)*65500);
	
	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	****************************
//	***** MACD Histogram 2 *****
//	****************************
/*
This system uses the MACD Histogram indicator popularized by Alexander Elder.
It uses it in a way that has been popularized for use by the regular MACD; it
looks for divergences between the indicator and price. The MACD Histogram is
calculated by subtracting the 9-period exponential moving average of the MACD
from the MACD itself. A divergence in price is then detected against this
indicator and a trade is entered in the direction of indicator movement with
the belief that the price will shortly follow.

Even though it is displayed here as a complete system and is functional as
such, it is primarily designed as an entry method. A favorite stop-loss and
exit strategy should be considered when using this system. This system is
identical to "MACD Histogram 1" except it has an alternate exiting method.

Further Reading from Alexander Elder:
	Trading for a Living: Psychology, Trading Tactics, Money Management.
		(Wiley Finance Editions) John Wiley and Sons, Inc. 1993
	Study Guide for Trading for a Living: Psychology, Trading Tactics,
		Money Management. (Wiley Finance Editions) John Wiley and Sons,
		Inc. 1993

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = MACD Histogram Indicator
	
MetaStock Code:
	a1:=MACD()-Mov(MACD(),9,E)>Ref(MACD()-Mov(MACD(),9,E),-1) AND
		Ref(MACD()-Mov(MACD(),9,E),-1)<Ref(MACD()-Mov(MACD(),9,E),-2);
	a2:=MACD()-Mov(MACD(),9,E)<Ref(MACD()-Mov(MACD(),9,E),-1) AND
		Ref(MACD()-Mov(MACD(),9,E),-1)>Ref(MACD()-Mov(MACD(),9,E),-2);
	b1:=ValueWhen(1,a1,Ref(MACD()-Mov(MACD(),9,E),-1))>
		ValueWhen(2,a1,Ref(MACD()-Mov(MACD(),9,E),-1)) AND
		ValueWhen(1,a1,C)<ValueWhen(2,a1,C);
	b2:=ValueWhen(1,a2,Ref(MACD()-Mov(MACD(),9,E),-1))<
		ValueWhen(2,a2,Ref(MACD()-Mov(MACD(),9,E),-1)) AND
		ValueWhen(1,a2,C)>ValueWhen(2,a2,C);
	state1:=If(BarsSince(b1)<BarsSince(b2),1,0);

	EL:=state1>Ref(state1,-1)
	CL:= (MACD()-Mov(MACD(),9,E))<Ref((MACD()-Mov(MACD(),9,E)),-1)
	ES:= state1<Ref(state1,-1)
	CS:= (MACD()-Mov(MACD(),9,E))>Ref((MACD()-Mov(MACD(),9,E)),-1)
*/
int s46(struct datasys *x)									// MACD Histogram 2
{
	
	int i=0;
	int *bslong, *bsshort;
	float vwhigh1=0, vwhigh2=0, vwhclose1=0, vwhclose2=0, vwlow1=0, vwlow2=0, vwlclose1=0, vwlclose2=0;
	float *mov12, *mov26, *mov9, *macd, *macdhist, *state;

	bslong=intarray1;										// BarsSince Long Signal
	bsshort=intarray2;										// BarsSince Short Signal

	mov12=floatarray1;										// 15 Percent (Approx 12-period) exp. moving average
	mov26=floatarray2;										// 7.5 Percent (Approx 26-period) exp. moving average
	mov9=floatarray3;										// 20 Percent (Approx 9-period) exp. moving average of MACD
	macd=floatarray4;										// Moving Average Convergence/Divergence (MACD) Indicator
	macdhist=floatarray5;									// MACD Histogram Indicator
	state=floatarray6;										// State of Trade (Long or Short)

	if((x->lastvalid - x->firstvalid)<37) return 2;			// Return 2 if not enough data
															//	to calculate.


	mov12[x->firstvalid]=x->close[x->firstvalid];			// 15 Percent (Approx 12-period) exp. moving average
	mov26[x->firstvalid]=x->close[x->firstvalid];			// 7.5 Percent (Approx 26-period) exp. moving average
	macd[x->firstvalid]=									// MACD Calculation
		mov12[x->firstvalid]-mov26[x->firstvalid];
	mov9[x->firstvalid]=macd[x->firstvalid];				// 20 Percent (Approx 9-period) exp. moving average
	macdhist[x->firstvalid]=								// MACD Histogram
		macd[x->firstvalid]-mov9[x->firstvalid];			

															// Day 2 calculations
	mov12[x->firstvalid+1]=(float)((mov12[x->firstvalid]*(float).85)+(x->close[x->firstvalid+1]*(float).15));
	mov26[x->firstvalid+1]=(float)((mov26[x->firstvalid]*(float).925)+(x->close[x->firstvalid+1]*(float).075));
	macd[x->firstvalid+1]=mov12[x->firstvalid+1]-mov26[x->firstvalid+1];
	mov9[x->firstvalid+1]=(float)((mov9[x->firstvalid]*(float).8)+(macd[x->firstvalid+1]*(float).2));
	macdhist[x->firstvalid+1]=macd[x->firstvalid+1]-mov9[x->firstvalid+1];


	for (i=x->firstvalid+2; i<=x->lastvalid; i++)			// Day 3 calculations forward
	{
		mov12[i]=(float)((mov12[i-1]*(float).85)+(x->close[i]*(float).15));
		mov26[i]=(float)((mov26[i-1]*(float).925)+(x->close[i]*(float).075));
		macd[i]=mov12[i]-mov26[i];
		mov9[i]=(float)((mov9[i-1]*(float).8)+(macd[i]*(float).2));
		macdhist[i]=macd[i]-mov9[i];

		if(macdhist[i]>macdhist[i-1] AND macdhist[i-1]<macdhist[i-2])
		{
			vwhigh2=vwhigh1;
			vwhigh1=macdhist[i-1];

			vwhclose2=vwhclose1;
			vwhclose1=x->close[i];
		}

		if(vwhigh1>vwhigh2 AND vwhclose1<vwhclose2)	bslong[i]=0;
		else bslong[i]=bslong[i-1]+1;
		
		if(macdhist[i]<macdhist[i-1] AND macdhist[i-1]>macdhist[i-2])
		{
			vwlow2=vwlow1;
			vwlow1=macdhist[i-1];

			vwlclose2=vwlclose1;
			vwlclose1=x->close[i];
		}

		if(vwlow1<vwlow2 AND vwlclose1>vwlclose2) bsshort[i]=0;
		else bsshort[i]=bsshort[i-1]+1;

		if(bslong[i]<bsshort[i]) state[i]=1;
		else state[i]=0;
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+36; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (state[i]>state[i-1])
			x->el[i]=1;

		if (macdhist[i]<macdhist[i-1])
			x->cl[i]=1;

		if (state[i]<state[i-1])
			x->es[i]=1;

		if (macdhist[i]>macdhist[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, macdhist, sizeof(float)*65500);		// Ind1 = MACD Histogram Indicator
	
	*(x->elIsValid) = x->firstvalid+36;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+36;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+36;
	*(x->csIsValid) = x->firstvalid+36;
	*(x->ind1FirstValid) = x->firstvalid+33;


	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays
	bzero(intarray2,sizeof(int)*65500);
	
	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***************************************
//	***** Meisels Overbought/Oversold *****
//	***************************************
/*
Ron Meisels developed the Meisels Indicator as an overbought/oversold indicator
that moves between a +10/-10 range and is based on whether the market closed
higher/lower than the previous trading day. The original entry concept is
maintained here with a long entry occurring when the indicator reaches -6
(oversold), and a short entry occurring when the indicator reaches +6
(overbought). In this case, an exit has been added when the indicator reaches a
zero level from either direction. This produces a very good short-term approach
to trading.

As with all overbought/oversold indicators and systems, even though it can be
very good at capturing profits on a large number of trades, no real protection
mechanism has been put into place if the trade immediately moves against you.
Stop-loss orders should be used to prevent the few failing trades from removing
all acquired profits.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Meisels Indicator
	
MetaStock Code:
	M1:=Sum(If(C>Ref(C,-1),+1,If(C<Ref(C,-1),-1,0)),10);

	EL:=Cross(-6,M1) OR M1=-6
	CL:= Cross(M1,0) OR M1=0
	ES:= Cross(M1,6) OR M1=6
	CS:= Cross(0,M1) OR M1=0
*/
int s47(struct datasys *x)									// Meisels Overbought/Oversold
{
	
	int i=0, mcount=0;
	int *mstore;
	float *meisels;

	mstore=intarray1;										// Storage Array

	meisels=floatarray1;									// Meisels Indicator


	if((x->lastvalid - x->firstvalid)<11) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Create a condition array for Meisels
	{
		if(x->close[i]>x->close[i-1]) mstore[i]=1;
		else if(x->close[i]<x->close[i-1]) mstore[i]=-1;
		else mstore[i]=0;
	}

	for (i=x->firstvalid+1; i<=x->firstvalid+10; i++)
		mcount=mcount+mstore[i];

	meisels[x->firstvalid+10]=(float)mcount;

	for (i=x->firstvalid+11; i<=x->lastvalid; i++)
		meisels[i]=meisels[i-1]-mstore[i-10]+mstore[i];



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (meisels[i]==(-6) OR (meisels[i]<(-6) AND meisels[i-1]>(-6)))
			x->el[i]=1;

		if (meisels[i]==0 OR (meisels[i]>0 AND meisels[i-1]<0))
			x->cl[i]=1;

		if (meisels[i]==6 OR (meisels[i]>6 AND meisels[i-1]<6))
			x->es[i]=1;
		
		if (meisels[i]==0 OR (meisels[i]<0 AND meisels[i-1]>0))
			x->cs[i]=1;
	}

	memcpy (x->ind1, meisels, sizeof(float)*65500);			// Ind1 = Meisels Indicator

	*(x->elIsValid) = x->firstvalid+10;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+10;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+10;
	*(x->csIsValid) = x->firstvalid+10;
	*(x->ind1FirstValid) = x->firstvalid+10;

	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays

	bzero(floatarray1,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	**************************
//	***** MESA Sine Wave *****
//	**************************
/*
The MESA Sine Wave indicator was initially revealed in the November 1996 issue
of Technical Analysis of Stocks & Commodities magazine by its creator, John
Ehlers. The indicator itself is designed to determine if a security is in a
cyclic or trending mode. However, the short time frame used in this system
doesn't really allow it to ever make that distinction. Instead, it tries to
identify and take advantage of extremely short-term cyclic activity. Since the
period being used is so short, the MESA Sine Wave is almost turned into a
binary indicator with a very fast sensitivity to a change in direction. Trading
can easily occur daily with this system.

Further reading by John Ehlers:
	MESA and Trading Market Cycles. John Wiley and Sons, Inc. 1992

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Not Yet Determined
	
MetaStock Code:
	EL:= MESALeadSine(2)<MESASineWave(2)
	ES:= MESALeadSine(2)>MESASineWave(2)
*/

// *** Not yet Encoded ***
int s48(struct datasys *x)									// MESA Sine Wave
{
	return 0;
}




//	*****************************
//	***** Modified Momentum *****
//	*****************************
/*
This is a typical momentum system applied to an atypical momentum indicator. It
creates an indicator by taking a 15-period Moving Average of a 25-period
Rate-of-Change of a 3-period Moving Average. After all of that, it enters a
long position when the indicator is above the 9-period Moving Average of itself
and exits/shorts when the indicator crosses below the 9-period Moving Average
of itself.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 15-Period Modified Momentum Indicator
	Ind2 = 9-Period Exponential Moving Average of Mod. Momentum
	
MetaStock Code:
	var1:=(Mov(ROC(Mov(C,3,S),25,%),15,E));

	EL:=var1>Mov(var1,9,E)
	ES:= var1<Mov(var1,9,E)
*/
int s49(struct datasys *x)									// Modified Momentum
{
	
	int i=0;
	float movstor=0;
	float *mov3, *roc, *modmom15, *mov9;

	mov3=floatarray1;										// 3-Period Simple Moving Average of Close
	roc=floatarray2;										// 25-Period Rate of Change of Simple Moving Average
	modmom15=floatarray3;									// 15-Period Exponential Moving Average of Rate of Change
															//	(Modified Momentum)
	mov9=floatarray4;										// 9-Period Exponential Moving Average of Mod. Momentum


	if((x->lastvalid - x->firstvalid)<50) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+2; i>=x->firstvalid; i--)			// 3-Period Simple Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov3[x->firstvalid+2]=(float)(movstor/3.0);

	for (i=x->firstvalid+3; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-3];
		mov3[i] = (float)(movstor / 3.0);
	}


	for (i=x->firstvalid+27; i<=x->lastvalid; i++)			// 25-Period Rate of Change of Simple Moving Average
		roc[i]=(float)((mov3[i]/mov3[i-25])-1)*100;




	modmom15[x->firstvalid+41]=roc[x->firstvalid+41];		// 15-Period Exponential Moving Average of Rate of Change
															//	(Modified Momentum)
	for (i=x->firstvalid+42; i<=x->lastvalid; i++)
		modmom15[i] = (float)(roc[i] * .125) + (float)(modmom15[i-1] * (.875));


	mov9[x->firstvalid+49]=modmom15[x->firstvalid+49];		// 9-Period Exponential Moving Average of Mod. Momentum

	for (i=x->firstvalid+50; i<=x->lastvalid; i++)
		mov9[i] = (float)(modmom15[i] * .2) + (float)(mov9[i-1] * (.8));


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+49; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (modmom15[i]>mov9[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (modmom15[i]<mov9[i])

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, modmom15, sizeof(float)*65500);		// Ind1 = 15-Period Modified Momentum Indicator
	memcpy (x->ind2, mov9, sizeof(float)*65500);			// Ind2 = 9-Period Exponential Moving Average of Mod. Momentum

	*(x->elIsValid) = x->firstvalid+49;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+49;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+49;
	*(x->csIsValid) = x->firstvalid+49;
	*(x->ind1FirstValid) = x->firstvalid+41;
	*(x->ind2FirstValid) = x->firstvalid+49;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	********************
//	***** Momentum *****
//	********************
/*
This system uses the Momentum indicator, but rather than determine when the
momentum of prices themselves is in a positive/negative state, it determines
when a Linear Regression of Momentum is in a positive/negative state. This
reduces whipsaws in trading, but also makes sure that there is consistent
movement in the direction of the trade.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 12-Period Momentum
	Ind2 = 8-Period Linear Regression of Momentumm
	
MetaStock Code:
	EL:= LinearReg(Mo(12),8)>100
	ES:= LinearReg(Mo(12),8)<100
*/
int s50(struct datasys *x)									// Momentum
{
	int i=0, j=0;
	float sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0;
	float *mom, *linreg;

	mom=floatarray1;										// 12-Period Momentum
	linreg=floatarray2;										// 8-Period Linear Regression of Momentum


	if((x->lastvalid - x->firstvalid)<20) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+12; i<=x->lastvalid; i++)			// 12-Period Momentum
		mom[i]=(float)(x->close[i]/x->close[i-12])*100;


	for (i=x->firstvalid+19; i<=x->lastvalid; i++)			// 8-Period Linear Regression of Momentum
	{
		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-7; j<=i; j++)
		{
			sum1=sum1+((float)j*mom[j]);
			sum2=sum2+(float)j;
			sum3=sum3+mom[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+19)
			{
				movc=movc+mom[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+19)
		{
			movc=movc-mom[i-8]+mom[i];
			movcum=movcum-(i-8)+i;
		}

		linreg[i]=			
			(8*sum1-sum2*sum3)/
			(8*sum4-(float)pow(sum2,2))*i+((movc/8)-(movcum/8)*
			(8*sum1-sum2*sum3)/
			(8*sum4-(float)pow(sum2,2)));
	}



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+19; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (linreg[i]>100)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (linreg[i]<100)

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, mom, sizeof(float)*65500);				// Ind1 = 12-Period Momentum
	memcpy (x->ind2, linreg, sizeof(float)*65500);			// Ind2 = 8-Period Linear Regression of Momentumm

	*(x->elIsValid) = x->firstvalid+19;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+19;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+19;
	*(x->csIsValid) = x->firstvalid+19;
	*(x->ind1FirstValid) = x->firstvalid+12;
	*(x->ind2FirstValid) = x->firstvalid+19;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	*****************************************
//	***** New Relative Volatility Index *****
//	*****************************************
/*
The New Relative Volatility Index indicator was designed by Donald Dorsey and
published in the September 1995 issue of Technical Analysis of Stocks and
Commodities magazine. The original system as published enters a long position
when the indicator crosses above a value of 50 and exits when it crosses below
50. 

This version of the system isn't looking for a specific threshold, but instead
looks at the direction of the indicator. If the indicator is rising, it takes a
long position. As soon as the indicator changes direction and begins falling,
it exits and takes a short position. While significantly increasing the number
of trades over the original system, the overall profitability of the trades it
makes seems to be significantly higher.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = New Relative Volatility Index
	
MetaStock Code:
	var1:=(100*Mov(If(H>Ref(H,-1),Std(H,10),0),14,E)/(Mov(If(H>Ref(H,-1),
		Std(H,10),0),14,E)+Mov(If(H<Ref(H,-1),Std(H,10),0),14,E))+100*
		Mov(If(L>Ref(L,-1),Std(L,10),0),14,E)/(Mov(If(L>Ref(L,-1),
		Std(L,10),0),14,E)+Mov(If(L<Ref(L,-1),Std(L,10),0),14,E)))/2;

	EL:=var1>Ref(var1,-1)
	ES:= var1<Ref(var1,-1)
*/
int s51(struct datasys *x)									// New Relative Volatility Index
{
	int i=0, j=0;


	float movstor=0, stdstor=0;
	float *movhigh10, *stdevhigh, *movlow10, *stdevlow;
	float *highup, *highdown, *lowup, *lowdown;
	float *movhighup, *movhighdown, *movlowup, *movlowdown;
	float *rvih, *rvil, *newrvi;



	if((x->lastvalid - x->firstvalid)<24) return 2;			// Return 2 if not enough data
															//	to calculate.

	movhigh10=floatarray1;									// 10-Period Moving Average of Highs
	stdevhigh=floatarray2;									// 10-Period Standard Deviation of Highs
	movlow10=floatarray3;									// 10-Period Moving Average of Lows
	stdevlow=floatarray4;									// 10-Period Standard Deviation of Lows
	highup=floatarray5;										// Up Moves of Standard Deviation of Highs
	highdown=floatarray6;									// Down Moves of Standard Deviation of Highs
	lowup=floatarray7;										// Up Moves of Standard Deviation of Lows
	lowdown=floatarray8;									// Down Moves of Standard Deviation of Lows
	movhighup=floatarray9;									// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (up)
	movhighdown=floatarray10;								// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (down)
	movlowup=floatarray11;									// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (up)
	movlowdown=floatarray12;								// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (down)
	rvih=floatarray13;										// Relative Volatility Index of Highs
	rvil=floatarray14;										// Relative Volatility Index of Lows
	newrvi=floatarray15;									// New Relative Volatility Index
	

	for (i=x->firstvalid+9; i>=x->firstvalid; i--)			// 10-Period Moving Average of Highs
	{
		movstor=movstor+x->high[i];
	}

	movhigh10[x->firstvalid+9]=(float)(movstor/10.0);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->high[i] - x->high[i-10];
		movhigh10[i] = (float)(movstor / 10.0);
	}

	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Highs
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->high[j]-movhigh10[i],2);
		}

		stdevhigh[i]= (float)sqrt(stdstor/10.0);
	}

	movstor=0;
	stdstor=0;

	for (i=x->firstvalid+9; i>=x->firstvalid; i--)			// 10-Period Moving Average of Lows
	{
		movstor=movstor+x->low[i];
	}

	movlow10[x->firstvalid+9]=(float)(movstor/10.0);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->low[i] - x->low[i-10];
		movlow10[i] = (float)(movstor / 10.0);
	}

	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Lows
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->low[j]-movlow10[i],2);
		}

		stdevlow[i]= (float)sqrt(stdstor/10.0);
	}


	for (i=x->firstvalid+9; i<=x->lastvalid; i++)
	{
		if(x->high[i]>x->high[i-1]) highup[i]=stdevhigh[i];
		if(x->high[i]<x->high[i-1]) highdown[i]=stdevhigh[i];

		if(x->low[i]>x->low[i-1]) lowup[i]=stdevlow[i];
		if(x->low[i]<x->low[i-1]) lowdown[i]=stdevlow[i];
	}




	movhighup[x->firstvalid+9]=highup[x->firstvalid+9];		// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (up)

	movhighdown[x->firstvalid+9]=highdown[x->firstvalid+9];	// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (down)

	movlowup[x->firstvalid+9]=lowup[x->firstvalid+9];		// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (up)

	movlowdown[x->firstvalid+9]=lowdown[x->firstvalid+9];	// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (down)

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movhighup[i] = (float)(highup[i] * (2.0/15.0)) + (float)(movhighup[i-1] * (1.0-(2.0/15.0)));
		movhighdown[i] = (float)(highdown[i] * (2.0/15.0)) + (float)(movhighdown[i-1] * (1.0-(2.0/15.0)));
		movlowup[i] = (float)(lowup[i] * (2.0/15.0)) + (float)(movlowup[i-1] * (1.0-(2.0/15.0)));
		movlowdown[i] = (float)(lowdown[i] * (2.0/15.0)) + (float)(movlowdown[i-1] * (1.0-(2.0/15.0)));

		rvih[i]=100*movhighup[i]/(movhighup[i]+movhighdown[i]);
		rvil[i]=100*movlowup[i]/(movlowup[i]+movlowdown[i]);

		newrvi[i]=(rvih[i]+rvil[i])/2;
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+23; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (newrvi[i]>newrvi[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (newrvi[i]<newrvi[i-1])

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, newrvi, sizeof(float)*65500);			// Ind1 = New Relative Volatility Index


	*(x->elIsValid) = x->firstvalid+23;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+23;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+23;
	*(x->csIsValid) = x->firstvalid+23;
	*(x->ind1FirstValid) = x->firstvalid+20;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);
	bzero(floatarray10,sizeof(float)*65500);
	bzero(floatarray11,sizeof(float)*65500);
	bzero(floatarray12,sizeof(float)*65500);
	bzero(floatarray13,sizeof(float)*65500);
	bzero(floatarray14,sizeof(float)*65500);
	bzero(floatarray15,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	********************************
//	***** Oscillator Composite *****
//	********************************
/*
This system sums the results of four 34-period overbought/oversold oscillators:
the Relative Strength Indicator, the Stochastic Oscillator, the Momentum
Indicator, and the Commodity Channel Index. For a long position, the composite
oscillator crosses below -50. The long position is then exited and a short
position taken when the oscillator crosses above 450. These two thresholds
identify major overbought/oversold conditions and the system tries to exploit
this type of behavior.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Oscillator Composite
	
MetaStock Code:
	Var1:=RSI(34)+Stoch(34,3)+Mo(34)+CCI(34);

	EL:=Var1<-50
	ES:= Var1>450
*/
int s52(struct datasys *x)									// Oscillator Composite
{
	int i=0, j=0, masize=34;
	float rsiup=0, rsidown=0, upold=0, downold=0, sumnum=0, sumden=0;
	float colg=0, colh=0, coli=0, colj=0, matemp=0, hhv=0, llv=0;
	float *mom, *rsi, *stoch, *hhv34, *llv34, *typical, *movavg, *cci, *osccomp;

	mom=floatarray1;										// 34-Period Momentum
	rsi=floatarray2;										// 34-Period Relative Strength Indicator
	stoch=floatarray3;										// 34-Period Stochastid with 3-period slowing.
	hhv34=floatarray4;										// 34-Period Highest High Value of Highs
	llv34=floatarray5;										// 34-Period Lowest Low Value of Lows
	typical=floatarray6;									// Typical Price (Used in CCI Calculation)
	movavg=floatarray7;										// 34-Period Moving Average (Used in CCI Calculation)
	cci=floatarray8;										// Commodity Channel Index
	osccomp=floatarray9;									// Oscillator Composite


	if((x->lastvalid - x->firstvalid)<38) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+34; i<=x->lastvalid; i++)			// 34-Period Momentum
		mom[i]=(float)(x->close[i]/x->close[i-34])*100;




	for (i=x->firstvalid+1; i<=x->firstvalid+33; i++)		// 34-Period Relative Strength Index (RSI)
	{
		if(x->close[i]>x->close[i-1]) rsiup=rsiup+(x->close[i]-x->close[i-1]);
		if(x->close[i]<x->close[i-1]) rsidown=rsidown+(x->close[i-1]-x->close[i]);
	}

	if(rsidown==0) rsidown=(float).0001;					// (To prevent divide by zero error)

	rsi[x->firstvalid+33]=100-(100/(1+(rsiup/rsidown)));

	rsiup=rsiup/(float)34;
	rsidown=rsidown/(float)34;

	for (i=x->firstvalid+34; i<=x->lastvalid; i++)
	{
		if(x->close[i]>x->close[i-1])
			rsiup=(rsiup*((float)33/(float)34))+((x->close[i]-x->close[i-1])*((float)1/(float)34));
		else 
			rsiup=rsiup*((float)33/(float)34);

		if(x->close[i]<x->close[i-1])
			rsidown=(rsidown*((float)33/(float)34))+((x->close[i-1]-x->close[i])*((float)1/(float)34));
		else 
			rsidown=rsidown*((float)33/(float)34);

		rsi[i]=100-(100/(1+(rsiup/rsidown)));
	}


	for (i=x->firstvalid+33; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 34-day levels.
		for (j=i-33; j<=i; j++)								//	(Needed for Stochastic Calculation)
		{
			if (j==i-33)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv34[i]=hhv;
		llv34[i]=llv;
	}

	for (i=x->firstvalid+33+2; i<=x->lastvalid; i++)		// 34-Period Stochastid with 3-period slowing.
	{
		sumnum=0;											// Summed Numerator
		sumden=0;											// Summed Denominator

		for (j=i-2; j<=i; j++)								// 3-period slowing.
		{
			sumnum=sumnum+(x->close[j]-llv34[j]);
			sumden=sumden+(hhv34[j]-llv34[j]);
		}

		stoch[i]=(sumnum/sumden)*100;
	}



	for(i=x->firstvalid; i<=x->lastvalid; i++)				// Begin 14-period CCI calculation
	{
		typical[i]=(x->high[i]+x->low[i]+x->close[i])/(float)3;
		
		if(i==x->firstvalid+(masize-1))
			for(j=i-(masize-1); j<=i; j++)
				matemp=matemp+typical[j];

		if(i>x->firstvalid+(masize-1))
			matemp=matemp-typical[i-masize]+typical[i];

		if(i>=x->firstvalid+(masize-1))
		{
			movavg[i]=matemp/(float)masize;

			colg=0;
			colh=0;
			coli=0;
			colj=0;


			for(j=i-(masize-1); j<=i; j++)
				colg=colg+(float)fabs(typical[j]-movavg[i]);

			colh=colg/masize;
			coli=colh*(float)0.015;
			colj=typical[i]-movavg[i];
			cci[i]=colj/coli;
		}
	}

	for (i=x->firstvalid+37; i<=x->lastvalid; i++)
		osccomp[i]=rsi[i]+stoch[i]+mom[i]+cci[i];



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+37; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (osccomp[i]<-50)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (osccomp[i]>450)

		{
			x->cl[i]=1;
			x->es[i]=1;
		}

		x->ind1[i]=osccomp[i];								// Oscillator Composite
	}

	memcpy (x->ind1, osccomp, sizeof(float)*65500);			// Ind1 = Oscillator Composite
	
	*(x->elIsValid) = x->firstvalid+37;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+37;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+37;
	*(x->csIsValid) = x->firstvalid+37;
	*(x->ind1FirstValid) = x->firstvalid+37;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Pattern Trading System 1 *****
//	************************************
/*
This system is designed to use with stocks/stock indexes since it relies upon
the inherent upward bias typically seen in them. It follows the philosophy that
ANY up movement becomes an enter long signal, and any down movement following a
valid up movement trend (two days or more up movement) becomes a valid exit
signal. While being a very fast system, it can also be an extremely profitable
one. Since the upward bias is already accounted for, it has no short positions
available.

While it can be very good at capturing profits on a large number of trades, no
real protection mechanism has been put into place if the trade immediately
moves against you. Stop-loss orders should be used to prevent the few failing
trades from removing all acquired profits.

Trade Type:
	Long Positions Only

Indicator Output: 
	None
	
MetaStock Code:
	EL:= C>Ref(C,-1) AND Ref(C,-1)<Ref(C,-2)
	CL:= C<Ref(C,-1) AND Ref(C,-1)>Ref(C,-2) AND Ref(C,-2)>Ref(C,-3)
*/
int s53(struct datasys *x)									// Pattern Trading System 1
{

	int i=0;

	if((x->lastvalid - x->firstvalid)<4) return 2;			// Return 2 if not enough data
															//	to calculate.


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+3; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>x->close[i-1] AND x->close[i-1]<x->close[i-2])
			x->el[i]=1;

		if (x->close[i]<x->close[i-1] AND x->close[i-1]>x->close[i-2] AND x->close[i-2]>x->close[i-3])
			x->cl[i]=1;
	}
	
	*(x->elIsValid) = x->firstvalid+3;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+3;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+3;
	*(x->csIsValid) = x->firstvalid+3;

	return 0;												// Return NULL for valid system.
}





//	************************************
//	***** Pattern Trading System 2 *****
//	************************************
/*
A long position is entered when today's close is greater than the open, today's
open is greater than yesterday's close, today's close is above the midpoint of
today's trading, the low is greater than yesterday's low, and the close is
greater than yesterday's high. This shows a more specific immediate up-trend.
A short signal is the reverse.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	None
	
MetaStock Code:
	EL:= L>Ref(L,-1) AND C>Ref(H,-1) AND O>Ref(C,-1) AND C>((H+L)/2) AND C>O
	ES:= H<Ref(H,-1) AND C<Ref(L,-1) AND O<Ref(C,-1) AND C<((H+L)/2) AND C<O
*/
int s54(struct datasys *x)									// Pattern Trading System 2
{

	int i=0;

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->low[i]>x->low[i-1] AND x->close[i]>x->high[i-1] AND
			x->open[i]>x->close[i-1] AND x->close[i]>((x->high[i]+x->low[i])/(float)2)
			AND x->close[i]>x->open[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->high[i]<x->high[i-1] AND x->close[i]<x->low[i-1] AND
			x->open[i]<x->close[i-1] AND x->close[i]<((x->high[i]+x->low[i])/(float)2)
			AND x->close[i]<x->open[i])

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}
	
	*(x->elIsValid) = x->firstvalid+1;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+1;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+1;
	*(x->csIsValid) = x->firstvalid+1;

	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Pattern Trading System 3 *****
//	************************************
/*
A long position is entered when today's close is greater than the open, today's
open is greater than yesterday's close, and today's close is equal to or above
the midpoint of today's trading. This shows an immediate up-trend. A short
signal is the reverse. 

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	None
	
MetaStock Code:
	EL:= C>O AND O>Ref(C,-1) AND C>=((H+L)/2)
	ES:= C<O AND O<Ref(C,-1) AND C<=((H+L)/2)
*/
int s55(struct datasys *x)									// Pattern Trading System 3
{

	int i=0;

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>x->open[i] AND x->open[i]>x->close[i-1]
			AND x->close[i]>=((x->high[i]+x->low[i])/(float)2))
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<x->open[i] AND x->open[i]<x->close[i-1]
			AND x->close[i]<=((x->high[i]+x->low[i])/(float)2))

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}
	
	*(x->elIsValid) = x->firstvalid+1;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+1;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+1;
	*(x->csIsValid) = x->firstvalid+1;

	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Pattern Trading System 4 *****
//	************************************
/*
This system works by a very simple pattern. It enters long when the price
closes above the high of two days ago and does it on more than 75% above the
monthly average volume. It closes the long position and enters a short
position when the price closes below the low of two days ago and does it on
more then 75% above the average monthly volume. 

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 20-Period Simple Moving Average of Volume
	
MetaStock Code:
	EL:= (C>Ref(H,-2) AND (V>1.75*Mov(V,20,S)))
	ES:= (C<Ref(L,-2) AND (V>1.75*Mov(V,20,S)))
*/
int s56(struct datasys *x)									// Pattern Trading System 4
{

	int i=0;
	float movstor=0;
	float *mov20;

	mov20=floatarray1;										// 20-Period Simple Moving Average of Volume

	if((x->lastvalid - x->firstvalid)<20) return 2;			// Return 2 if not enough data
															//	to calculate.

	for (i=x->firstvalid+19; i>=x->firstvalid; i--)			// 20-Period Moving Average of Volume
	{
		movstor=movstor+x->volume[i];
	}

	mov20[x->firstvalid+19]=(float)(movstor/20.0);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->volume[i] - x->volume[i-20];
		mov20[i] = (float)(movstor / 20.0);
	}

  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+19; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>x->high[i-2] AND (x->volume[i]>((float)1.75*mov20[i])))
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<x->low[i-2] AND (x->volume[i]>((float)1.75*mov20[i])))
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, mov20, sizeof(float)*65500);			// Ind1 = 20-Period Simple Moving Average of Volume
	
	*(x->elIsValid) = x->firstvalid+19;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+19;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+19;
	*(x->csIsValid) = x->firstvalid+19;
	*(x->ind1FirstValid) = x->firstvalid+19;

	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays

	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Pattern Trading System 5 *****
//	************************************
/*
This system also follows a short-term approach.

The primary pattern is determine by the whole bar (high, low, and close) being
higher than the whole bar of the previous day, the previous whole bar being
lower than the whole bar the day before that, and the whole bar of that day
being lower than the one before that. All of this needs to occur with the low
of the lowest bar still being above a 20-period moving average and Welles
Wilder's ADX being greater than 15 (The prices need to be in an uptrend). This
way, a long position is entered when prices are in a trend, pull back, and then
continue in the direction of the trend.

An exit occurs either 2 days after entry, or if the price falls below the
previous day's low.

The reverse would need to occur for short positions.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 20-Period Exponential Moving Average of Close
	Ind2 = 14-Period Average Directional Index
	
MetaStock Code:
	var1:=(H>Ref(H,-1) AND L>Ref(L,-1) AND C>Ref(C,-1)) AND
		(Ref(H,-1)<Ref(H,-2) AND Ref(L,-1)<Ref(L,-2) AND
		Ref(C,-1)<Ref(C,-2)) AND (Ref(H,-2)<Ref(H,-3) AND
		Ref(L,-2)<Ref(L,-3) AND Ref(C,-2)<Ref(C,-3)) AND
		Ref(L,-1)>Mov(C,20,E);
	var2:=(H<Ref(H,-1) AND L<Ref(L,-1) AND C<Ref(C,-1)) AND
		(Ref(H,-1)>Ref(H,-2) AND Ref(L,-1)>Ref(L,-2) AND
		Ref(C,-1)>Ref(C,-2)) AND (Ref(H,-2)>Ref(H,-3) AND
		Ref(L,-2)>Ref(L,-3) AND Ref(C,-2)>Ref(C,-3)) AND
		Ref(L,-1)<Mov(C,20,E);

	EL:=var1 AND ADX(14)>15
	CL:= Ref(var1,-2) OR L<Ref(L,-1)
	ES:= var2 AND ADX(14)>15
	CS:= Ref(var2,-2) OR H>Ref(H,-1)
*/
int s57(struct datasys *x)									// Pattern Trading System 5
{

	int i=0;
	int *var1, *var2;
	float th=0, tl=0, atr1=0, dmp=0, dmm=0, pdmcount=0, mdmcount=0, adxcount=0;
	float *atr14, *pdm, *mdm, *pdi, *mdi, *dx, *adx, *pdmfinal, *mdmfinal, *ema20;
	
	var1=intarray1;											// Pattern 5 Long Condition True or False (1 or 0)
	var2=intarray2;											// Pattern 5 Short Condition True or False (1 or 0)

	atr14=floatarray1;										// 14-Period Average True Range array
	pdm=floatarray2;										// 14-Period Plus Directional Movement array
	mdm=floatarray3;										// 14-Period Minus Directional Movement array
	pdi=floatarray4;										// 14-Period Plus Directional Indicator array
	mdi=floatarray5;										// 14-Period Minus Directional Indicator array
	dx=floatarray6;											// 14-Period Directional Index array
	adx=floatarray7;										// 14-Period Average Directional Index array
	pdmfinal=floatarray8;									// 14-Period Plus Directional Movement (Final) array
	mdmfinal=floatarray9;									// 14-Period Minus Directional Movement (Final) array
	ema20=floatarray10;										// 20-Period Exponential Moving Average of Close
	
	
	if((x->lastvalid - x->firstvalid)<28) return 2;			// Return 2 if not enough data
															//	to calculate.



	ema20[x->firstvalid]=x->close[x->firstvalid];			// 20-Period Exponential Moving Average of Close

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		ema20[i] = (float)(x->close[i] * (2.0/21.0)) + (float)(ema20[i-1] * (1.0-(2.0/21.0)));
	}



	for (i=x->firstvalid+1; i<=x->firstvalid+14; i++)		// 14-Day Average True Range 1st calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=atr1+(th-tl);
	}
	atr14[x->firstvalid+14]=(atr1/(float)14.0);


	for (i=x->firstvalid+15; i<=x->lastvalid; i++)			// 14-Day Average True Range continuous calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=th-tl;
		atr14[i]=(((atr14[i-1]*(float)13.0)+atr1)/(float)14.0);
	}

	
	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 14-day PDI and MDI calculation
	{
		if (x->high[i]>x->high[i-1]) dmp=(x->high[i]-x->high[i-1]);
			else dmp=0;
		if (x->low[i]<x->low[i-1]) dmm=(x->low[i-1]-x->low[i]);
			else dmm=0;
		if(dmp>dmm) pdm[i]=dmp;
			else pdm[i]=0;
		if(dmp<dmm) mdm[i]=dmm;
			else mdm[i]=0;
	}

	for (i=x->firstvalid+1; i<=x->firstvalid+14; i++)
	{
		pdmcount=pdmcount+pdm[i];
		mdmcount=mdmcount+mdm[i];
	}

	pdmfinal[x->firstvalid+14]=pdmcount/(float)14.0;
	mdmfinal[x->firstvalid+14]=mdmcount/(float)14.0;

	for (i=x->firstvalid+15; i<=x->lastvalid; i++)
	{
		pdmfinal[i]=((pdmfinal[i-1]*13)+pdm[i])/(float)14.0;
		mdmfinal[i]=((mdmfinal[i-1]*13)+mdm[i])/(float)14.0;
	}

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)
	{
		pdi[i]=round((pdmfinal[i]/atr14[i])*(float)100.0);	// 14-day PDI
		mdi[i]=round((mdmfinal[i]/atr14[i])*(float)100.0);	// 14-day MDI
		dx[i]=round(((float)fabs(pdi[i]-mdi[i])/(pdi[i]+mdi[i]))*(float)100.0);	// Directional Index
	}

															// Average Directional Index Calculation
	for (i=x->firstvalid+14; i<=x->firstvalid+27; i++) adxcount=adxcount+dx[i];

	adx[x->firstvalid+27]=adxcount/(float)14.0;

	for (i=x->firstvalid+28; i<=x->lastvalid; i++)
	{
		adx[i]=round(((adx[i-1]*13)+dx[i])/(float)14.0);
	}


	for (i=x->firstvalid+19; i<=x->lastvalid; i++)
	{
		if ((x->high[i]>x->high[i-1] AND x->low[i]>x->low[i-1] AND x->close[i]>x->close[i-1]) AND
			(x->high[i-1]<x->high[i-2] AND x->low[i-1]<x->low[i-2] AND x->close[i-1]<x->close[i-2]) AND
			(x->high[i-2]<x->high[i-3] AND x->low[i-2]<x->low[i-3] AND x->close[i-2]<x->close[i-3]) AND
			x->low[i-1]>ema20[i]) 
			
			var1[i]=1;


		if ((x->high[i]<x->high[i-1] AND x->low[i]<x->low[i-1] AND x->close[i]<x->close[i-1]) AND
			(x->high[i-1]>x->high[i-2] AND x->low[i-1]>x->low[i-2] AND x->close[i-1]>x->close[i-2]) AND
			(x->high[i-2]>x->high[i-3] AND x->low[i-2]>x->low[i-3] AND x->close[i-2]>x->close[i-3]) AND
			x->low[i-1]<ema20[i]) 
			
			var2[i]=1;
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+27; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (var1[i]==1 AND adx[i]>15)
			x->el[i]=1;

		if (var1[i-2]==1 OR x->low[i]<x->low[i-1])
			x->cl[i]=1;

		if (var2[i]==1 AND adx[i]>15)
			x->es[i]=1;

		if (var2[i-2]==1 OR x->high[i]>x->high[i-1])
			x->cs[i]=1;
	}
	
	memcpy (x->ind1, ema20, sizeof(float)*65500);			// Ind1 = 20-Period Exponential Moving Average of Close
	memcpy (x->ind2, adx, sizeof(float)*65500);				// Ind2 = 14-Period Average Directional Index


	*(x->elIsValid) = x->firstvalid+27;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+27;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+27;
	*(x->csIsValid) = x->firstvalid+27;
	*(x->ind1FirstValid) = x->firstvalid+19;
	*(x->ind2FirstValid) = x->firstvalid+27;


	bzero(intarray1,sizeof(int)*65500);						// Clean arrays
	bzero(intarray2,sizeof(int)*65500);

	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);
	bzero(floatarray10,sizeof(float)*65500);
		
	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Pattern Trading System 6 *****
//	************************************
/*
While more of a 'condition' rather than a pattern, this extremely simple system
takes a similar approach and enters long when a bar's high and low are both
greater than the previous bar's high and low. It then takes a short position
when the opposite condition occurs. While trading heavily, it still can produce
substantial profits.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	None
	
MetaStock Code:
	EL:= H>Ref(H,-1) AND L>Ref(L,-1)
	ES:= H<Ref(H,-1) AND L<Ref(L,-1)
*/
int s58(struct datasys *x)									// Pattern Trading System 6
{

	int i=0;

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->high[i]>x->high[i-1] AND x->low[i]>x->low[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->high[i]<x->high[i-1] AND x->low[i]<x->low[i-1])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}
	
	*(x->elIsValid) = x->firstvalid+1;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+1;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+1;
	*(x->csIsValid) = x->firstvalid+1;

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 1% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
1% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 1% Crossover Line
	
MetaStock Code:
	var1:=.01;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s59(struct datasys *x)									// Percentage Crossover 1%
{

	int i=0;
	float pcnt=(float).01;
	float *var1;

	var1=floatarray1;										// 1% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.


	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}

	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 1% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}





//	***********************************
//	***** Percentage Crossover 2% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
2% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 2% Crossover Line
	
MetaStock Code:
	var1:=.02;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s60(struct datasys *x)									// Percentage Crossover 2%
{

	int i=0;
	float pcnt=(float).02;
	float *var1;

	var1=floatarray1;										// 2% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 2% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 3% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
3% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 3% Crossover Line
	
MetaStock Code:
	var1:=.03;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s61(struct datasys *x)									// Percentage Crossover 3%
{

	int i=0;
	float pcnt=(float).03;
	float *var1;

	var1=floatarray1;										// 3% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.


	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 3% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 4% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
4% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 4% Crossover Line
	
MetaStock Code:
	var1:=.04;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s62(struct datasys *x)									// Percentage Crossover 4%
{

	int i=0;
	float pcnt=(float).04;
	float *var1;

	var1=floatarray1;										// 4% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.



	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 4% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 5% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
5% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 5% Crossover Line
	
MetaStock Code:
	var1:=.05;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s63(struct datasys *x)									// Percentage Crossover 5%
{

	int i=0;
	float pcnt=(float).05;
	float *var1;

	var1=floatarray1;										// 5% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 5% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 6% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
6% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 6% Crossover Line
	
MetaStock Code:
	var1:=.06;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s64(struct datasys *x)									// Percentage Crossover 6%
{

	int i=0;
	float pcnt=(float).06;
	float *var1;

	var1=floatarray1;										// 6% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 6% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 7% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
7% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 7% Crossover Line
	
MetaStock Code:
	var1:=.07;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s65(struct datasys *x)									// Percentage Crossover 7%
{

	int i=0;
	float pcnt=(float).07;
	float *var1;

	var1=floatarray1;										// 7% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 7% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 8% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
8% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 8% Crossover Line
	
MetaStock Code:
	var1:=.08;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s66(struct datasys *x)									// Percentage Crossover 8%
{

	int i=0;
	float pcnt=(float).08;
	float *var1;

	var1=floatarray1;										// 8% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 8% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Percentage Crossover 9% *****
//	***********************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
9% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 9% Crossover Line
	
MetaStock Code:
	var1:=.09;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s67(struct datasys *x)									// Percentage Crossover 9%
{

	int i=0;
	float pcnt=(float).09;
	float *var1;

	var1=floatarray1;										// 9% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 9% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Percentage Crossover 10% *****
//	************************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
10% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 10% Crossover Line
	
MetaStock Code:
	var1:=.1;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s68(struct datasys *x)									// Percentage Crossover 10%
{

	int i=0;
	float pcnt=(float).1;
	float *var1;

	var1=floatarray1;										// 10% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 10% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	************************************
//	***** Percentage Crossover 20% *****
//	************************************
/*
Unlike a typical trading system that reverses when a new entry signal occurs,
this one takes an opposite position only when an exit signal occurs. It is
effectively a trailing stop that enters a long or short position only when a
20% trailing stop is crossed. The advantage of this type of system is that it
is tailored to the price of the individual security that it is monitoring and
follows it closely to lock in profits. The disadvantage is that if the price
begins to cycle consistently then it will have excessive trading whipsaws.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 20% Crossover Line
	
MetaStock Code:
	var1:=.2;
	var2:=If((C*(1-var1))>PREV,C*(1-var1),If((C*(1+var1))<PREV,C*(1+var1),PREV));

	EL:=Cross(C,var2)
	ES:=Cross(var2,C)
*/
int s69(struct datasys *x)									// Percentage Crossover 20%
{

	int i=0;
	float pcnt=(float).2;
	float *var1;

	var1=floatarray1;										// 20% Crossover Line

	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.

	var1[x->firstvalid]=x->close[x->firstvalid];

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		if ((x->close[i]*((float)1-pcnt))>var1[i-1]) var1[i]=x->close[i]*((float)1-pcnt);
		else if ((x->close[i]*((float)1+pcnt))<var1[i-1]) var1[i]=x->close[i]*((float)1+pcnt);
		else var1[i]=var1[i-1];
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>var1[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<var1[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, var1, sizeof(float)*65500);			// Ind1 = 20% Crossover Line
	
	*(x->elIsValid) = x->firstvalid;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid;						//	for each output array.
	*(x->esIsValid) = x->firstvalid;
	*(x->csIsValid) = x->firstvalid;
	*(x->ind1FirstValid) = x->firstvalid;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays

	return 0;												// Return NULL for valid system.
}




//	****************************************
//	***** Polarized Fractal Efficiency *****
//	****************************************
/*
Dr. Al Larsen (Hans Hannula) of MicroMedia developed the Polarized Fractal
Efficiency (PFE) indicator and published it in the January 1994 issue of
Technical Analysis of Stocks and Commodities magazine. The PFE indicator by
itself has a variable minimum and maximum position that is dependent upon the
price and movement of the underlying security. For this system, the PFE was
'normalized' by taking the stochastic of the PFE, but using the available data
in the chart to generate the length of the stochastic, rather than using a
fixed stochastic length. 

After the stochastic is performed, the PFE no longer has a true zero crossing
point. The system will enter a long position when the PFE crosses above a
simulated zero crossing point, being the 50% point of the stochastic. It will
then stay in the position until the PFE either crosses above the 80% point of
the stochastic (locking in profits) or when it crosses back below the 50% point
of the stochastic (acting as a stop-loss). The reverse would be true for short
positions, except that it will lock in profits when the PFE stochastic crosses
below 20%.

Note that there are two MetaStock code sets. The first is the code set using
MetaStock's built'in Polarized Fractal Efficiency function. Equis had their PFE
function fine-tuned by Hans Hannula personally and that algorithm is not
available to anyone else. The second system uses the PFE as described in
"Stocks and Commodities" magazine. Unfortunately, the indicator, and hence the
trading results, are significantly different from the authors published
description. For the purpose of this system here, we followed the second
system.

 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Polarized Fractal Efficiency (Final)
	
MetaStock Code:
 ** Original System **
	var1:=(PFE(C,34,3)-Lowest(PFE(C,34,3)))/(Highest(PFE(C,34,3))-Lowest(PFE(C,34,3)));

	EL:=Cross(var1,.5)
	CL:= Cross(.5,var1) OR Cross(var1,.8)
	ES:= Cross(.5,var1)
	CS:= Cross(var1,.5) OR Cross(.2,var1)

 ** Implemented System **
	PFE2:=Mov(If(C,>,Ref(C,-9),Sqr(Pwr(Roc(C,9,$),2) + Pwr(10,2)) / 
		Sum(Sqr(Pwr(Roc(C,1,$),2)+1),9),- Sqr(Pwr(Roc(C,9,$),2) + Pwr(10,2)) /
		Sum(Sqr(Pwr(Roc(C,1,$),2)+1),9))*100,5,E)

	var1:=(PFE2(C,34,3)-Lowest(PFE2(C,34,3)))/(Highest(PFE2(C,34,3))-Lowest(PFE2(C,34,3)));

	EL:=Cross(var1,.5)
	CL:= Cross(.5,var1) OR Cross(var1,.8)
	ES:= Cross(.5,var1)
	CS:= Cross(var1,.5) OR Cross(.2,var1)
*/
int s70(struct datasys *x)									// Polarized Fractal Efficiency
{

	int i=0, j=0;
	float sumden=0, highest=0, lowest=0;
	float *pfe34, *sqrdenport, *sumdenport2;
	float *sqrnum, *ema3, *pfefinal;

	pfe34=floatarray1;										// 34-Period Polarized Fractal Efficiency (PFE)
	sqrdenport=floatarray2;									// Squared Denominator Portion
	sumdenport2=floatarray3;								// Summed Denominator Portion (2)
	sqrnum=floatarray4;										// Squared Numerator
	ema3=floatarray5;										// 3-Period Exp. Moving Average of pfe34
	pfefinal=floatarray6;									// PFE Stochastic of Cumulated Highs and Lows


	if((x->lastvalid - x->firstvalid)<37) return 2;			// Return 2 if not enough data
															//	to calculate.

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Begin Polarized Fractal Efficiency Calculation
		sqrdenport[i]=(float)sqrt((float)pow(x->close[i]-x->close[i-1],2)+1);

	for (i=x->firstvalid+33; i<=x->lastvalid; i++)
	{
		sumden=0;

		for (j=i-32; j<=i; j++)								// ** There has to be a way to make this more efficient **
			sumden=sumden+sqrdenport[j];

		sumdenport2[i]=sumden;

		sqrnum[i]=(float)sqrt((float)pow(x->close[i]-x->close[i-33],2)+pow(34,2));

		if (x->close[i]>x->close[i-33])
			pfe34[i]= (sqrnum[i]/sumdenport2[i])*(float)100;
		else pfe34[i]= (0-(sqrnum[i]/sumdenport2[i]))*(float)100;

	}


	ema3[x->firstvalid+33]=pfe34[x->firstvalid+33];			// 3-Period Exponential Moving Average of PFE-34

	for (i=x->firstvalid+34; i<=x->lastvalid; i++)
	{
		ema3[i] = (float)(pfe34[i]*(float).5) + (float)(ema3[i-1]*(float).5);

		if(ema3[i]>highest) highest=ema3[i];
		if(ema3[i]<lowest) lowest=ema3[i];

		pfefinal[i]=(ema3[i]-lowest)/(highest-lowest);
	}



	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+36; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (pfefinal[i]>(float).5 AND pfefinal[i-1]<.5)
			x->el[i]=1;

		if ((pfefinal[i]<(float).5 AND pfefinal[i-1]>.5) OR (pfefinal[i]>(float).8 AND pfefinal[i-1]<.8))
			x->cl[i]=1;

		if (pfefinal[i]<(float).5 AND pfefinal[i-1]>.5)
			x->es[i]=1;

		if ((pfefinal[i]>(float).5 AND pfefinal[i-1]<.5) OR (pfefinal[i]<(float).2 AND pfefinal[i-1]>.2))
			x->cs[i]=1;
	}

	memcpy (x->ind1, pfefinal, sizeof(float)*65500);		// Ind1 = Polarized Fractal Efficiency (Final)
	
	*(x->elIsValid) = x->firstvalid+36;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+36;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+36;
	*(x->csIsValid) = x->firstvalid+36;
	*(x->ind1FirstValid) = x->firstvalid+34;

	
	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Projection Oscillator 1 *****
//	***********************************
/*
The Projection oscillator is basically a slope-adjusted Stochastic developed by
Mel Widner, Ph.D. and was published in the July 1995 issue of Technical
Analysis of Stocks and Commodities magazine. It's an indicator that identifies
its position relative to the projection bands. For this system, rather than
trade the oscillator in relation to a 20/80 position like a regular stochastic
oscillator, a short-term smoothed projection oscillator is traded in relation
to an even shorter-term moving average of itself.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 3-Period Exponential Moving Average of 8-Period Projection Oscillator
	Ind2 = 3-Period Simple Moving Average of Smoothed Projection Oscillator (projosc)
	
MetaStock Code:
	EL:= Cross(ProjOsc(8,3),Mov(ProjOsc(8,3),3,S))
	ES:= Cross(Mov(ProjOsc(8,3),3,S),ProjOsc(8,3))
*/
int s71(struct datasys *x)									// Projection Oscillator 1
{

	int i=0, j=0;
	float sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0;
	float sumnum=0, sumden=0, movstor=0, maxtest=0, mintest=0;
	float *lrslopehigh, *lrslopelow, *pbhigh, *pblow, *potemp, *projosc, *mov3;

	lrslopehigh=floatarray1;								// 8-Period Linear Regression Slope of Highs
	lrslopelow=floatarray2;									// 8-Period Linear Regression Slope of Lows
	pbhigh=floatarray3;										// Projection Bands of Highs
	pblow=floatarray4;										// Projection Bands of Lows
	potemp=floatarray5;										// 8-Period Projection Oscillator
	projosc=floatarray6;									// 3-Period Exponential Moving Average of Projection Oscillator
	mov3=floatarray7;										// 3-Period Simple Moving Average of Smoothed Projection Oscillator
															//	(projosc)

	if((x->lastvalid - x->firstvalid)<17) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+7; i<=x->lastvalid; i++)			// 8-Period Linear Regression Slope of Highs
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-7; j<=i; j++)
		{
			sum1=sum1+((float)j*x->high[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->high[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+7)
			{
				movc=movc+x->high[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+7)
		{
			movc=movc-x->high[i-8]+x->high[i];
			movcum=movcum-(i-8)+i;
		}

		lrslopehigh[i]=
			(sum1-((sum2*sum3)/8))/(sum4-(((float)pow(sum2,2))/(float)8));
	}

	movc=0;
	movcum=0;

	for (i=x->firstvalid+7; i<=x->lastvalid; i++)			// 8-Period Linear Regression Slope of Lows
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-7; j<=i; j++)
		{
			sum1=sum1+((float)j*x->low[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->low[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+7)
			{
				movc=movc+x->low[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+7)
		{
			movc=movc-x->low[i-8]+x->low[i];
			movcum=movcum-(i-8)+i;
		}

		lrslopelow[i]=
			(sum1-((sum2*sum3)/8))/(sum4-(((float)pow(sum2,2))/(float)8));
	}




	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Projection Bands of Highs and Lows
	{

		maxtest=0;
		mintest=0;

		for (j=i; j>=i-7; j--)
		{
			if(j==i)
			{
				maxtest=x->high[i];
				mintest=x->low[i];
			}
			else
			{
				maxtest=__max(maxtest,x->high[j]+((i-j)*lrslopehigh[i]));
				mintest=__min(mintest,x->low[j]+((i-j)*lrslopelow[i]));
			}
		}

		pbhigh[i]=maxtest;
		pblow[i]=mintest;

		potemp[i]=((x->close[i]-pblow[i])/(pbhigh[i]-pblow[i]))*100;
	}


	projosc[x->firstvalid+14]=potemp[x->firstvalid+16];		// 3-Period Exponential Moving Average of Projection Oscillator

	for (i=x->firstvalid+15; i<=x->lastvalid; i++)
	{
		projosc[i] = (float)(potemp[i]*(float).5)+(float)(projosc[i-1]*(float).5);
	}





	for (i=x->firstvalid+16; i>=x->firstvalid; i--)			// 3-Period Simple Moving Average of
	{														//	Smoothed Projection Oscillator
		movstor=movstor+projosc[i];
	}

	mov3[x->firstvalid+16]=(float)(movstor/3.0);

	for (i=x->firstvalid+17; i<=x->lastvalid; i++)
	{
		movstor = movstor + projosc[i] - projosc[i-3];
		mov3[i] = (float)(movstor / 3.0);
	}



	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+16; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (projosc[i]>mov3[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (projosc[i]<mov3[i])
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, projosc, sizeof(float)*65500);			// Ind1 = 3-Period Exponential Moving Average of
															//	8-Period Projection Oscillator
	memcpy (x->ind2, mov3, sizeof(float)*65500);			// Ind2 = 3-Period Simple Moving Average of
															//	Smoothed Projection Oscillator (projosc)
	
	*(x->elIsValid) = x->firstvalid+16;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+16;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+16;
	*(x->csIsValid) = x->firstvalid+16;
	*(x->ind1FirstValid) = x->firstvalid+14;
	*(x->ind2FirstValid) = x->firstvalid+16;


	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Projection Oscillator 2 *****
//	***********************************
/*
The Projection oscillator is basically a slope-adjusted Stochastic developed by
Mel Widner, Ph.D. and was published in the July 1995 issue of Technical
Analysis of Stocks and Commodities magazine. It's an indicator that identifies
its position relative to the projection bands. For this system, the Projection
Oscillator is traded using a standard Stochastic method except that a
30/70 position is used to determine an oversold/overbought state instead of a
20/80 position like a regular Stochastic oscillator.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 3-Period Exponential Moving Average of 14-Period Projection Oscillator
	
MetaStock Code:
	EL:= Cross(ProjOsc(14,3),30)
	ES:= Cross(70,ProjOsc(14,3))
*/
int s72(struct datasys *x)									// Projection Oscillator 2
{

	int i=0, j=0;
	float sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0;
	float sumnum=0, sumden=0, movstor=0, maxtest=0, mintest=0;
	float *lrslopehigh, *lrslopelow, *pbhigh, *pblow, *potemp, *projosc;

	lrslopehigh=floatarray1;								// 14-Period Linear Regression Slope of Highs
	lrslopelow=floatarray2;									// 14-Period Linear Regression Slope of Lows
	pbhigh=floatarray3;										// Projection Bands of Highs
	pblow=floatarray4;										// Projection Bands of Lows
	potemp=floatarray5;										// 14-Period Projection Oscillator
	projosc=floatarray6;									// 3-Period Exponential Moving Average of Projection Oscillator


	if((x->lastvalid - x->firstvalid)<28) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+13; i<=x->lastvalid; i++)			// 14-Period Linear Regression Slope of Highs
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-13; j<=i; j++)
		{
			sum1=sum1+((float)j*x->high[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->high[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+13)
			{
				movc=movc+x->high[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+13)
		{
			movc=movc-x->high[i-14]+x->high[i];
			movcum=movcum-(i-14)+i;
		}

		lrslopehigh[i]=
			(sum1-((sum2*sum3)/14))/(sum4-(((float)pow(sum2,2))/(float)14));
	}

	movc=0;
	movcum=0;

	for (i=x->firstvalid+13; i<=x->lastvalid; i++)			// 14-Period Linear Regression Slope of Lows
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-13; j<=i; j++)
		{
			sum1=sum1+((float)j*x->low[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->low[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+13)
			{
				movc=movc+x->low[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+13)
		{
			movc=movc-x->low[i-14]+x->low[i];
			movcum=movcum-(i-14)+i;
		}

		lrslopelow[i]=
			(sum1-((sum2*sum3)/14))/(sum4-(((float)pow(sum2,2))/(float)14));
	}


	for (i=x->firstvalid+26; i<=x->lastvalid; i++)			// Projection Bands of Highs and Lows
	{

		maxtest=0;
		mintest=0;

		for (j=i; j>=i-13; j--)
		{
			if(j==i)
			{
				maxtest=x->high[i];
				mintest=x->low[i];
			}
			else
			{
				maxtest=__max(maxtest,x->high[j]+((i-j)*lrslopehigh[i]));
				mintest=__min(mintest,x->low[j]+((i-j)*lrslopelow[i]));
			}
		}

		pbhigh[i]=maxtest;
		pblow[i]=mintest;

		potemp[i]=((x->close[i]-pblow[i])/(pbhigh[i]-pblow[i]))*100;
	}

	projosc[x->firstvalid+26]=potemp[x->firstvalid+26];		// 3-Period Exponential Moving Average of Projection Oscillator

	for (i=x->firstvalid+27; i<=x->lastvalid; i++)
	{
		projosc[i] = (float)(potemp[i]*(float).5)+(float)(projosc[i-1]*(float).5);
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+27; i<=x->lastvalid; i++)				// Calculate system signals and
	{														//	copy to output arrays.
		if (projosc[i]>30 AND projosc[i-1]<30)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (projosc[i]<70 AND projosc[i-1]>70)
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, projosc, sizeof(float)*65500);			// Ind1 = 3-Period Exponential Moving Average of
															//	14-Period Projection Oscillator


	*(x->elIsValid) = x->firstvalid+27;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+27;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+27;
	*(x->csIsValid) = x->firstvalid+27;
	*(x->ind1FirstValid) = x->firstvalid+26;

	bzero(floatarray1,sizeof(float)*65500);					// Clean arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Relative Momentum Index *****
//	***********************************
/*
The Relative Momentum Index (RMI) was developed by Roger Altman and published
in the February 1993 issue of Technical Analysis of Stocks and Commodities
magazine. The RMI is a variation of an RSI, except that it calculates relative
strength of momentum instead of relative strength of prices.

The system is traded the same way that an RSI is typically traded. It enters a
long position when the RMI crosses above 30, moving out of an oversold
condition. It then exits the long position when the RMI rises and then crosses
below 70, moving out of an overbought condition. The reverse is for short
positions.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 20-Period Relative Momentum Index (RMI)
	
MetaStock Code:
	EL:=Cross(RMI(C,20,5),30)
	ES:= Cross(70,RMI(C,20,5))
*/
int s73(struct datasys *x)									// Relative Momentum Index
{

	int i=0;
	float rsiup=0, rsidown=0;
	float *rmi;

	rmi=floatarray1;										// Relative Momentum Index Indicator

	if((x->lastvalid - x->firstvalid)<26) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+5; i<=x->firstvalid+24; i++)		// 20-Period Relative Momentum Index (RMI)
	{
		if(x->close[i]>x->close[i-5]) rsiup=rsiup+(x->close[i]-x->close[i-5]);
		if(x->close[i]<x->close[i-5]) rsidown=rsidown+(x->close[i-5]-x->close[i]);
	}

	if(rsidown==0) rsidown=(float).0001;					// (To prevent divide by zero error)

	rmi[x->firstvalid+24]=100-(100/(1+(rsiup/rsidown)));

	rsiup=rsiup/(float)20;
	rsidown=rsidown/(float)20;

	for (i=x->firstvalid+25; i<=x->lastvalid; i++)
	{
		if(x->close[i]>x->close[i-5])
			rsiup=(rsiup*((float)19/(float)20))+((x->close[i]-x->close[i-5])*((float)1/(float)20));
		else 
			rsiup=rsiup*((float)19/(float)20);

		if(x->close[i]<x->close[i-5])
			rsidown=(rsidown*((float)19/(float)20))+((x->close[i-5]-x->close[i])*((float)1/(float)20));
		else 
			rsidown=rsidown*((float)19/(float)20);

		rmi[i]=100-(100/(1+(rsiup/rsidown)));
	}


	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+25; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (rmi[i]>30 AND rmi[i-1]<30)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (rmi[i]<70 AND rmi[i-1]>70)
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, rmi, sizeof(float)*65500);				// Ind1 = 20-Period Relative Momentum Index (RMI)


	*(x->elIsValid) = x->firstvalid+25;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+25;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+25;
	*(x->csIsValid) = x->firstvalid+25;
	*(x->ind1FirstValid) = x->firstvalid+24;


	bzero(floatarray1,sizeof(float)*65500);					// Clean array

	return 0;												// Return NULL for valid system.
}




//	***************************************
//	***** Relative Volatility Index 1 *****
//	***************************************
/*
The Relative Volatility Index (RMI) was developed by Donald Dorsey and
published in the June 1993 issue of Technical Analysis of Stocks and
Commodities magazine. The RVI is a variation of an RSI, except that it
calculates relative strength of the standard deviation of price changes instead
of relative strength of prices.

This system is traded the same way that an RSI is typically traded. It enters a
long position when the RMI crosses above 30, moving out of an oversold
condition. It then exits the long position when the RMI rises and then crosses
below 70, moving out of an overbought condition. The reverse is for short
positions.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = New Relative Volatility Index
	
MetaStock Code:
	EL:= Cross(RVI(14),30)
	ES:= Cross(70,RVI(14))
*/
int s74(struct datasys *x)									// Relative Volatility Index 1
{
	int i=0, j=0;
	float movstor=0, stdstor=0;
	float *movhigh10, *stdevhigh, *movlow10, *stdevlow;
	float *highup, *highdown, *lowup, *lowdown;
	float *movhighup, *movhighdown, *movlowup, *movlowdown;
	float *rvih, *rvil, *newrvi;

	movhigh10=floatarray1;									// 10-Period Moving Average of Highs
	stdevhigh=floatarray2;									// 10-Period Standard Deviation of Highs
	movlow10=floatarray3;									// 10-Period Moving Average of Lows
	stdevlow=floatarray4;									// 10-Period Standard Deviation of Lows
	highup=floatarray5;										// Up Moves of Standard Deviation of Highs
	highdown=floatarray6;									// Down Moves of Standard Deviation of Highs
	lowup=floatarray7;										// Up Moves of Standard Deviation of Lows
	lowdown=floatarray8;									// Down Moves of Standard Deviation of Lows
	movhighup=floatarray9;									// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (up)
	movhighdown=floatarray10;								// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (down)
	movlowup=floatarray11;									// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (up)
	movlowdown=floatarray12;								// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (down)
	rvih=floatarray13;										// Relative Volatility Index of Highs
	rvil=floatarray14;										// Relative Volatility Index of Lows
	newrvi=floatarray15;									// New Relative Volatility Index


	if((x->lastvalid - x->firstvalid)<24) return 2;			// Return 2 if not enough data
															//	to calculate.

	
	for (i=x->firstvalid+9; i>=x->firstvalid; i--)			// 10-Period Moving Average of Highs
	{
		movstor=movstor+x->high[i];
	}

	movhigh10[x->firstvalid+9]=(float)(movstor/10.0);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->high[i] - x->high[i-10];
		movhigh10[i] = (float)(movstor / 10.0);
	}

	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Highs
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->high[j]-movhigh10[i],2);
		}

		stdevhigh[i]= (float)sqrt(stdstor/10.0);
	}

	movstor=0;
	stdstor=0;

	for (i=x->firstvalid+9; i>=x->firstvalid; i--)			// 10-Period Moving Average of Lows
	{
		movstor=movstor+x->low[i];
	}

	movlow10[x->firstvalid+9]=(float)(movstor/10.0);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->low[i] - x->low[i-10];
		movlow10[i] = (float)(movstor / 10.0);
	}

	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Lows
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->low[j]-movlow10[i],2);
		}

		stdevlow[i]= (float)sqrt(stdstor/10.0);
	}


	for (i=x->firstvalid+9; i<=x->lastvalid; i++)
	{
		if(x->high[i]>x->high[i-1]) highup[i]=stdevhigh[i];
		if(x->high[i]<x->high[i-1]) highdown[i]=stdevhigh[i];

		if(x->low[i]>x->low[i-1]) lowup[i]=stdevlow[i];
		if(x->low[i]<x->low[i-1]) lowdown[i]=stdevlow[i];
	}




	movhighup[x->firstvalid+9]=highup[x->firstvalid+9];		// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (up)

	movhighdown[x->firstvalid+9]=highdown[x->firstvalid+9];	// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (down)

	movlowup[x->firstvalid+9]=lowup[x->firstvalid+9];		// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (up)

	movlowdown[x->firstvalid+9]=lowdown[x->firstvalid+9];	// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (down)

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movhighup[i] = (float)(highup[i] * (1.0/14.0)) + (float)(movhighup[i-1] * (1.0-(1.0/14.0)));
		movhighdown[i] = (float)(highdown[i] * (1.0/14.0)) + (float)(movhighdown[i-1] * (1.0-(1.0/14.0)));
		movlowup[i] = (float)(lowup[i] * (1.0/14.0)) + (float)(movlowup[i-1] * (1.0-(1.0/14.0)));
		movlowdown[i] = (float)(lowdown[i] * (1.0/14.0)) + (float)(movlowdown[i-1] * (1.0-(1.0/14.0)));

		rvih[i]=100*movhighup[i]/(movhighup[i]+movhighdown[i]);
		rvil[i]=100*movlowup[i]/(movlowup[i]+movlowdown[i]);

		newrvi[i]=(rvih[i]+rvil[i])/2;
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+23; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (newrvi[i]>30 AND newrvi[i-1]<30)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (newrvi[i]<70 AND newrvi[i-1]>70)
		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, newrvi, sizeof(float)*65500);			// Ind1 = New Relative Volatility Index


	*(x->elIsValid) = x->firstvalid+23;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+23;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+23;
	*(x->csIsValid) = x->firstvalid+23;
	*(x->ind1FirstValid) = x->firstvalid+22;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);
	bzero(floatarray10,sizeof(float)*65500);
	bzero(floatarray11,sizeof(float)*65500);
	bzero(floatarray12,sizeof(float)*65500);
	bzero(floatarray13,sizeof(float)*65500);
	bzero(floatarray14,sizeof(float)*65500);
	bzero(floatarray15,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***************************************
//	***** Relative Volatility Index 2 *****
//	***************************************
/*
The Relative Volatility Index (RMI) was developed by Donald Dorsey and
published in the June 1993 issue of Technical Analysis of Stocks and
Commodities magazine. The RVI is a variation of an RSI, except that it
calculates relative strength of the standard deviation of price changes instead
of relative strength of prices.

This system is traded the same way that an RSI is typically traded. It enters a
long position when the RMI crosses above 40, moving out of an oversold
condition. It then exits the long position when the RMI rises and then crosses
below 40, moving out of an overbought condition. The reverse is for short
positions. These different parameters form the "Relative Volatility Index 1"
system makes this system increase the number of trades significantly.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = New Relative Volatility Index
	
MetaStock Code:
	EL:=Cross(RVI(14),40)
	ES:= Cross(60,RVI(14))
*/
int s75(struct datasys *x)									// Relative Volatility Index 2
{
	int i=0, j=0;
	float movstor=0, stdstor=0;
	float *movhigh10, *stdevhigh, *movlow10, *stdevlow;
	float *highup, *highdown, *lowup, *lowdown;
	float *movhighup, *movhighdown, *movlowup, *movlowdown;
	float *rvih, *rvil, *newrvi;

	movhigh10=floatarray1;									// 10-Period Moving Average of Highs
	stdevhigh=floatarray2;									// 10-Period Standard Deviation of Highs
	movlow10=floatarray3;									// 10-Period Moving Average of Lows
	stdevlow=floatarray4;									// 10-Period Standard Deviation of Lows
	highup=floatarray5;										// Up Moves of Standard Deviation of Highs
	highdown=floatarray6;									// Down Moves of Standard Deviation of Highs
	lowup=floatarray7;										// Up Moves of Standard Deviation of Lows
	lowdown=floatarray8;									// Down Moves of Standard Deviation of Lows
	movhighup=floatarray9;									// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (up)
	movhighdown=floatarray10;								// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (down)
	movlowup=floatarray11;									// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (up)
	movlowdown=floatarray12;								// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (down)
	rvih=floatarray13;										// Relative Volatility Index of Highs
	rvil=floatarray14;										// Relative Volatility Index of Lows
	newrvi=floatarray15;									// New Relative Volatility Index


	if((x->lastvalid - x->firstvalid)<24) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+9; i>=x->firstvalid; i--)			// 10-Period Moving Average of Highs
	{
		movstor=movstor+x->high[i];
	}

	movhigh10[x->firstvalid+9]=(float)(movstor/10.0);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->high[i] - x->high[i-10];
		movhigh10[i] = (float)(movstor / 10.0);
	}

	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Highs
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->high[j]-movhigh10[i],2);
		}

		stdevhigh[i]= (float)sqrt(stdstor/10.0);
	}

	movstor=0;
	stdstor=0;

	for (i=x->firstvalid+9; i>=x->firstvalid; i--)			// 10-Period Moving Average of Lows
	{
		movstor=movstor+x->low[i];
	}

	movlow10[x->firstvalid+9]=(float)(movstor/10.0);

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->low[i] - x->low[i-10];
		movlow10[i] = (float)(movstor / 10.0);
	}

	
	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Lows
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(x->low[j]-movlow10[i],2);
		}

		stdevlow[i]= (float)sqrt(stdstor/10.0);
	}


	for (i=x->firstvalid+9; i<=x->lastvalid; i++)
	{
		if(x->high[i]>x->high[i-1]) highup[i]=stdevhigh[i];
		if(x->high[i]<x->high[i-1]) highdown[i]=stdevhigh[i];

		if(x->low[i]>x->low[i-1]) lowup[i]=stdevlow[i];
		if(x->low[i]<x->low[i-1]) lowdown[i]=stdevlow[i];
	}




	movhighup[x->firstvalid+9]=highup[x->firstvalid+9];		// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (up)

	movhighdown[x->firstvalid+9]=highdown[x->firstvalid+9];	// 14-Period Exponential Moving Average of
															//	Standard Deviations of highs (down)

	movlowup[x->firstvalid+9]=lowup[x->firstvalid+9];		// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (up)

	movlowdown[x->firstvalid+9]=lowdown[x->firstvalid+9];	// 14-Period Exponential Moving Average of
															//	Standard Deviations of lows (down)

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		movhighup[i] = (float)(highup[i] * (1.0/14.0)) + (float)(movhighup[i-1] * (1.0-(1.0/14.0)));
		movhighdown[i] = (float)(highdown[i] * (1.0/14.0)) + (float)(movhighdown[i-1] * (1.0-(1.0/14.0)));
		movlowup[i] = (float)(lowup[i] * (1.0/14.0)) + (float)(movlowup[i-1] * (1.0-(1.0/14.0)));
		movlowdown[i] = (float)(lowdown[i] * (1.0/14.0)) + (float)(movlowdown[i-1] * (1.0-(1.0/14.0)));

		rvih[i]=100*movhighup[i]/(movhighup[i]+movhighdown[i]);
		rvil[i]=100*movlowup[i]/(movlowup[i]+movlowdown[i]);

		newrvi[i]=(rvih[i]+rvil[i])/2;
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+23; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (newrvi[i]>40 AND newrvi[i-1]<40)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (newrvi[i]<60 AND newrvi[i-1]>60)

		{
			x->cl[i]=1;
			x->es[i]=1;
		}
	}

	memcpy (x->ind1, newrvi, sizeof(float)*65500);			// Ind1 = New Relative Volatility Index
	
	*(x->elIsValid) = x->firstvalid+23;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+23;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+23;
	*(x->csIsValid) = x->firstvalid+23;
	*(x->ind1FirstValid) = x->firstvalid+22;



	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	bzero(floatarray7,sizeof(float)*65500);
	bzero(floatarray8,sizeof(float)*65500);
	bzero(floatarray9,sizeof(float)*65500);
	bzero(floatarray10,sizeof(float)*65500);
	bzero(floatarray11,sizeof(float)*65500);
	bzero(floatarray12,sizeof(float)*65500);
	bzero(floatarray13,sizeof(float)*65500);
	bzero(floatarray14,sizeof(float)*65500);
	bzero(floatarray15,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	*****************************
//	***** RSI Trailing Exit *****
//	*****************************
/*
This is a traditional Welles Wilder RSI system with some small modifications.
To enter long, it first looks for an RSI crossing above 30 while also being
above a 3-period moving average of itself. Second, it sets a stop-loss by
exiting a position if the RSI crosses back below 30. Third, it exits when the
RSI is above 70 and it crosses below the 3-period moving average of itself. The
combination of these three conditions allows for increased robustness over the
traditional RSI overbought/oversold rules by itself.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 14-Period Relative Strength Index
	Ind2 = 3-Periodd Simple Moving Average of Relative Strength Index
	
MetaStock Code:
	EL:= RSI(14)>Mov(RSI(14),3,S) AND Cross(RSI(14),30)
	CL:= Cross(30,RSI(14)) OR (RSI(14)<Mov(RSI(14),3,S) AND RSI(14)>70)
	ES:= RSI(14)<Mov(RSI(14),3,S) AND Cross(70,RSI(14))
	CS:= Cross(RSI(14),70) OR (RSI(14)>Mov(RSI(14),3,S) AND RSI(14)<30)
*/
int s76(struct datasys *x)									// RSI Trailing Exit
{

	int i=0;
	float rsiup=0, rsidown=0, movstor=0;
	float *rsi, *mov3;

	rsi=floatarray1;										// 14-Period Relative Strength Index (RSI)
	mov3=floatarray2;										// 3-Period Simple Moving Average of RSI


	if((x->lastvalid - x->firstvalid)<16) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->firstvalid+13; i++)		// 14-Period Relative Strength Index (RSI)
	{
		if(x->close[i]>x->close[i-1]) rsiup=rsiup+(x->close[i]-x->close[i-1]);
		if(x->close[i]<x->close[i-1]) rsidown=rsidown+(x->close[i-1]-x->close[i]);
	}

	if(rsidown==0) rsidown=(float).0001;					// (To prevent divide by zero error)

	rsi[x->firstvalid+13]=100-(100/(1+(rsiup/rsidown)));

	rsiup=rsiup/(float)14;
	rsidown=rsidown/(float)14;

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)
	{
		if(x->close[i]>x->close[i-1])
			rsiup=(rsiup*((float)13/(float)14))+((x->close[i]-x->close[i-1])*((float)1/(float)14));
		else 
			rsiup=rsiup*((float)13/(float)14);

		if(x->close[i]<x->close[i-1])
			rsidown=(rsidown*((float)13/(float)14))+((x->close[i-1]-x->close[i])*((float)1/(float)14));
		else 
			rsidown=rsidown*((float)13/(float)14);

		rsi[i]=100-(100/(1+(rsiup/rsidown)));
	}



	for (i=x->firstvalid+15; i>=x->firstvalid; i--)			// 3-Period Moving Average of RSI
	{
		movstor=movstor+rsi[i];
	}

	mov3[x->firstvalid+15]=(float)(movstor/3.0);

	for (i=x->firstvalid+16; i<=x->lastvalid; i++)
	{
		movstor = movstor + rsi[i] - rsi[i-3];
		mov3[i] = (float)(movstor / 3.0);
	}



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+15; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (rsi[i]>mov3[i] AND rsi[i]>30 AND rsi[i-1]<30)
			x->el[i]=1;

		if ((rsi[i]<30 AND rsi[i-1]>30) OR (rsi[i]<mov3[i] AND rsi[i]>70))
			x->cl[i]=1;

		if (rsi[i]<mov3[i] AND rsi[i]<70 AND rsi[i-1]>70)
			x->es[i]=1;

		if ((rsi[i]>70 AND rsi[i-1]<70) OR (rsi[i]>mov3[i] AND rsi[i]<30))
			x->cs[i]=1;
	}

	memcpy (x->ind1, rsi, sizeof(float)*65500);				// Ind1 = 14-Period Relative Strength Index
	memcpy (x->ind2, mov3, sizeof(float)*65500);			// Ind2 = 3-Periodd Simple Moving Average of Relative Strength Index


	*(x->elIsValid) = x->firstvalid+15;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+15;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+15;
	*(x->csIsValid) = x->firstvalid+15;
	*(x->ind1FirstValid) = x->firstvalid+13;
	*(x->ind2FirstValid) = x->firstvalid+15;


	
	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	**************************************
//	***** Short Term Range Rejection *****
//	**************************************
/*
Unlike other trading range systems that look for a breakout, this system
specifically looks for the absence of a trading range and then takes trades in
the direction of the short and intermediate-term linear regression slopes. The
system reverses whenever the short and intermediate-term linear regression
slopes move above/below the zero line. The system exits any position when
either the intermediate-term linear regression slope crosses the zero line, or
whenever a trading range is entered.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 21-Period Highest High Value of Close
	Ind2 = 21-Period Lowest Low Value of Close
	Ind3 = 21-Period Simple Moving Average of Close
	Ind4 = 5-Period Linear Regression Slope
	Ind5 = 21-Period Linear Regression Slope
	
MetaStock Code:
	var1:=HHV(C,21)<1.1*Mov(C,21,S) AND LLV(C,21)>0.9*Mov(C,21,S);

	EL:=var1=0 AND LinRegSlope(C,5)>0 AND LinRegSlope(C,21)>0
	CL:= var1=1 OR LinRegSlope(C,21)<0
	ES:= var1=0 AND LinRegSlope(C,5)<0 AND LinRegSlope(C,21)<0
	CS:= var1=1 OR LinRegSlope(C,21)>0
*/
int s77(struct datasys *x)									// Short Term Range Rejection
{

	int i=0, j=0;
	int *var1;
	float hhv=0, llv=0, movstor=0, sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0;
	float *hhv21, *llv21, *mov21, *lrslope21, *lrslope5;

	var1=intarray1;											// Range Identification Signal array (1 or 0)

	hhv21=floatarray1;										// 21-Period Highest High Value of Close
	llv21=floatarray2;										// 21-Period Lowest Low Value of Close
	mov21=floatarray3;										// 21-Period Simple Moving Average of Close
	lrslope21=floatarray4;									// 21-Period Linear Regression Slope
	lrslope5=floatarray5;									// 5-Period Linear Regression Slope


	if((x->lastvalid - x->firstvalid)<21) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 21-day levels and also based on Close.
		for (j=i-20; j<=i; j++)
		{
			if (j==i-20)
			{
				hhv=x->close[j];
				llv=x->close[j];
			}

			if(x->close[j]>hhv) hhv=x->close[j];
			if(x->close[j]<llv) llv=x->close[j];
		}

		hhv21[i]=hhv;
		llv21[i]=llv;
	}

	for (i=x->firstvalid+20; i>=x->firstvalid; i--)			// 21-Period Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov21[x->firstvalid+20]=(float)(movstor/21.0);

	for (i=x->firstvalid+21; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-21];
		mov21[i] = (float)(movstor / 21.0);
	}



	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// 21-Period Linear Regression Slope
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-20; j<=i; j++)
		{
			sum1=sum1+((float)j*x->close[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->close[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+20)
			{
				movc=movc+x->close[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+20)
		{
			movc=movc-x->close[i-21]+x->close[i];
			movcum=movcum-(i-21)+i;
		}

		lrslope21[i]=
			(sum1-((sum2*sum3)/21))/(sum4-(((float)pow(sum2,2))/(float)21));
	}


	movc=0;
	movcum=0;


	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// 5-Period Linear Regression Slope
	{
		// Slope Calculation

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-4; j<=i; j++)
		{
			sum1=sum1+((float)j*x->close[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->close[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+4)
			{
				movc=movc+x->close[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+4)
		{
			movc=movc-x->close[i-5]+x->close[i];
			movcum=movcum-(i-5)+i;
		}

		lrslope5[i]=
			(sum1-((sum2*sum3)/5))/(sum4-(((float)pow(sum2,2))/(float)5));
	}


	for (i=x->firstvalid+20; i<=x->lastvalid; i++)
		if(hhv21[i]<(mov21[i]*1.1) AND llv21[i]>(mov21[i]*.9))
			var1[i]=1;


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (var1[i]==0 AND lrslope5[i]>0 AND lrslope21[i]>0)
			x->el[i]=1;

		if (var1[i]==1 OR lrslope21[i]<0)
			x->cl[i]=1;

		if (var1[i]==0 AND lrslope5[i]<0 AND lrslope21[i]<0)
			x->es[i]=1;

		if (var1[i]==1 OR lrslope21[i]>0)
			x->cs[i]=1;
	}
	
	memcpy (x->ind1, hhv21, sizeof(float)*65500);			// Ind1 = 21-Period Highest High Value of Close
	memcpy (x->ind2, llv21, sizeof(float)*65500);			// Ind2 = 21-Period Lowest Low Value of Close
	memcpy (x->ind3, mov21, sizeof(float)*65500);			// Ind3 = 21-Period Simple Moving Average of Close
	memcpy (x->ind4, lrslope5, sizeof(float)*65500);		// Ind4 = 5-Period Linear Regression Slope
	memcpy (x->ind5, lrslope21, sizeof(float)*65500);		// Ind5 = 21-Period Linear Regression Slope


	*(x->elIsValid) = x->firstvalid+20;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+20;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+20;
	*(x->csIsValid) = x->firstvalid+20;
	*(x->ind1FirstValid) = x->firstvalid+20;
	*(x->ind2FirstValid) = x->firstvalid+20;
	*(x->ind3FirstValid) = x->firstvalid+20;
	*(x->ind4FirstValid) = x->firstvalid+4;
	*(x->ind5FirstValid) = x->firstvalid+20;

	
	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays
	
	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***********************************
//	***** Small Triangle Breakout *****
//	***********************************
/*
This system looks for a very small triangle consisting of two consecutive bars
with lower highs and higher lows.  This is an uncommon pattern that is traded
as a consolidation breakout. Once this small triangle occurs, a breakout is
detected and a trade is placed in the direction of the breakout. A long
position is exited when the price falls below the previous days low, and a
short position is exited when the price rises above the previous days high.

Note that the system tester will show all entries or exits as if the trade is
made on the closing price (an MOC or Market-On-Close order). While the system
can certainly be traded this way, the proper technique would be to know when
the three-bar triangle pattern occurs and then to make a trade in the direction
of the breakout upon crossing either the high or low price of the most recent
small triangle bar. A true stop would be placed at the previous day's extreme
price (low for long positions, high for short position) and is constantly moved
each day to follow the position.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	None
	
MetaStock Code:
	var1:=(H<=Ref(H,-1) AND Ref(H,-1)<=Ref(H,-2) AND L>=Ref(L,-1) AND
		Ref(L,-1)>=Ref(L,-2));

	EL:=Ref(var1,-1) AND H>Ref(H,-1)
	CL:= L<Ref(L,-1)
	ES:= Ref(var1,-1) AND L<Ref(L,-1)
	CS:= H>Ref(H,-1)
*/
int s78(struct datasys *x)									// Small Triangle Breakout
{

	int i=0;
	int *var1;

	var1=intarray1;											// Small Triangle Indetification (1 or 0)

	if((x->lastvalid - x->firstvalid)<4) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+2; i<=x->lastvalid; i++)
		if(x->high[i]<=x->high[i-1] AND x->high[i-1]<=x->high[i-2]
			AND x->low[i]>=x->low[i-1] AND x->low[i-1]>=x->low[i-2])
			var1[i]=1;


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+3; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (var1[i-1]==1 AND x->high[i]>x->high[i-1])
			x->el[i]=1;

		if (x->low[i]<x->low[i-1])
			x->cl[i]=1;

		if (var1[i-1]==1 AND x->low[i]<x->low[i-1])
			x->es[i]=1;

		if (x->high[i]>x->high[i-1])
			x->cs[i]=1;
	}

	*(x->elIsValid) = x->firstvalid+3;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+3;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+3;
	*(x->csIsValid) = x->firstvalid+3;

	bzero(intarray1,sizeof(int)*65500);						// Clean Array

	return 0;												// Return NULL for valid system.
}




//	****************************
//	***** StarcBand System *****
//	****************************
/*
STARC bands (SToller Average Range Channels) were developed by Manning Stoller
and are a type of volatility band based upon Welles Wilder's Average True Range
function. Unlike other band systems that trade based upon a prices relationship
to the bands, this system takes a completely different approach. It enters a
long position when the lower STARC band crosses above the 20-period moving
average of prices. It then exits and takes a short position when the upper
STARC band crosses below the 20-period moving average of prices. Even though
this was not the designer's original method, it still shows to be a profitable
method of trading.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 20-Period Exponential Moving Average of Close
	Ind2 = 6-Period Simple Moving Average of Close
	Ind3 = 15-Day Average True Range
	Ind4 = StarcBand High Band
	Ind5 = StarcBand Low Band
	
MetaStock Code:
	EL:=Cross(Mov(C,6,S)-(ATR(15)*2),Mov(C,20,E))
	ES:= Cross(Mov(C,20,E),Mov(C,6,S)+(ATR(15)*2))
*/
int s79(struct datasys *x)									// StarcBand System
{

	int i=0;
	float th=0, tl=0, atr1=0, movstor=0;
	float *atr15, *mov6, *ema20;

	atr15=floatarray1;										// 15-Day Average True Range
	mov6=floatarray2;										// 6-Period Simple Moving Average of Close
	ema20=floatarray3;										// 20-Period Exponential Moving Average of Close



	if((x->lastvalid - x->firstvalid)<21) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->firstvalid+15; i++)		// 15-Day Average True Range 1st calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=atr1+(th-tl);
	}
	atr15[x->firstvalid+15]=(atr1/(float)15.0);


	for (i=x->firstvalid+16; i<=x->lastvalid; i++)			// 15-Day Average True Range continuous calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=th-tl;
		atr15[i]=(((atr15[i-1]*(float)14.0)+atr1)/(float)15.0);
	}



	for (i=x->firstvalid; i>=x->firstvalid+5; i++)			// 6-Period Simple Moving Average of Close
	{
		movstor=movstor+x->close[i];
	}

	mov6[x->firstvalid+5]=(float)(movstor/6.0);

	for (i=x->firstvalid+6; i<=x->lastvalid; i++)
	{
		movstor = movstor + x->close[i] - x->close[i-6];
		mov6[i] = (float)(movstor / 6.0);
	}



	ema20[x->firstvalid]=x->close[x->firstvalid];			// 20-Period Exponential Moving Average of Close

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		ema20[i] = (float)(x->close[i] * (2.0/21.0)) + (float)(ema20[i-1] * (1.0-(2.0/21.0)));
	}



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if ((mov6[i]-(atr15[i]*2))>ema20[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if ((mov6[i]+(atr15[i]*2))<ema20[i])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}

		x->ind4[i]=(mov6[i]+(atr15[i]*2));					// Ind4 = StarcBand High Band
		x->ind5[i]=(mov6[i]-(atr15[i]*2));					// Ind5 = StarcBand Low Band
	}

	memcpy (x->ind1, ema20, sizeof(float)*65500);			// Ind1 = 20-Period Exponential Moving Average of Close
	memcpy (x->ind2, mov6, sizeof(float)*65500);			// Ind2 = 6-Period Simple Moving Average of Close
	memcpy (x->ind3, atr15, sizeof(float)*65500);			// Ind3 = 15-Day Average True Range

	*(x->elIsValid) = x->firstvalid+20;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+20;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+20;
	*(x->csIsValid) = x->firstvalid+20;
	*(x->ind1FirstValid) = x->firstvalid+19;
	*(x->ind2FirstValid) = x->firstvalid+5;
	*(x->ind3FirstValid) = x->firstvalid+14;
	*(x->ind4FirstValid) = x->firstvalid+20;
	*(x->ind5FirstValid) = x->firstvalid+20;

	
	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	****************************************
//	***** Stochastic Oscillator System *****
//	****************************************
/*
George Lane developed the Stochastic Oscillator. This is the classic Stochastic
Oscillator trading system except with a protective stop added. It enters when
the Stochastic Oscillator crosses above 20 and exits when it crosses above and
then below 80, or back below 20 (this is the protective stop part). Note that
this system uses an unsmoothed Stochastic rather than the smoothed one that is
typically used by other trading systems.
 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 14-Period Stochastic Oscillator
	
MetaStock Code:
	EL:= Cross(Stoch(14,1),20)
	CL:= Cross(80,Stoch(14,1)) OR Stoch(14,1)<20
	ES:= Cross(80,Stoch(14,1))
	CS:= Cross(Stoch(14,1),20) OR Stoch(14,1)>80
*/
int s80(struct datasys *x)									// Stochastic Oscillator System
{

	int i=0, j=0;
	float hhv=0, llv=0;
	float *hhv14, *llv14, *stoch14;

	hhv14=floatarray1;										// 14-Period Highest High Value of Highs
	llv14=floatarray2;										// 14-Period Lowest Low Value of Lows
	stoch14=floatarray3;									// 14-Period Stochastic Oscillator


	if((x->lastvalid - x->firstvalid)<15) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+13; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 14-day levels.
		for (j=i-13; j<=i; j++)								//	(Needed for Stochastic Calculation)
		{
			if (j==i-13)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv14[i]=hhv;
		llv14[i]=llv;

		stoch14[i]=((x->close[i]-llv14[i])/(hhv14[i]-llv14[i]))*100;
	}



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+14; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (stoch14[i]>20 AND stoch14[i-1]<20)
			x->el[i]=1;

		if ((stoch14[i]<80 AND stoch14[i-1]>80) OR stoch14[i]<20)
			x->cl[i]=1;


		if (stoch14[i]<80 AND stoch14[i-1]>80)
			x->es[i]=1;

		if ((stoch14[i]>20 AND stoch14[i-1]<20) OR stoch14[i]>80)
			x->cs[i]=1;
	}

	memcpy (x->ind1, stoch14, sizeof(float)*65500);			// Ind1 = 14-Period Stochastic Oscillator

	*(x->elIsValid) = x->firstvalid+14;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+14;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+14;
	*(x->csIsValid) = x->firstvalid+14;
	*(x->ind1FirstValid) = x->firstvalid+13;

	
	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	********************
//	***** StochRSI *****
//	********************
/*
Tushar Chande and Stanley Kroll developed the StochRSI indicator. One of the
problems with using the RSI as an overbought/oversold indicator is that, due to
the built-in smoothing, it may be a long time before an extreme is ever
reached. This forces it to miss out on many significant trading signals.
Applying a stochastic process to the RSI makes it so that an extreme will have
to be reached within a limited amount of time (preferably when a valid trading
signal is present). The system trades the same way that the Stochastic 
oscillator does; Around the 20 and 80 extremes.

As with all overbought/oversold indicators and systems, even though it can be
very good at capturing profits on a large number of trades, no real protection
mechanism has been put into place if the trade immediately moves against you.
Stop-loss orders should be used to prevent the few failing trades from removing
all acquired profits.

Further Reading from Tushar Chande and Stanley Kroll:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators. (Wiley Finance Editions) John Wiley and Sons, Inc. 1994

Further Reading from Tushar Chande:
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997

Further Reading from Stanley Kroll:
	The Business One Irwin Guide to the Futures Markets. Irwin Professional
		Publishing. 1992
	The Professional Commodity Trader. Traders Press. 1995

 
Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 8-Period Stochastic with 3-period slowing of RSI
	
MetaStock Code:
	EL:=Cross(20,(Sum(RSI(10)-LLV(RSI(10),10),3)/
		Sum(HHV(RSI(10),10)-LLV(RSI(10),10),3))*100)

	ES:= Cross((Sum(RSI(10)-LLV(RSI(10),10),3)/
		Sum(HHV(RSI(10),10)-LLV(RSI(10),10),3))*100,80)
*/
int s81(struct datasys *x)									// StochRSI
{

	int i=0, j=0;
	float rsiup=0, rsidown=0, hhv=0, llv=0, sumnum=0, sumden=0;
	float *rsi, *hhv10, *llv10, *stoch10;

	rsi=floatarray1;										// 10-Period Relative Strength Index (RSI)
	hhv10=floatarray2;										// 10-Period Highest High Value of RSI
	llv10=floatarray3;										// 10-Period Lowest Low Value of RSI
	stoch10=floatarray4;									// 8-Period Stochastic with 3-period slowing of RSI


	if((x->lastvalid - x->firstvalid)<21) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->firstvalid+9; i++)		// 10-Period Relative Strength Index (RSI)
	{
		if(x->close[i]>x->close[i-1]) rsiup=rsiup+(x->close[i]-x->close[i-1]);
		if(x->close[i]<x->close[i-1]) rsidown=rsidown+(x->close[i-1]-x->close[i]);
	}

	if(rsidown==0) rsidown=(float).0001;					// (To prevent divide by zero error)

	rsi[x->firstvalid+9]=100-(100/(1+(rsiup/rsidown)));

	rsiup=rsiup/(float)10;
	rsidown=rsidown/(float)10;

	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
	{
		if(x->close[i]>x->close[i-1])
			rsiup=(rsiup*((float)9/(float)10))+((x->close[i]-x->close[i-1])*((float)1/(float)10));
		else 
			rsiup=rsiup*((float)9/(float)10);

		if(x->close[i]<x->close[i-1])
			rsidown=(rsidown*((float)9/(float)10))+((x->close[i-1]-x->close[i])*((float)1/(float)10));
		else 
			rsidown=rsidown*((float)9/(float)10);

		rsi[i]=100-(100/(1+(rsiup/rsidown)));
	}


	for (i=x->firstvalid+18; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 10-day levels.
		for (j=i-9; j<=i; j++)
		{
			if (j==i-9)
			{
				hhv=rsi[j];
				llv=rsi[j];
			}

			if(rsi[j]>hhv) hhv=rsi[j];
			if(rsi[j]<llv) llv=rsi[j];
		}

		hhv10[i]=hhv;
		llv10[i]=llv;
	}


	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// 8-Period Stochastic with 3-period slowing.
	{
		sumnum=0;											// Summed Numerator
		sumden=0;											// Summed Denominator

		for (j=i-2; j<=i; j++)								// 3-period slowing.
		{
			sumnum=sumnum+(rsi[j]-llv10[j]);
			sumden=sumden+(hhv10[j]-llv10[j]);
		}

		stoch10[i]=(sumnum/sumden)*100;
	}




  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+21; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (stoch10[i]<20 AND stoch10[i-1]>20)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (stoch10[i]>80 AND stoch10[i-1]<80)
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, stoch10, sizeof(float)*65500);			// Ind1 = 8-Period Stochastic with 3-period slowing of RSI
	
	*(x->elIsValid) = x->firstvalid+21;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+21;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+21;
	*(x->csIsValid) = x->firstvalid+21;
	*(x->ind1FirstValid) = x->firstvalid+20;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***********************
//	***** Swing Index *****
//	***********************
/*
The Swing Index was created by Welles Wilder to identify the true price of a
security by evaluating the current bar's open/high/low/close prices as well as
the previous bar's information. It then plots that relationship as a value
above or below a zero line. Because it is looking for a change in direction of
price movement (using a bar by bar approach) it trades with a very similar
philosophy to Pattern Trading System 1 except much more frequently. It also
allows for short positions.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Swing Index
	
MetaStock Code:
	EL:= Swing(3)>0
	ES:= Swing(3)<0
*/
int s82(struct datasys *x)									// Swing Index
{

	int i=0;
	float f19=0, g19=0, h19=0, i19=0, j19=0, k19=0, l19=0, m19=0, n19=0, o19=0;
	float *swing;

	swing=floatarray1;										// Swing Index Indicator


	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Calculate Swing Index
	{
		f19=(float)fabs(x->high[i]-x->close[i-1]);
		g19=(float)fabs(x->low[i]-x->close[i-1]);
		h19=(float)fabs(x->high[i]-x->low[i]);
		i19=(float)fabs(x->close[i-1]-x->open[i-1]);
		j19=x->close[i]-x->close[i-1];
		k19=x->close[i]-x->open[i];
		l19=x->close[i-1]-x->open[i-1];
		m19=j19+((float).5*k19)+((float).25*l19);
		n19=__max(f19,g19);



		if (f19>g19 AND f19>h19)
			o19=f19-((float)0.5*g19)+((float)0.25*i19);
		else if (g19>f19 AND g19>h19)
			o19=g19-((float)0.5*f19)+((float)0.25*i19);
		else
			o19=h19+((float)0.25*i19);

		swing[i]=__min((float)100,50*m19/o19*n19/3);
	}



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (swing[i]>0)
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (swing[i]<0)
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, swing, sizeof(float)*65500);			// Ind1 = Swing Index

	*(x->elIsValid) = x->firstvalid+1;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+1;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+1;
	*(x->csIsValid) = x->firstvalid+1;
	*(x->ind1FirstValid) = x->firstvalid+1;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Array

	return 0;												// Return NULL for valid system.
}




//	*****************************
//	***** Turtle Breakout 1 *****
//	*****************************
/*
While by no means the complete system, this system is the basis of the trading
system taught by Richard Dennis to his world-known 'Turtles'. It's based on a
breakout with a protective stop.

This system identifies the highest and lowest prices over the last 20 days. It
enters a long position when the price breaks out of the 20-day high. Once the
position is entered, it identifies the 10-day low and exits when the price 
crosses below this point. As prices continue to move up, the 10-day low also
continues to move up acting as a stop-loss as well as a trailing stop. For the
short position, the price crosses below the 20-day low and the 
stop-loss/trailing stop is set at the 10-day high.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 10-Period Highest High Value of Highs
	Ind2 = 10-Period Lowest Low Value of Lows
	Ind3 = 20-Period Highest High Value of Highs
	Ind4 = 20-Period Lowest Low Value of Lows
	
MetaStock Code:
	EL:= H>Ref(HHV(H,20),-1)
	CL:= L<Ref(LLV(L,10),-1)
	ES:= L<Ref(LLV(L,20),-1)
	CS:= H>Ref(HHV(H,10),-1)
*/
int s83(struct datasys *x)									// Turtle Breakout 1
{

	int i=0, j=0;
	float hhv=0, llv=0;
	float *hhv10, *llv10, *hhv20, *llv20;

	hhv10=floatarray1;										// 10-Period Highest High Value of Highs
	llv10=floatarray2;										// 10-Period Lowest Low Value of Lows
	hhv20=floatarray3;										// 20-Period Highest High Value of Highs
	llv20=floatarray4;										// 20-Period Lowest Low Value of Lows


	if((x->lastvalid - x->firstvalid)<21) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+9; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 10-day levels.
		for (j=i-9; j<=i; j++)
		{
			if (j==i-9)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv10[i]=hhv;
		llv10[i]=llv;
	}


	hhv=0;
	llv=0;


	for (i=x->firstvalid+19; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 20-day levels.
		for (j=i-19; j<=i; j++)
		{
			if (j==i-19)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv20[i]=hhv;
		llv20[i]=llv;
	}



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->high[i]>hhv20[i-1])
			x->el[i]=1;

		if (x->low[i]<llv10[i-1])
			x->cl[i]=1;

		if (x->low[i]<llv20[i-1])
			x->es[i]=1;

		if (x->high[i]>hhv10[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, hhv10, sizeof(float)*65500);			// Ind1 = 10-Period Highest High Value of Highs
	memcpy (x->ind2, llv10, sizeof(float)*65500);			// Ind2 = 10-Period Lowest Low Value of Lows
	memcpy (x->ind3, hhv20, sizeof(float)*65500);			// Ind3 = 20-Period Highest High Value of Highs
	memcpy (x->ind4, llv20, sizeof(float)*65500);			// Ind4 = 20-Period Lowest Low Value of Lows


	*(x->elIsValid) = x->firstvalid+20;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+20;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+20;
	*(x->csIsValid) = x->firstvalid+20;
	*(x->ind1FirstValid) = x->firstvalid+9;
	*(x->ind2FirstValid) = x->firstvalid+9;
	*(x->ind3FirstValid) = x->firstvalid+19;
	*(x->ind4FirstValid) = x->firstvalid+19;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	*****************************
//	***** Turtle Breakout 2 *****
//	*****************************
/*
While by no means the complete system, this system is the basis of the trading
system taught by Richard Dennis to his world-known 'Turtles'. It's based on a
breakout with a protective stop.

This system identifies the highest and lowest prices over the last 20 days. It
enters a long position when the price breaks out of the 20-day high. Once the
position is entered, it identifies the 5-day low and exits when the price 
crosses below this point. As prices continue to move up, the 5-day low also
continues to move up acting as a stop-loss as well as a trailing stop. For the
short position, the price crosses below the 20-day low and the 
stop-loss/trailing stop is set at the 5-day high. This allows for a tighter
stop than "Turtle Breakout 1" so as to lock-in profits at the expense of being
left out of a significant trend without being whipsawed out.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 5-Period Highest High Value of Highs
	Ind2 = 5-Period Lowest Low Value of Lows
	Ind3 = 20-Period Highest High Value of Highs
	Ind4 = 20-Period Lowest Low Value of Lows
	
MetaStock Code:
	EL:= H>Ref(HHV(H,20),-1)
	CL:= L<Ref(LLV(L,5),-1)
	ES:= L<Ref(LLV(L,20),-1)
	CS:= H>Ref(HHV(H,5),-1)
*/
int s84(struct datasys *x)									// Turtle Breakout 2
{

	int i=0, j=0;
	float hhv=0, llv=0;
	float *hhv5, *llv5, *hhv20, *llv20;

	hhv5=floatarray1;										// 5-Period Highest High Value of Highs
	llv5=floatarray2;										// 5-Period Lowest Low Value of Lows
	hhv20=floatarray3;										// 20-Period Highest High Value of Highs
	llv20=floatarray4;										// 20-Period Lowest Low Value of Lows


	if((x->lastvalid - x->firstvalid)<21) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+4; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 5-day levels.
		for (j=i-4; j<=i; j++)
		{
			if (j==i-4)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv5[i]=hhv;
		llv5[i]=llv;
	}


	hhv=0;
	llv=0;


	for (i=x->firstvalid+19; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 20-day levels.
		for (j=i-19; j<=i; j++)
		{
			if (j==i-19)
			{
				hhv=x->high[j];
				llv=x->low[j];
			}

			if(x->high[j]>hhv) hhv=x->high[j];
			if(x->low[j]<llv) llv=x->low[j];
		}

		hhv20[i]=hhv;
		llv20[i]=llv;
	}



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->high[i]>hhv20[i-1])
			x->el[i]=1;

		if (x->low[i]<llv5[i-1])
			x->cl[i]=1;

		if (x->low[i]<llv20[i-1])
			x->es[i]=1;

		if (x->high[i]>hhv5[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, hhv5, sizeof(float)*65500);			// Ind1 = 5-Period Highest High Value of Highs
	memcpy (x->ind2, llv5, sizeof(float)*65500);			// Ind2 = 5-Period Lowest Low Value of Lows
	memcpy (x->ind3, hhv20, sizeof(float)*65500);			// Ind3 = 20-Period Highest High Value of Highs
	memcpy (x->ind4, llv20, sizeof(float)*65500);			// Ind4 = 20-Period Lowest Low Value of Lows

	*(x->elIsValid) = x->firstvalid+20;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+20;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+20;
	*(x->csIsValid) = x->firstvalid+20;
	*(x->ind1FirstValid) = x->firstvalid+4;
	*(x->ind2FirstValid) = x->firstvalid+4;
	*(x->ind3FirstValid) = x->firstvalid+19;
	*(x->ind4FirstValid) = x->firstvalid+19;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	*******************************
//	***** Ultimate Oscillator *****
//	*******************************
/*
Larry Williams developed the Ultimate Oscillator. Typically, the Ultimate
Oscillator is used to analyze divergences, but this system looks for a 7/14/28
oscillator to change direction therefore acting as a directional momentum
indicator. It enters a long position when the direction of the oscillator is
moving up and either exits/enters short when the direction of the oscillator
moves down.

Further Reading from Larry Williams:
	The New Technical Trader: Boost Your Profit by Plugging Into the Latest
		Indicators (With Stanley Kroll). (Wiley Finance Editions) John Wiley
		and Sons, Inc. 1994
	Beyond Technical Analysis: How to Develop and Implement a Winning Trading
		System. (Wiley Finance Editions) John Wiley and Sons, Inc. 1997
	Long-Term Secrets to Short-Term Trading. John Wiley and Sons, Inc. 1999
	Day Trade Futures Online. John Wiley and Sons, Inc. 2000
	The Definite Guide to Futures Trading. Windsor Books. 1990
	How I Made a Million Dollars Trading Commodities Last Year. Windsor Books. 1979
	Sure Thing Commodity Trading. 1988

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Ultimate Oscillator
	
MetaStock Code:
	EL:= Ult(7,14,28)>Ref(Ult(7,14,28),-1)
	ES:= Ult(7,14,28)<Ref(Ult(7,14,28),-1)
*/
int s85(struct datasys *x)									// Ultimate Oscillator
{

	int i=0;
	float th=0, tl=0, rangesum=0, bpsum=0;
	float *tr1, *bp, *div7, *div14, *div28, *ultosc;

	tr1=floatarray1;										// 1-Day True Range
	bp=floatarray1;											// Buying Pressure
	div7=floatarray1;										// 7-Period Divisor
	div14=floatarray1;										// 14-Period Divisor
	div28=floatarray1;										// 28-Period Divisor
	ultosc=floatarray1;										// Ultimate Oscillator (7,14,28)


	if((x->lastvalid - x->firstvalid)<31) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// 1-Day True Range
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		tr1[i]=th-tl;
		bp[i]=x->close[i]-tl;
	}


	for (i=x->firstvalid+1; i<=x->firstvalid+7; i++)		// 7-Day Division (Buying Pressure/Range)
	{
		rangesum=rangesum+tr1[i];
		bpsum=bpsum+bp[i];
	}

	div7[i]=bpsum/rangesum;

	for (i=x->firstvalid+8; i<=x->lastvalid; i++)
	{
		rangesum=rangesum+tr1[i]-tr1[i-7];
		bpsum=bpsum+bp[i]-bp[i-7];

		div7[i]=bpsum/rangesum;
	}


	rangesum=0;
	bpsum=0;

	for (i=x->firstvalid+1; i<=x->firstvalid+14; i++)		// 14-Day Division (Buying Pressure/Range)
	{
		rangesum=rangesum+tr1[i];
		bpsum=bpsum+bp[i];
	}

	div14[i]=bpsum/rangesum;

	for (i=x->firstvalid+15; i<=x->lastvalid; i++)
	{
		rangesum=rangesum+tr1[i]-tr1[i-14];
		bpsum=bpsum+bp[i]-bp[i-14];

		div14[i]=bpsum/rangesum;
	}


	rangesum=0;
	bpsum=0;

	for (i=x->firstvalid+1; i<=x->firstvalid+28; i++)		// 28-Day Division (Buying Pressure/Range)
	{
		rangesum=rangesum+tr1[i];
		bpsum=bpsum+bp[i];
	}

	div28[i]=bpsum/rangesum;

	ultosc[i]=(((4*div7[i])+(2*div14[i])+div28[i])/7)*100;	// Ultimate Oscillator (first calculation)

	for (i=x->firstvalid+29; i<=x->lastvalid; i++)
	{
		rangesum=rangesum+tr1[i]-tr1[i-28];
		bpsum=bpsum+bp[i]-bp[i-28];

		div28[i]=bpsum/rangesum;
															// Ultimate Oscillator
		ultosc[i]=(((4*div7[i])+(2*div14[i])+div28[i])/7)*100;

	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+29; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (ultosc[i]>ultosc[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (ultosc[i]<ultosc[i-1])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}

		x->ind1[i]=ultosc[i];
	}

	memcpy (x->ind1, ultosc, sizeof(float)*65500);			// Ind1 = Ultimate Oscillator

	*(x->elIsValid) = x->firstvalid+29;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+29;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+29;
	*(x->csIsValid) = x->firstvalid+29;
	*(x->ind1FirstValid) = x->firstvalid+28;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	**************************************
//	***** Vertical Horizontal Filter *****
//	**************************************
/*
Adam White introduced the Vertical Horizontal Filter (VHF) in the August 1991
issue of Futures magazine. It is similar to the r-squared and Welles Wilders
ADX indicator in that it identifies trending/non trending activity except that
it is nowhere near as sensitive as the r-squared (therefore reducing whipsaws)
and much more responsive than the ADX (increasing the chance of getting in at
the beginning of a trend). Once a trending status is identified by the ADX, it
looks to see which direction the trend is going by looking at a linear
regression slope with the same periods as the VHF and then enters a position
accordingly. It then exits when the trend breaks down.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 21-Period Vertical Horizontal Filter (VHF)
	Ind2 = 21-Period Linear Regression Slope
	
MetaStock Code:
	EL:= Cross(VHF(C,21),.3) AND LinRegSlope(C,21)>0
	CL:= Cross(.75,VHF(C,21)) OR Cross(0,LinRegSlope(C,21))
	ES:= Cross(VHF(C,21),.3) AND LinRegSlope(C,21)<0
	CS:= Cross(.75,VHF(C,21)) OR Cross(LinRegSlope(C,21),0)
*/
int s86(struct datasys *x)									// Vertical Horizontal Filter
{

	int i=0, j=0;
	float hhv=0, llv=0, densum=0, sum1=0, sum2=0, sum3=0, sum4=0, movc=0, movcum=0;
	float *hhv21, *llv21, *num, *den, *vhf, *lrslope;

	hhv21=floatarray1;										// 21-Period Highest High Value of Close
	llv21=floatarray2;										// 21-Period Lowest Low Value of Close
	num=floatarray3;										// VHF Numerator
	den=floatarray4;										// VHF Denominator
	vhf=floatarray5;										// 21-Period Vertical Horizontal Filter (VHF)
	lrslope=floatarray6;									// 21-Period Linear Regression Slope


	if((x->lastvalid - x->firstvalid)<24) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Set up HHV and LLV arrays based
	{														//	on 21-day levels of Closing prices.
		for (j=i-20; j<=i; j++)
		{
			if (j==i-20)
			{
				hhv=x->close[j];
				llv=x->close[j];
			}

			if(x->close[j]>hhv) hhv=x->close[j];
			if(x->close[j]<llv) llv=x->close[j];
		}

		hhv21[i]=hhv;
		llv21[i]=llv;

		num[i]=(float)fabs(hhv21[i]-llv21[i]);
	}



	for (i=x->firstvalid+1; i<=x->firstvalid+21; i++)		// 21-Period Vertical-Horizontal Filter
		densum=densum+(float)fabs(x->close[i]-x->close[i-1]);

	den[i]=densum;

	vhf[i]=num[i]/den[i];

	for (i=x->firstvalid+22; i<=x->lastvalid; i++)
	{
		densum=densum+(float)fabs(x->close[i]-x->close[i-1])-(float)fabs(x->close[i-21]-x->close[i-22]);

		den[i]=densum;

		vhf[i]=num[i]/den[i];
	}



	for (i=x->firstvalid+20; i<=x->lastvalid; i++)
	{
		// Slope Calculation								// 21-Period Linear Regression Slope

		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		
		for (j=i-20; j<=i; j++)
		{
			sum1=sum1+((float)j*x->close[j]);
			sum2=sum2+(float)j;
			sum3=sum3+x->close[j];
			sum4=sum4+(float)pow(j,2);

			if(i==x->firstvalid+20)
			{
				movc=movc+x->close[j];
				movcum=movcum+j;
			}

		}

		if(i>x->firstvalid+20)
		{
			movc=movc-x->close[i-21]+x->close[i];
			movcum=movcum-(i-21)+i;
		}

		lrslope[i]=
			(sum1-((sum2*sum3)/21))/(sum4-(((float)pow(sum2,2))/(float)21));


	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+23; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (vhf[i]>.3 AND vhf[i-1]<.3 AND lrslope[i]>0)
			x->el[i]=1;

		if ((vhf[i]<.75 AND vhf[i-1]>.75) OR (lrslope[i]<0 AND lrslope[i-1]>0))
			x->cl[i]=1;
			
		if (vhf[i]>.3 AND vhf[i-1]<.3 AND lrslope[i]<0)
			x->es[i]=1;

		if ((vhf[i]<.75 AND vhf[i-1]>.75) OR (lrslope[i]>0 AND lrslope[i-1]<0))
			x->cs[i]=1;
	}

	memcpy (x->ind1, vhf, sizeof(float)*65500);				// Ind1 = 21-Period Vertical Horizontal Filter (VHF)
	memcpy (x->ind2, lrslope, sizeof(float)*65500);			// Ind2 = 21-Period Linear Regression Slope

	*(x->elIsValid) = x->firstvalid+23;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+23;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+23;
	*(x->csIsValid) = x->firstvalid+23;
	*(x->ind1FirstValid) = x->firstvalid+21;
	*(x->ind1FirstValid) = x->firstvalid+20;



	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);
	bzero(floatarray4,sizeof(float)*65500);
	bzero(floatarray5,sizeof(float)*65500);
	bzero(floatarray6,sizeof(float)*65500);
	return 0;												// Return NULL for valid system.
}




//	*****************************************
//	***** Volatility Breakout (Chaikin) *****
//	*****************************************
/*
This system uses the Volatility indicator created by Marc Chaikin to determine
extremely short periods of volatility expansion. Typically, trades with this
system are only held for 1 or 2 days. It looks to see if the volatility of a
security is increasing and then takes a trade in the direction of price
movement. It exits the position either when prices move in the opposite
direction or when volatility decreases (signaling a potential change in
direction).

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = Chaikin's Volatility
	
MetaStock Code:
	EL:= Vol(10,10)>Ref(Vol(10,10),-1) AND C>Ref(C,-1)
	CL:= Vol(10,10)<Ref(Vol(10,10),-1) OR C<Ref(C,-1)
	ES:= Vol(10,10)>Ref(Vol(10,10),-1) AND C<Ref(C,-1)
	CS:= Vol(10,10)<Ref(Vol(10,10),-1) OR C>Ref(C,-1)
*/
int s87(struct datasys *x)									// Volatility Breakout (Chaikin)
{

	int i=0;
	float *ema10, *chaikin;

	ema10=floatarray1;										// 10-Period Exponential Moving Average of Close
	chaikin=floatarray2;									// Chaikin's Volatility


	if((x->lastvalid - x->firstvalid)<21) return 2;			// Return 2 if not enough data
															//	to calculate.


															// 10-Period Exponential Moving Average of Close
	ema10[x->firstvalid]=(x->high[x->firstvalid]-x->low[x->firstvalid]);	

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)
	{
		ema10[i] = (float)((x->high[i]-x->low[i]) * (2.0/11.0)) + (float)(ema10[i-1] * (1.0-(2.0/11.0)));
	}


	for (i=x->firstvalid+10; i<=x->lastvalid; i++)
		chaikin[i]=((ema10[i]-ema10[i-10])/ema10[i-10])*100;



  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+20; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (chaikin[i]>chaikin[i-1] AND x->close[i]>x->close[i-1])
			x->el[i]=1;

		if (chaikin[i]<chaikin[i-1] OR x->close[i]<x->close[i-1])
			x->cl[i]=1;
			

		if (chaikin[i]>chaikin[i-1] AND x->close[i]<x->close[i-1])
			x->es[i]=1;

		if (chaikin[i]<chaikin[i-1] OR x->close[i]>x->close[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, chaikin, sizeof(float)*65500);			// Ind1 = Chaikin's Volatility

	*(x->elIsValid) = x->firstvalid+20;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+20;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+20;
	*(x->csIsValid) = x->firstvalid+20;
	*(x->ind1FirstValid) = x->firstvalid+19;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	******************************************
//	***** Volatility Breakout (Standard) *****
//	******************************************
/*
There are many methods of analyzing historical volatility. This system is
identical to the 'Volatility System (Chaikin)' except that is uses the industry
standard of historical volatility as the volatility measure. 

This system determines extremely short periods of volatility expansion.
Typically, trades with this system are only held for 1 or 2 days. It looks to
see if the volatility of a security is increasing and then takes a trade in the
direction of price movement. It exits the position either when prices move in
the opposite direction or when volatility decreases (signaling a potential
change in direction).

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = 10-Period Volatility (Standard)
	
MetaStock Code:
	v1:=Std(Log(C/Ref(C,-1)),10)*Sqrt(365)*100;

	EL:=v1>Ref(v1,-1) AND C>Ref(C,-1)
	CL:= v1<Ref(v1,-1) OR C<Ref(C,-1)
	ES:= v1>Ref(v1,-1) AND C<Ref(C,-1)
	CS:= v1<Ref(v1,-1) OR C>Ref(C,-1)
*/
int s88(struct datasys *x)									// Volatility Breakout (Standard)
{

	int i=0, j=0;
	float movstor=0, stdstor=0;
	float *mov10, *stdev, *vol;

	mov10=floatarray1;										// 10-Period Moving Average of Log of (Close/(Close[-1])
	stdev=floatarray2;										// 10-Period Standard Deviation of Log of (Close/(Close[-1])
	vol=floatarray3;										// Standard Volatility


	if((x->lastvalid - x->firstvalid)<12) return 2;			// Return 2 if not enough data
															//	to calculate.


	for (i=x->firstvalid+1; i>=x->firstvalid+10; i++)		// 10-Period Moving Average of Log of (Close/(Close[-1])
	{
		movstor=movstor+(float)log(x->close[i]/x->close[i-1]);
	}

	mov10[x->firstvalid+10]=(float)(movstor/(float)10.0);

	for (i=x->firstvalid+11; i<=x->lastvalid; i++)
	{
		movstor = movstor + (float)log(x->close[i]/x->close[i-1]) - (float)log(x->close[i-10]/x->close[i-11]);
		mov10[i] = (float)(movstor / 10.0);
	}


	for (i=x->firstvalid+10; i<=x->lastvalid; i++)			// 10-Period Standard Deviation of Log of (Close/(Close[-1])
	{
		stdstor=0.0;
		for (j=i-9; j<=i; j++)
		{
			stdstor = stdstor+(float)pow(log(x->close[j]/x->close[j-1])-mov10[i],2);
		}

		stdev[i]= (float)sqrt(stdstor/10.0);

		vol[i]= stdev[i]*(float)sqrt(365)*100;				// Standard Volatility
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+11; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (vol[i]>vol[i-1] AND x->close[i]>x->close[i-1])
			x->el[i]=1;

		if (vol[i]<vol[i-1] OR x->close[i]<x->close[i-1])
			x->cl[i]=1;
			

		if (vol[i]>vol[i-1] AND x->close[i]<x->close[i-1])
			x->es[i]=1;

		if (vol[i]<vol[i-1] OR x->close[i]>x->close[i-1])
			x->cs[i]=1;
	}

	memcpy (x->ind1, vol, sizeof(float)*65500);				// Ind1 = 10-Period Volatility (Standard)

	*(x->elIsValid) = x->firstvalid+11;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+11;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+11;
	*(x->csIsValid) = x->firstvalid+11;
	*(x->ind1FirstValid) = x->firstvalid+10;


	bzero(floatarray1,sizeof(float)*65500);					// Clean Arrays
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}




//	***************************
//	***** Volatility Stop *****
//	***************************
/*
Another volatility based trading system, this one uses high and low stop
indicators designed by Mark Vakkur and presented in the October 1999 issue of
Technical Analysis of Stocks and Commodities magazine. Instead of using the
rules that the author suggests, the two indicators have become the trading
system and act not only as exit points, but also as reversal conditions. The
indicators use the Welles Wilder's Average True Range indicator to make
the determination of volatility. 

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	Ind1 = High Stop
	Ind1 = Low Stop
	
MetaStock Code:
	hstop:=Min(Ref(C,-1)+(ATR(4)*2),If(Ref(H,-1)>PREV,C*2,PREV));
	lstop:=Max(Ref(C,-1)-(ATR(4)*2),If(Ref(L,-1)<PREV,0,PREV));

	EL:=BarsSince(C>hstop)>BarsSince(C<lstop)
	ES:= BarsSince(C>hstop)<BarsSince(C<lstop)
*/
int s89(struct datasys *x)									// Volatility Stop
{

	int i=0;
	int *bshs, *bsls;
	float th=0, tl=0, atr1=0;
	float *atr4, *hstop, *lstop;

	bshs=intarray1;											// BarsSince High Stop
	bsls=intarray2;											// BarsSince Low Stop

	atr4=floatarray1;										// 4-Day Average True Range
	hstop=floatarray2;										// High Stop
	lstop=floatarray3;										// Low Stop



	if((x->lastvalid - x->firstvalid)<12) return 2;			// Return 2 if not enough data
															//	to calculate.



	for (i=x->firstvalid+1; i<=x->firstvalid+4; i++)		// 4-Day Average True Range 1st calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=atr1+(th-tl);
	}

	atr4[x->firstvalid+4]=(atr1/(float)4.0);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)			// 4-Day Average True Range continuous calculation
	{
		if(x->close[i-1]>x->high[i]) th=x->close[i-1];
			else th=x->high[i];
		if(x->close[i-1]<x->low[i]) tl=x->close[i-1];
			else tl=x->low[i];
		atr1=th-tl;
		atr4[i]=(((atr4[i-1]*(float)3.0)+atr1)/(float)4.0);
	}

															// hstop and lstop calculations.
	hstop[x->firstvalid+4]=x->close[x->firstvalid+3]+(atr4[x->firstvalid+4]*(float)2);
	lstop[x->firstvalid+4]=x->close[x->firstvalid+3]-(atr4[x->firstvalid+4]*(float)2);

	for (i=x->firstvalid+5; i<=x->lastvalid; i++)
	{
		if (x->high[i-1]>hstop[i-1])
			hstop[i]=__min(x->close[i-1]+(atr4[i]*(float)2),x->close[i]*(float)2);
		else
			hstop[i]=__min(x->close[i-1]+(atr4[i]*(float)2),hstop[i-1]);

		if (x->low[i-1]<lstop[i-1])
			lstop[i]=__max(x->close[i-1]-(atr4[i]*(float)2),0);
		else
			lstop[i]=__max(x->close[i-1]-(atr4[i]*(float)2),lstop[i-1]);

		if (x->close[i]>hstop[i]) bshs[i]=0;
		else bshs[i]=bshs[i-1]+1;

		if (x->close[i]<lstop[i]) bsls[i]=0;
		else bsls[i]=bsls[i-1]+1;
	}


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+11; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (bshs[i]>bsls[i])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (bshs[i]<bsls[i])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}

	memcpy (x->ind1, hstop, sizeof(float)*65500);			// Ind1 = High Stop
	memcpy (x->ind2, lstop, sizeof(float)*65500);			// Ind1 = Low Stop

	*(x->elIsValid) = x->firstvalid+11;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+11;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+11;
	*(x->csIsValid) = x->firstvalid+11;
	*(x->ind1FirstValid) = x->firstvalid+4;
	*(x->ind2FirstValid) = x->firstvalid+4;


	bzero(intarray1,sizeof(int)*65500);						// Clean Arrays
	bzero(intarray2,sizeof(int)*65500);

	bzero(floatarray1,sizeof(float)*65500);
	bzero(floatarray2,sizeof(float)*65500);
	bzero(floatarray3,sizeof(float)*65500);

	return 0;												// Return NULL for valid system.
}





//	*********************************
//	***** Volume Trading System *****
//	*********************************
/*
This system enters and exits on 'significant' trading days. Only if the trading
volume today is greater than the trading volume of yesterday does it become a
significant trading day. When there is a significant trading day, the system
places a trade in the direction of the movement (compared to yesterday's
close). If the volume today is greater than yesterday's volume and the close is
greater than yesterday's close, then the system will enter a long position.
While the price may move lower tomorrow, if the volume doesn't support the
behavior then it is not a significant trading and the position remains. The
system exits and takes a short position when today's close is less than
yesterday's close and has an increase from yesterday's volume to support it.

Trade Type:
	Both Long and Short Positions

Indicator Output: 
	None
	
MetaStock Code:
	EL:= C>Ref(C,-1) AND V>Ref(V,-1)
	ES:= C<Ref(C,-1) AND V>Ref(V,-1)
*/
int s90(struct datasys *x)									// Volume Trading System
{

	int i=0;


	if((x->lastvalid - x->firstvalid)<2) return 2;			// Return 2 if not enough data
															//	to calculate.


  	bzero(x->el,sizeof(int)*65500);							// Clean Output Arrays
	bzero(x->cl,sizeof(int)*65500);
	bzero(x->es,sizeof(int)*65500);
	bzero(x->cs,sizeof(int)*65500);

	for (i=x->firstvalid+1; i<=x->lastvalid; i++)			// Calculate system signals and
	{														//	copy to output arrays.
		if (x->close[i]>x->close[i-1] AND x->volume[i]>x->volume[i-1])
		{
			x->el[i]=1;
			x->cs[i]=1;
		}

		if (x->close[i]<x->close[i-1] AND x->volume[i]>x->volume[i-1])
		{
			x->es[i]=1;
			x->cl[i]=1;
		}
	}


	*(x->elIsValid) = x->firstvalid+1;						// Set first valids of calculations
	*(x->clIsValid) = x->firstvalid+1;						//	for each output array.
	*(x->esIsValid) = x->firstvalid+1;
	*(x->csIsValid) = x->firstvalid+1;


	return 0;												// Return NULL for valid system.
}









//	***********************************
//	***** Signal Cleanup Function *****
//	***********************************
//	Type: 1=Longs Only, 2=Shorts Only, 3=Both Longs and Shorts
void maint_signal_cleanup (struct datasys *x, int type)
{
	int i;

	bzero(x->state,sizeof(int)*65500);

	if (type == 1)
	{

		if (x->el[x->firstvalid]==1)
			x->state[x->firstvalid]=1;

		x->cl[x->firstvalid]=0;
		x->es[x->firstvalid]=0;
		x->cs[x->firstvalid]=0;

		for (i=x->firstvalid+1; i<=x->lastvalid; i++)
		{
			if(x->el[i]==0 AND x->cl[i]==0)
				x->state[i]=x->state[i-1];
			else
			{
				if (x->el[i]==1 AND x->state[i-1]==0)
				{
					x->state[i]=1;
					x->cl[i]=0;
				}
				else if (x->el[i]==1 AND x->state[i-1]==1)
				{
					x->el[i]=0;
					x->state[i]=1;
				}
	
				if (x->cl[i]==1 AND x->state[i-1]==1)
				{
					x->state[i]=0;
					x->el[i]=0;
				}
				else if (x->cl[i]==1 AND x->state[i-1]==0)
				{
					x->cl[i]=0;
					x->state[i]=0;
				}
			}
		}

		bzero(x->es,sizeof(int)*65500);
		bzero(x->cs,sizeof(int)*65500);
	}


	if (type == 2)
	{

		if (x->es[x->firstvalid]==1)
			x->state[x->firstvalid]=-1;

		x->el[x->firstvalid]=0;
		x->cl[x->firstvalid]=0;
		x->cs[x->firstvalid]=0;

		for (i=x->firstvalid+1; i<=x->lastvalid; i++)
		{
			if(x->es[i]==0 AND x->cs[i]==0)
				x->state[i]=x->state[i-1];
			else
			{
				if (x->es[i]==1 AND x->state[i-1]==0)
				{
					x->state[i]=-1;
					x->cs[i]=0;
				}
				else if (x->es[i]==1 AND x->state[i-1]==-1)
				{
					x->es[i]=0;
					x->state[i]=-1;
				}
	
				if (x->cs[i]==1 AND x->state[i-1]==-1)
				{
					x->state[i]=0;
					x->es[i]=0;
				}
				else if (x->cs[i]==1 AND x->state[i-1]==0)
				{
					x->cs[i]=0;
					x->state[i]=0;
				}
			}
		}

		bzero(x->el,sizeof(int)*65500);
		bzero(x->cl,sizeof(int)*65500);
	}


	if (type == 3)
	{

		if (x->el[x->firstvalid]==1 AND x->es[x->firstvalid]==1)
			x->state[x->firstvalid]=1;
		else if (x->el[x->firstvalid]==1)
			x->state[x->firstvalid]=1;
		else if (x->es[x->firstvalid]==1)
			x->state[x->firstvalid]=-1;
		else x->state[x->firstvalid]=0;

		x->cl[x->firstvalid]=0;
		x->cs[x->firstvalid]=0;

		for (i=x->firstvalid+1; i<=x->lastvalid; i++)
		{
			if ((x->el[i]==0) AND (x->cl[i]==0) AND (x->es[i]==0) AND (x->cs[i]==0))
				x->state[i]=x->state[i-1];
			else
			{
				if (x->state[i-1]==0)
				{
					x->cl[i]=0;
					x->cs[i]=0;

					if (x->el[i]==1 AND x->es[i]==1)
					{
						x->state[i]=1;
						x->es[i]=0;
					}

					else if (x->el[i]==1)
						x->state[i]=1;  //1

					else if (x->es[i]==1)
						x->state[i]=-1;  //-1

					else x->state[i]=x->state[i-1];

				}

				if (x->state[i-1]==1)
				{
					x->el[i]=0;
					x->cs[i]=0;

					if (x->es[i]==1)
					{
						x->state[i]=-1;
						x->cl[i]=0;
					}

					else if (x->cl[i]==1)
						x->state[i]=0;

					else x->state[i]=x->state[i-1];
				}

				if (x->state[i-1]==-1)
				{
					x->es[i]=0;
					x->cl[i]=0;

					if (x->el[i]==1)
					{
						x->state[i]=1;
						x->cs[i]=0;
					}

					else if (x->cs[i]==1)
						x->state[i]=0;

					else x->state[i]=x->state[i-1];   
				} 
			}
		}
	}
}








/*
	// *** For Testing Output Indicator Only ***
	for (i=x->firstvalid+62; i<=x->lastvalid; i++) x->ind1[i]=cg[i];							
	*(x->ind1FirstValid) = x->firstvalid+62;
	// *** End Indicator Test ***
*/


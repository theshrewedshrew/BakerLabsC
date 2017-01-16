#ifndef _Test_H
#define _Test_H
#include "PSIITEST.H"
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
*/
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
#endif

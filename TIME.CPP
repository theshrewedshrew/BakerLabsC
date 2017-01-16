#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <dos.h>

#define ZERO_FLAG	0x040
#define CONTROL_C	3
#define MS_PER_TICK	53	/* milliseconds per IBM PC clock tick */

unsigned long count;
unsigned ticks;
void interrupt timer(), interrupt (*old_handler)();

main()
{
	union REGS sreg, rreg;

	/* time starts at zero */
	count = 0;
	ticks = 0;

	/* initializations related to MS-DOS call to read keyboard */
	sreg.x.dx = 0xff;
	sreg.h.ah = 0x06;
	
	cout<<"\nTo stop the timer test program, type CTRL-C.";
	cout<<"\nTo display time since starting the program, hit any key.";
	cout<<"\nThe time is accurate to roughly the nearest 1 msec.\n\n";
	
	/* Save the address of the current timer interrupt handler */
	old_handler = getvect(8);

	/* Call "timer" function when timer interrupt occurs. */
	setvect(8, timer);
	
	/* Set up 8259 PIC chip to allow INT0 interrupt. */
	outportb(0x21, inportb(0x21) & 0xfe);
	
	/* issue command to 8253:  counter 0, binary counter, rate generator */
	/* (mode 2), load least significant byte of counter followed by      */
	/* most significant byte					     */
	outportb(0x43, 0x34);
	
	/* Timer is set for 0x4cd * 813.8 ns = 1 ms (LSB followed by MSB). */
	outportb(0x40, 0xcd); /* least significant byte of timer count */
	outportb(0x40, 0x04); /* most significant byte of timer count  */
	
	while (1) {
		/* wait for keystroke */
		while ( 1 ) {
			intdos(&sreg, &rreg);
			if ( ! (rreg.x.flags & ZERO_FLAG) )
				break;
	    	}
	
		/* stop the program if ctrl-C */
		if ( (rreg.x.ax & 0xff) == CONTROL_C ) {
			/* NOTE:  the following code MUST be executed before  */
			/* returning to MS-DOS in order to allow proper	      */
			/* operation of programs which use the 8253 timer.    */
	
			/* restore 8253 to original state set during PC boot  */
			/* NOTE:  this program leaves 8259 mask register with */
			/* least significant bit clear (i.e., INT0 enabled).  */
			outportb(0x43, 0x34);
			outportb(0x40, 0);
			outportb(0x40, 0);
	
			/* restore original interrupt vector for number 8 */
			setvect(8, old_handler);
	
			printf("Timer test program returning to MS-DOS.\n");
			exit(0);
		}
		else
			printf("TIME = %lu MSEC.\n",count);
	}
}
	
/* timer interrupt service routine (interrupt number 8) */
void interrupt
timer()
{
	count++;
	
	/* chain to the MS-DOS timer handler approx. 18 times per second */
	if (++ticks == MS_PER_TICK) {
		old_handler();
		ticks = 0;
	}
	
	/* issue end-of-interrupt command to 8259 PIC chip */
	outportb(0x20, 0x20);
}
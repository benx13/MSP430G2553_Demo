#include <msp430g2553.h>     // header file that depends upon your variant 

int main(void)
	{
	WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer
	
	DCOCTL = 0;				 //reseting the DCO
	BCSCTL1 = CALBC1_1MHZ;	 //setting the DCO to 1MHZ
	DCOCTL = CALDCO_1MHZ;	

	P1DIR = 0x01;    		 //Declare PIN0 AND PIN1 OF PORT 1 AS OUTPUT
	P1OUT = 0x00;            //MAKE PIN0 HIGH AND PIN1 LOW INITIALLY
	while(1)
		{
		P1OUT ^=0X01;        //Toggle the respective by using bit-xor operator 
		__delay_cycles(500000);
		} 
	return 0;
	}

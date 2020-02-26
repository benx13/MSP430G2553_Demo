#include <msp430g2553.h>  // header file that depends upon your variant 
/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW + WDTHOLD;// Stop watchdog timer
	P1DIR |= 0x01;
	while(1)
	{
		P1OUT ^=0X01;   //Toggle the respective by using bit-xor operator 
		__delay_cycles(50000);
	} 
	return 0;
}


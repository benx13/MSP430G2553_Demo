//******************************************************************************
//   MSP430G2xx3 Demo - USCI_A0, 9600 UART Echo ISR, DCO SMCLK
//
//   Description: Echo a received character, RX ISR used. 
//   USCI_A0 RX interrupt triggers TX Echo.
//   Baud rate divider with 1MHz = 1MHz/9600 = ~104.2
//   ACLK = n/a, MCLK = SMCLK = 1MHz
//
//                MSP430G2553
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |     P1.2/UCA0TXD|------------>
//            |                 | 9600 - 8N1
//            |     P1.1/UCA0RXD|<------------
//
//******************************************************************************
#include <msp430.h>


#define RXD BIT1 //Check your launchpad rev to make sure this is the case. Set
#define TXD BIT2 // TXD with respect to what your sending to the computer. Sent

void UART_TX(char * tx_data);
char string[4]={'u','a','r','t'};


void main(void) 
	{
	WDTCTL = WDTPW + WDTHOLD;   // Stop the watchdog
	
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;      //setting clock to 1MHZ
	DCOCTL = CALDCO_1MHZ;
	
	UCA0CTL1 |= UCSWRST;        // Select SMCLK
	P1SEL = RXD + TXD ;         // Select TX and RX functionality for P1.1 & P1.2
	P1SEL2 = RXD + TXD ; 
	UCA0CTL1 |= UCSSEL_2;       // Set baudrate to 9600 1MHZ
	UCA0BR0 = 104;
	UCA0BR1 = 0;
	UCA0MCTL = UCBRS0;          // UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;       // Initilize USCI state machine
	
	while(1)                    // Infinit loop
		{
	UART_TX(string);            // Send string 
	__delay_cycles(10000000);
		}
	}



void UART_TX(char * tx_data) // Define a function which accepts a character pointer to an
	{
	unsigned int i=0;
	while(tx_data[i]) // Increment through array, look for null pointer (0) at end of string
		{
		while ((UCA0STAT & UCBUSY)); // Wait if line TX/RX module is busy with data
		UCA0TXBUF = tx_data[i]; // Send out element i of tx_data array on UART bus
		i++; // Increment variable for array address
		}
	}

//******************************************************************************
//
//                MSP430G2553
//             -----------------
//            |                 |
//            |                 |
//            |                 |
//            |            P2.1/|--> GPIO - STEP
//            |                 |
//            |            P2.0/|--> GPIO - DIR
//            |                 |
//            |  P1.1-P1.2/RX-TX|<-- PC
//            |                 |
//In this demo we will control a Stepper motor linked to A4988 driver via UART protocol 
//the program will read first a hexa decimal number n ranged from 0x00 to 0xFF then do 
//n Stepper revoulution 
//PWM is not used in this certain example instead we are generationg simple GPIO impulses
//******************************************************************************
#include <msp430.h>




//******************************************************************************
void initClockTo1MHz();
void initGPIO();
void initUART();
void Rotate_Stepper(int rounds);
//******************************************************************************
void main()
	{
	WDTCTL = WDTPW + WDTHOLD;					// Stop WDT
	initClockTo1MHz();
	initGPIO();
	Rotate_Stepper(2);							//unitial 2 stepper revolutions to check wiring 
	initUART();									
	__bis_SR_register(GIE);       				// interrupts enabled
	}



//  Echo back RXed character, confirm TX buffer is ready first
//  then RX Stepper rotations
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  UCA0TXBUF = UCA0RXBUF;					// Echo back RX
  Rotate_Stepper(UCA0RXBUF);				// Turn Stepper n rotations
  //Disclaimer: in case you wanted to manipilate the recieved value cast
  //The RX register
}

void initUART()
	{
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  	UCA0BR0 = 104;                            // 1MHz 9600
  	UCA0BR1 = 0;                              // 1MHz 9600
  	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
	}

void initClockTo1MHz()
	{
    DCOCTL = 0;                             // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                  // Set DCO to 1MHZ
    DCOCTL = CALDCO_1MHZ;
	}

void initGPIO()
	{
	P1SEL = BIT1 + BIT2;                      // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;					  // 
	P2DIR |= 0x01 + 0x02;					  // P2.1 and P2.0 set as output
	P2OUT |= 0x01;							  // P2.0 set to High
	P2OUT &=~ 0x02;							  // P2.1 set to Low
	}
void Rotate_Stepper(int rounds)
	{
	int i=0;
	int k = rounds*200;
	for (i; i<k; i++)
		{
		P2OUT |= 0x02;
		__delay_cycles(2000);
		P2OUT &=~ 0x02;
		__delay_cycles(2000);
		}
	}



//TO DO;
/*#pragma vector=USCIAB0RX_VECTOR*/
/*__interrupt void USCI0RX_ISR(void)*/
/*void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)*/
/*{*/
	/*while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?*/
	/*[>[>uint8_t RXData = UCA0RXBUF; //Must read UCxxRXBUF to clear the flag<]<]*/
	/*UCA0TXBUF = UCA0RXBUF;	*/
	/*[>[>if (UCA0RXBUF == 0x0F) P2OUT ^= BIT0;      // Toggle direction of motor<]<]*/
	/*[>[>else if (UCA0RXBUF <= 0x0E) Rotate_Stepper(UCA0RXBUF);<]<]*/
	/*[>Rotate_Stepper(UCA0RXBUF);<]*/
/*}*/

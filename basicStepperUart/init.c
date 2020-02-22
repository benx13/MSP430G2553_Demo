void initUART()
	{
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 104;                            // 16MHz 9600
    UCA0BR1 = 0;                              // 16MHz 9600
    UCA0MCTL = UCBRS_0 + UCOS16 + UCBRF_3;    // Modulation UCBRSx = 0
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IFG2 &= ~(UCA0RXIFG);
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
	}

void initClockTo16MHz()
	{
    if (CALBC1_16MHZ==0xFF)while(1);         // If calibration constant erased trap CPU
    DCOCTL = 0;                              // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_16MHZ;                  // Set DCO
    DCOCTL = CALDCO_16MHZ;
	}

void initGPIO()
	{
    P1SEL = BIT1 + BIT2;                      // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;
	P2DIR |= BIT1;							  // P2.1 set as output
	P2SEL |= BIT1;							  // P2.1 selected Timer1_A Out1
	}

int initPWM(void) 
	{
	/*** Timer1_A Set-Up ***/
	TA1CCR0 |= 1000 - 1;					  // PWM Period
	TA1CCTL1 |= OUTMOD_7;			  		  // TA1CCR1 output mode = reset/set
	TA1CCR1 |= 500;							  // TA1CCR1 PWM duty cycle
	TA1CTL |= TASSEL_2 + MC_1;				  // SMCLK, Up Mode (Counts to TA1CCR0)
	} 



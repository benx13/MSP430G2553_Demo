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
//            |                 |
//            |                 |
//In this demo we will control a Stepper motor linked to A4988 driver.
//PWM is not used in this certain example instead we are generationg simple GPIO impulses
//******************************************************************************



#include<msp430g2553.h> 


#define FORWARD 0x01
#define BACKWARD 0x00


void rotateMotor(int steps, int direction); //steps: number of motor steps(impules), direction:CW/CCW





int main(void) 
	{
	WDTCTL = WDTPW | WDTHOLD;                // Stop watchdog timer
	
	DCOCTL = 0;                              // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_16MHZ;                  // Set DCO
	DCOCTL = CALDCO_16MHZ;


	P2DIR |= (0x01 + 0x02);
	P2OUT &=~(0x01 + 0x02);

	rotateMotor(1000, FORWARD);
	__delay_cycles(1000000);
	}


void rotateMotor(int steps, int direction)
	{
	int i=0;
	if(direction == 1)P2OUT |= 0x01;
	else P2OUT &=~ 0x01;
	for (i; i<steps; i++)                      // Send impulsions 
		{
		P2OUT |= 0x02;                         // P2.1 set to high
		__delay_cycles(10000);
		P2OUT &=~ 0x02;                        // P2.1 set to low 
		__delay_cycles(10000);                
		}
	}

/*======================================================================================================
 ********this program turns on the led when the button is pressed and turn it off when not**************
***************************done December 25th 2018 innovation academy ********************************
 ======================================================================================================*/

//===============================includes-block==========================================================
#include <msp430.h>
//===============================defines-block============================================================
#define LED 0x01                    //define internal led p1.0 as LED
#define BUTTON 0x08                 //define internal button p1.3 as BUTTON

//===============================global-variables-block==================================================

//===============================functions initialization block==========================================
void turn_on_LED();                 //this function turn on the defined LED
void turn_off_LED();                //this function turn off the defined LED
int BUTTON_check_active_low();      //this function check weather the defined BUTTON is clicked or not
                                    //in active low state(pull up)

//================================main-block=============================================================
void main()
{
//--------------------------------Initializing registers-------------------------------------------------

    WDTCTL = WDTPW + WDTHOLD;       //stop watchdog timer
    P1DIR |= LED;                   //make LED pin as output
    P1REN |= BUTTON;                //activating the internal resistor for pull up pull down
    P1OUT |= BUTTON;                //choosing pull up for the button
    turn_off_LED();                 //make sure that the MSP start with the LED turned off

//-------------------------------Infinite loop-----------------------------------------------------------
    for(;;)
    {
        if (BUTTON_check_active_low() == 1) turn_on_LED();//turn on LED when button is clicked
        else turn_off_LED();                              //turn off LED when button is not clicked
    }
}

//================================functions-core=========================================================
void turn_on_LED()
{
    P1OUT |= LED;                   //turn on LED
}

//------------------------------------------------------------------------------------------------------
void turn_off_LED()
{
    P1OUT &=~LED;                   //turn off LED
}

//-------------------------------------------------------------------------------------------------------
int BUTTON_check_active_low()
{
    if((P1IN & BUTTON) == 0x00) return 1;       //check if button is clicked
    else return 0;                              //eg:1111 1111and0000 0001 = 0000 0001 so it not clicked
}


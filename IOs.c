/* 
 * File:   IOs.c
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 * App Project 2
 */

#include <p24F16KA101.h>
#include "xc.h"
#include "UART2.h"
#include "IOs.h"

extern int selection;
/*
 * Initializes IO pins for application.
 */
void IOinit(void)
{   
    // IO pin setup   
    AD1PCFG = 0xFFFF;      // set all analog pins as digital 
    TRISBbits.TRISB4 = 1;  // set RB4 to digi input
    TRISAbits.TRISA2 = 1;  // set RA2 to digi input
    TRISAbits.TRISA4 = 1;  // set RA4 to digi input
    TRISBbits.TRISB8 = 0;  // set RB8 to digi output for LED
    CNPU1bits.CN0PUE  = 1; // pull up resistor for RA4/CN0 
    CNPU1bits.CN1PUE  = 1; // pull up resistor for RB4/CN1
    CNPU2bits.CN30PUE = 1; // pull up resistor for RA2/CN30

    // CN Registers/Interrupts setup
    CNEN1bits.CN0IE  = 1; // RA4 enable CN
    CNEN1bits.CN1IE  = 1; // RB4 enable CN             
    CNEN2bits.CN30IE = 1; // RA2 enable CN 
    IPC4 = IPC4 | 0xF000; // CN interrupts set to priority 7
    IEC1bits.CNIE = 1; // CN interrupt requests enabled
    IFS1bits.CNIF = 0; // clear T2 interrupt flag - because you never know?
}

// Checks which PB is pressed and changes the multimeter mode
void IOcheck(void) 
{
    if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1 ) 
    { // If button connected to port RA2 is pressed
        selection =  1;
    } 
    else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1) 
    { // If button connected to port RA4 is pressed
        selection =  2;
    } 
    else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0) 
    { // If button connected to port RB4 is pressed
        selection =  3;
    }
}
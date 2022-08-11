/*
 * File:   Multimeter.c
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

#include "xc.h"
#include "UART2.h"
#include "IOs.h"
#include "ADC.h"
#include "Display.h"

int selection; // Used to track user input

// Interrupt that triggers on pushbutton press
void __attribute((interrupt, no_auto_psv))_CNInterrupt(void)
{
    IOcheck(); // Set selection based on the PB that was pressed
    IFS1bits.CNIF = 0; // Reset interrupt
    Nop(); // Buffer
}

// Reads multimeter input based on user inputs via pushbuttons and
// passes the result to the display function, or puts the hardware
// back into idle mode.
void readMultimeter()
{
    int result; // The voltage or resistance that is read by the ADC
    
    while(1) // Loops continuously
    {
        if(selection == 2) // If PB1 was pressed
        {             
            result = readVoltage(); // Read the voltage from the potentiometer using the ADC
            displayVoltage(result); // Display the voltage using the UART2
        }
        else if(selection == 1) // If PB2 was pressed
        {        
            result = readResistance(); // Read the resistance of the resistor using the ADC
            displayResistance(result); // Display the resistance using the UART2
        }
        else if(selection == 3) // If PB3 was pressed
        {        
            clearLine(); // Clear the text that was on the screen before
            Idle(); // Go into idle mode
        }   
    }  
}
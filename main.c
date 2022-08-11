/*
 * File:   main.c
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

#include <xc.h>
#include "ADC.h"
#include "UART2.h"
#include "ChangeClk.h"
#include "ADC.h"
#include "IOs.h"
#include "Display.h"
#include "Multimeter.h"

#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config OSCIOFNC = ON  // CLKO output disabled on pin 8, use as IO.

extern int selection; // Tracks user inputs

// Main function of application
int main(void) 
{
    selection = 3; // Initializes multimeter to idle mode
    
    NewClk(500); // Change clock: 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
    InitUART2(); // Initializes UART2 display module
    IOinit(); // Initializes IOs and CN interrupt used
    
    readMultimeter(); // Starts reading the multimeter
    
    return 0;
}
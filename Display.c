/*
 * File:   Display.c
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

// Library files
#include "xc.h"
#include "Display.h"
#include "UART2.h"

// Displays the voltage to the console if PB1 pressed
void displayVoltage(uint16_t voltage)
{
    clearLine(); // Clears previous display
    Disp2String("VOLTMETER Voltage = ");
    voltage = (voltage + 1) / 16;
    unsigned int first = voltage / 20;
    unsigned int second = (voltage % 20) / 2;
    unsigned int third = voltage % 2;
    
    XmitUART2(first + 48, 1);
    XmitUART2('.', 1);
    XmitUART2(second + 48, 1);
    XmitUART2(third + 48, 1);
    XmitUART2('V', 1);
    
    return; // Return to main function
}

// Displays the resistance to the console if PB2 pressed
void displayResistance(uint16_t resistance)
{
    clearLine();
    Disp2String("OHMMETER Resistance = ");
    Disp2Dec(resistance); // Displays resistance in decimal notation
    
    return; // Return to main function
}


// Clears the console display line.
void clearLine()
{
    XmitUART2('\r', 1); // Returns to beginning of display line
    XmitUART2(' ', 40); // Clears the line of characters
    XmitUART2('\r', 1); // Returns to beginning of display line
}
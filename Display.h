/*
 * File:   Display.h
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DISPLAY_H
#define	DISPLAY_H

#include <xc.h> // include processor files - each processor file is guarded.

extern int bars; // Used to compare current bar graph to older version

void display(uint16_t); // Formats the display of the bar graph and hex value 
                        // that get written to the console.

void displayVoltage(uint16_t);  // Prints out the Voltage reading
void displayResistance(uint16_t); // Prints out the Resistance reading
void clearLine(); // Clears the text on the line

#endif	/* DISPLAY_H */
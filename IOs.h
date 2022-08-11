/* 
 * File: IOs.h
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef IOS
#define	IOS

#include <xc.h> // include processor files - each processor file is guarded.

void IOinit(void); // Initializes IO pins
void IOcheck(void); // Checks to see which pushbuttons are pressed

#endif	/* IOS */
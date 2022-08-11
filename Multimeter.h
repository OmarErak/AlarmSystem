/*
 * File:   Multimeter.h
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

#ifndef MULTIMETER_H
#define	MULTIMETER_H

void __attribute((interrupt, no_auto_psv))_CNInterrupt(void);
void readMultimeter(void);

#endif	/* MULTIMETER_H */
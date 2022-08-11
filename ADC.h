/*
 * File:   ADC.h
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

// Guard condition
#ifndef ADC_HEADER
#define	ADC_HEADER

#include <xc.h> // include processor files - each processor file is guarded.  

uint16_t readVoltage(void);
uint16_t readResistance(void);
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);

#endif	/* ADC_HEADER */
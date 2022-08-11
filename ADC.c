/*
 * File:   ADC.c
 * Author: Travis Dow, Omar Erak, Pamilerin Falade
 */

// Library files
#include "xc.h"
#include "UART2.h"

// unused ADC interrupt
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; // Clear the interrupt flag
    
    return;
}

// Reads the voltage input to pin 8
uint16_t readVoltage(void)
{
    uint16_t ADCvalue; // 16-bit register used to hold ADC converted digital output ADC1BUF0
    
/* -------------ADC INITIALIZATION ------------------*/
    // AD1CON1
    AD1CON1bits.ADON = 1;        // Power on the ADC
    AD1CON1bits.FORM = 0b00;     // Set the output bits to integer format
    AD1CON1bits.SSRC = 0b111;    // Select the internal counter to end sampling and start conversion
    AD1CON1bits.ASAM = 0;        // Sampling begins when the SAMP bit is set
   
    // AD1CON2
    AD1CON2bits.VCFG = 0b000;    // Selects AVDD, AVSS (supply voltage to PIC) as Vref
    AD1CON2bits.CSCNA = 0;       // Do not scan inputs
    AD1CON2bits.SMPI = 0b0000;   // Enables interrupts when conversion is completed 
    AD1CON2bits.BUFM = 0;        // configures buffer as a 16-bit word
    AD1CON2bits.ALTS = 0;        // Sets MUX A input multiplexer settings to be used all the time.
    
    // AD1CON3
    AD1CON3bits.ADRC = 0;        // Use system clock
    AD1CON3bits.SAMC = 0b11111;  // Set sample time to be 1/10th of the signal being sampled
    AD1CON3bits.ADCS = 0b11111;  // A/D conversion clock select bits - 64*Tcy
    
    // AD1CHS
    AD1CHSbits.CH0NA = 0;        // Set channel 0 negative input as Vr-
    AD1CHSbits.CH0SA = 0b0101;   // Channel input positive input is AN5
    
    // IO pins
    AD1PCFG = 0x0000;            // Pins configured in analog mode; I/O port read disabled; A/D samples pin voltage
    AD1CSSL = 0x0000;            // Analog channel omitted from input scan
    
/* -------------ADC SAMPLING AND CONVERSION ------------------*/
    
    AD1CON1bits.SAMP = 1; // Start Sampling, conversion starts automatically after SSRC and SAMC settings
    
    while(AD1CON1bits.DONE == 0) {} // Loop until the ADC buffer is full
    
    ADCvalue = ADC1BUF0; // Copy ADC output buffer to ADCvalue
    
    AD1CON1bits.SAMP = 0; // Stop sampling
    AD1CON1bits.ADON = 0; // Turn off ADC
    
    AD1PCFG = 0xFFFF; // Set pins back to digital mode
    
    return ADCvalue; // Returns 10-bit ADC output to calling function
}

// Reads the resistance at pin 16
uint16_t readResistance(void)
{
    uint16_t ADCvalue;   // 16-bit register used to hold ADC converted digital output ADC1BUF0
    uint16_t Vcc = 3;    // Vcc = 3 Volts
    uint16_t R1 = 1000;  // Resistance of the first resistor is 1000 Ohms (from the diagram in the PDF)
    uint16_t resistance; // The calculated resistance value
    
/* -------------ADC INITIALIZATION ------------------*/
    // AD1CON1
    AD1CON1bits.ADON = 1;        // Power on the ADC
    AD1CON1bits.FORM = 0b00;     // Set the output bits to integer format
    AD1CON1bits.SSRC = 0b111;    // Select the internal counter to end sampling and start conversion
    AD1CON1bits.ASAM = 0;        // Sampling begins when the SAMP bit is set
   
    // AD1CON2
    AD1CON2bits.VCFG = 0b000;    // Selects AVDD, AVSS (supply voltage to PIC) as Vref
    AD1CON2bits.CSCNA = 0;       // Do not scan inputs
    AD1CON2bits.SMPI = 0b0000;   // Enables interrupts when conversion is completed 
    AD1CON2bits.BUFM = 0;        // configures buffer as a 16-bit word
    AD1CON2bits.ALTS = 0;        // Sets MUX A input multiplexer settings to be used all the time.
    
    // AD1CON3
    AD1CON3bits.ADRC = 0;        // Use system clock
    AD1CON3bits.SAMC = 0b11111;  // Set sample time to be 1/10th of the signal being sampled
    AD1CON3bits.ADCS = 0b11111;  // A/D conversion clock select bits - 64*Tcy
    
    // AD1CHS
    AD1CHSbits.CH0NA = 0;        // Set channel 0 negative input as Vr-
    AD1CHSbits.CH0SA = 0b1011;   // Channel input positive input is AN11
    
    // IO pins
    AD1PCFG = 0x0000;            // Pins configured in analog mode; I/O port read disabled; A/D samples pin voltage
    AD1CSSL = 0x0000;            // Analog channel omitted from input scan
    
/* -------------ADC SAMPLING AND CONVERSION ------------------*/
    
    AD1CON1bits.SAMP = 1; // Start Sampling, conversion starts automatically after SSRC and SAMC settings
    
    while(AD1CON1bits.DONE == 0) {} // Loop until the ADC buffer is full
    
    ADCvalue = ADC1BUF0; // Copy ADC output buffer to ADCvalue
    
    AD1CON1bits.SAMP = 0; // Stop sampling
    AD1CON1bits.ADON = 0; // Turn off ADC
    
    //Calculate resistance from Voltage read by ADC
    resistance = (ADCvalue * R1) / (Vcc - ADCvalue);
    
    AD1PCFG = 0xFFFF; // Set pins back to digital mode
    
    return resistance; // Returns calculated resistance
}
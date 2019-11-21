/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// set the SPI bus near pin 11 as output
// p11 MOSI -- should be our data out
// p12 MISO -- NOT CONNECTED, would be data in
// p13 SCLK -- clock output
// p14 SSEL -- slave select (chip select)
SPI output(p11, NC, p13, p14);

// use the analog in as our source
AnalogIn input(p20);

// use the analog out for testing only
//AnalogOut testOut(p18);

DigitalOut pin15(p15, 0);
DigitalOut pin16(p16, 0);
DigitalOut pin17(p17, 0);
DigitalOut pin18(p18, 0);
DigitalOut pin19(p19, 0);

Ticker ticker;

// function to do our ADC read and SPI write
void Loop();

// main() runs in its own thread in the OS
int main()
{    
    // SPI bit depth and mode
    // 16 bits
    // mode 0
    output.format(16, 0);
    
    // SPI clock frequency
    // 10MHz
    output.frequency(10000000);

    ticker.attach_us(Loop, 42);

    while (true) 
    {        
        // spinny spinny
    }
}

void Loop()
{
    // read ADC as UINT_16
    unsigned short sample = input.read_u16();
    
    // write to SPI
    output.write(sample);
}
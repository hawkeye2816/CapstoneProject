/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// set the SPI bus near pin 5 as input
SPISlave input(p5, NC, p7, p8);

// set the SPI bus near pin 11 as output
SPI output(p11, NC, p13, p14);

DigitalIn sw(p20, PullDown);

int main()
{
    // set up SPI
    // format: bit width, SPI mode
    input.format(16, 0);
    output.format(16, 0);
    
    // frequency defaults to 1MHz
    int freq = 10000000;
    input.frequency(freq);
    output.frequency(freq);
    
    const int GAIN = 3;
    const int OFFSET = (1 << 11) * (GAIN - 1);
    
    bool apply = true;

    while(true)
    {
        
        // toggle filter on/off with button
        if (sw)
        {
            apply = !apply;
            wait_ms(250);
        }
        
        if (input.receive())
        {
            unsigned short sample = input.read();
            
            if (apply)
            {
                // convert sample to int centered at 0
                int sampleInt = sample >> 4;
                // apply our gain and offset
                sampleInt = sampleInt * GAIN - OFFSET;
                sample = (unsigned short)(sampleInt << 4);
            }
            
            output.write(sample);
        } 
        
        
        //output.write(0xFFF);  
    }
}

#include "mbed.h"

#include <stdlib.h>

#include "DirectForm2.h"

// set the SPI bus near pin 5 as input
SPI input(p5, p6, p7);

// set the SPI bus near pin 11 as output
SPI output(p11, p12, p13);

int main()
{
    DirectForm2 filter(10);
    
    while(1)
    {
        output.write(filter.Apply(input.write(0x0000)));
    }
}
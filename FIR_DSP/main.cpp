#include "mbed.h"

#include <stdlib.h>
#include <vector>
#include <fstream>

#include "DirectFormFIR.h"

// set the SPI bus near pin 5 as input
SPISlave input(p5, NC, p7, p8);

// set the SPI bus near pin 11 as output
SPI output(p11, NC, p13, p14);

// local file system so we can read coefficients from a file
LocalFileSystem local("local");

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
    
    // get our array of filter coefficients
    std::vector<long long> coefficients;
    
    std::ifstream file;
    file.open("/local/coeff.csv");

    while (!file.eof())
    {
        double val = 0.f;
        file >> val;

        // bit shift left by 16 bits
        coefficients.push_back(val * (1<<24));

        if (file.peek() == ',')
        {
            file.ignore(256, ',');
        }
    }
    
    // set up our FIR implementation
    FirFilter filter(coefficients);
    
    bool DoFilter = true;
    
    while(1)
    {
        // toggle filter on/off with button
        if (sw)
        {
            DoFilter = !DoFilter;
            wait_ms(250);
        }
        
        // if the input SPI module has data
        if (input.receive())
        {
            // read the data
            unsigned int sample = input.read();
            
            if (DoFilter)
            {
                // apply the filter
                sample = filter.Apply(sample);
            }
            
            // write the data to the output SPI module
            output.write(sample);
        }
        
    }
}
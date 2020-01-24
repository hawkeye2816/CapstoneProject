**REQUIRES MBED LIBRARY AND MBED COMPATIBLE COMPILER**  
Online compiler available at mbed.com

Basic Structure
===============
The program was designed to be run on multiple mbeds in series, with an Analog-to-Digital conversion performed at the beginning and
a Digital-to-Analog conversion performed at the very end. The modules are intended to use SPI for communication.

ADC
---
The ADC program reads from the analog input pin on the mbed and transmits as SPI host to the following module. Since the LPC1768
has a 12-bit ADC and the register is 16 bits wide, the internal ADC wiring pads the value at the least significant end with 0s.
This is corrected by centering the value in the buffer before transmission.

FIR_DSP
-------
This program implements a Direct Form FIR filter. See [here](https://en.wikipedia.org/wiki/Finite_impulse_response) for a diagram and
detailed information on this filter style.

At initialization, the program looks for a file called 'coeff.csv' and reads it to load filter coefficients and generate the filter. This
file is meant to be directly exported from MatLab via the 'csvwrite' function. While the program will generate a filter as long as the
number of coefficients in the file, I do not recommend a filter length greater than 40, as it seems data corruption or overflow seems
to rapidly become an issue beyond that point. The user will need to test with an oscilloscope to determine the maximum filter length for
any particular sample rate.

BasicGainDSP
------------
As the name implies, this simply multiplies the samples by an integer value.

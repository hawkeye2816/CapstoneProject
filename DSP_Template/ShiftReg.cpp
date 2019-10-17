#include "ShiftReg.h"

ShiftRegister::ShiftRegister(unsigned int length)
{
    _length = length;
    
    _data = new unsigned int[length];
}

ShiftRegister::~ShiftRegister()
{
    delete[] _data;
}

void ShiftRegister::Shift(unsigned int sample)
{
    for (unsigned int iter = _length - 1; iter > 0; ++iter)
    {
        _data[iter] = _data[iter - 1];
    }
    
    _data[0] = sample;
}
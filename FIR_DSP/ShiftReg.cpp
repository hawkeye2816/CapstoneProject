#include "ShiftReg.h"

ShiftRegister::ShiftRegister(unsigned int length)
{
	_length = length;

	_data = new long long[length];

	for (unsigned int iter = 0; iter < length; ++iter)
	{
		_data[iter] = 0;
	}
}

ShiftRegister::~ShiftRegister()
{
	delete[] _data;
}

void ShiftRegister::Shift(long long sample)
{
	for (unsigned int iter = _length - 1; iter > 0; --iter)
	{
		_data[iter] = _data[iter - 1];
	}

	_data[0] = sample;
}

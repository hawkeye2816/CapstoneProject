#include "DirectFormFIR.h"

FirFilter::FirFilter(std::vector<long long> coefficients)
{
	_length = coefficients.size() - 1;
	_delayLine = new ShiftRegister(_length);
	_coefficients = coefficients;
}

FirFilter::~FirFilter()
{
	delete _delayLine;
}

unsigned short FirFilter::Apply(unsigned short sample)
{
	int centeredSample = (int)(sample >> 4);
	centeredSample -= 1 << 11;

	// first tap, no delay
	long long sampOut = centeredSample * _coefficients[0];

	// iterate over delay line
	for (unsigned int iter = 0; iter < _length; ++iter)
	{
		sampOut += _delayLine->Get(iter) * _coefficients[iter + 1];
	}

	// shift the new sample into the delay line
	_delayLine->Shift(centeredSample);

	// return filter output converted back to UINT_16
	int retSamp = (sampOut >> 24) + (1 << 11);
	return (unsigned short)(retSamp << 4);
}

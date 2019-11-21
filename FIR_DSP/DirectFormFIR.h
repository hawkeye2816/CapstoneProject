#ifndef FIR
#define FIR // header guard

#include "ShiftReg.h"

#include <vector>

class FirFilter
{
public:
	FirFilter(std::vector<long long> coefficients);
	~FirFilter();

	unsigned short Apply(unsigned short sample);

private:
	ShiftRegister* _delayLine;
	std::vector<long long> _coefficients;

	unsigned int _length;
};

#endif // header guard

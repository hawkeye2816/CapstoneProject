#include "DirectForm2.h"

DirectForm2::DirectForm2(unsigned int length)
{
    _length = length;
    _reg = new ShiftRegister(length);
    _leftCoeff = new float[length + 1];
    _rightCoeff = new float[length + 1];
    
    for (unsigned int iter = 0; iter < length + 1; ++iter)
    {
        _leftCoeff[iter] = 0;
        _rightCoeff[iter] = 0;
    }
}

DirectForm2::~DirectForm2()
{
    delete _reg;
    delete[] _rightCoeff;
    delete[] _leftCoeff;
}

void DirectForm2::SetForwardCoefficients(float* coefficients, unsigned int length)
{
    // if incoming length is less than filter length, loop over incoming length
    unsigned int upperBound = length < _length ? length : _length;
    
    for (unsigned int iter = 0; iter < upperBound; ++iter)
    {
        _rightCoeff[iter] = coefficients[iter];
    }
}

void DirectForm2::SetReverseCoefficients(float* coefficients, unsigned int length)
{
    // if incoming length is less than filter length, loop over incoming length
    unsigned int upperBound = length < _length ? length : _length;
    
    for (unsigned int iter = 0; iter < upperBound; ++iter)
    {
        _leftCoeff[iter] = coefficients[iter];
    }
}

unsigned int DirectForm2::Apply(unsigned int sample)
{
    ApplyLeft();
    
    unsigned int temp = _currSample;
    
    ApplyRight();
    
    _reg->Shift(temp);
    
    return _currSample;
}

void DirectForm2::ApplyLeft()
{
    // we need to apply coeff[1 -> len + 1] and combine with sample mult by coeff[0]
    // coeff[0] *should* be a 1 and we will assume it is
    double sampleTemp = _currSample; // times 1
    for (unsigned int iter = 0; iter < _reg->GetLength(); ++iter)
    {
        sampleTemp += (float)_reg->Get(iter) * _leftCoeff[iter + 1];
    }
    
    _currSample = (unsigned int)sampleTemp;
}

void DirectForm2::ApplyRight()
{
    // we need to apply coeff[1 -> len + 1] and combine with sample mult by coeff[0]
    // coeff[0] cannot be guaranteed any value this time
    double sampleTemp = _currSample * _rightCoeff[0];
    for (unsigned int iter = 0; iter < _reg->GetLength(); ++iter)
    {
        sampleTemp += (float)_reg->Get(iter) * _rightCoeff[iter + 1];
    }
    
    _currSample = (unsigned int)sampleTemp;
}
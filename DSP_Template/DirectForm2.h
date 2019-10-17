#ifndef DF2_H
#define DF2_H

#include "ShiftReg.h"

class DirectForm2
{
public:
    DirectForm2(unsigned int length = 10);
    ~DirectForm2();
    
    unsigned int Apply(unsigned int sample);
    
    // assumes length + 1 coefficients, will fill from beginning and trail zeros
    // as needed to ensure no array access exceptions
    void SetForwardCoefficients(float* coefficients, unsigned int length); 
    
    // assumes length + 1 coefficients, will fill from beginnint and trail zeros
    // as needed to ensure no array access exceptions
    // first coefficient must be a 1, per direct form 2
    void SetReverseCoefficients(float* coefficients, unsigned int length);
    
private:
    void ApplyLeft();
    void ApplyRight();
      
    float* _leftCoeff;
    float* _rightCoeff;
    
    unsigned int _currSample;
    
    ShiftRegister* _reg;
    unsigned int _length;
};

#endif // header guard
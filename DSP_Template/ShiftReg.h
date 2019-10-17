#ifndef SHIFT_H
#define SHIFT_H

class ShiftRegister
{
public:
    ShiftRegister(unsigned int length = 10);
    ~ShiftRegister();
    
    void Shift(unsigned int sample);
    
    unsigned int operator[](unsigned int i) { return _data[i]; }
    unsigned int Get(unsigned int i) { return _data[i]; }
    
    unsigned int GetLength() { return _length; }
    
private:
    unsigned int _length;
    unsigned int* _data;
};

#endif // header guard
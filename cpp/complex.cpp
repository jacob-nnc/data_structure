#include<stdio.h>
typedef struct
{
    double real;
    double imag;
}complex;
void complex_create(complex *_complex,double _real,double _imag)
{
    _complex->real=_real;
    _complex->imag=_imag;
}
double complex_getreal(complex _complex)
{
    return _complex.real;
}
double complex_getimag(complex _complex)
{
    return _complex.imag;
}
complex complex_add(complex _complex1,complex _complex2)
{
    complex sum;
    complex_create(&sum,complex_getreal(_complex1)+complex_getreal(_complex2),complex_getimag(_complex1)+complex_getimag(_complex2));
    return sum;
}
complex complex_sub(complex _complex1,complex _complex2)
{
    complex sum;
    complex_create(&sum,complex_getreal(_complex1)-complex_getreal(_complex2),complex_getimag(_complex1)-complex_getimag(_complex2));
    return sum;
}
complex complex_mul(complex _complex1,complex _complex2)
{
    complex ret;
    complex_create(&ret,complex_getreal(_complex1)*complex_getreal(_complex2)-complex_getimag(_complex1)*complex_getimag(_complex2),complex_getreal(_complex1)*complex_getimag(_complex2)+complex_getimag(_complex1)*complex_getreal(_complex2));
    return ret;
}

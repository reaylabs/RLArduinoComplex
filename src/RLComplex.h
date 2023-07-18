/*
RLArduinoComplex.h

Description
  Extension of the Complex library by Rob Tillaart.

Author
  ReayLabs
*/

#ifndef _RL_ARDUINO_COMPLEX_H_
#define _RL_ARDUINO_COMPLEX_H_

#include "Arduino.h"

#define LIB_VERSION  (F("1.0.0"))

class RLComplex : public Printable
{
  public:

    RLComplex(const float r = 0.0, const float i = 0.0);

    RLComplex(const RLComplex &c) : re(c.re), im(c.im) {};

    void set(const float r, const float i ) { re = r; im = i; };
    void setReal(const float r)  { re = r; };
    void setImag(const float i ) { im = i; };
    float real() const { return re; };
    float imag() const { return im; };
    void polar(const float modulus, const float phase);
    float phase() const       { return atan2(im, re); };
    float phaseDeg() const    { return phase() * 180.0 / PI; };
    float modulus() const     { return hypot(re, im); };
    float magnitude() const   { return hypot(re, im); };
    float magnitudeDB() const { return 20.0 * log10(hypot(re, im)); };
    String toString(int decimals);

    size_t printTo(Print& p) const;
    
    RLComplex conjugate() const { return RLComplex(re, -im); };
    RLComplex reciprocal() const;

    bool operator == (const RLComplex&) const;
    bool operator != (const RLComplex&) const;


    RLComplex operator - () const;
    RLComplex operator + (const RLComplex&) const;
    RLComplex operator - (const RLComplex&) const;
    RLComplex operator * (const RLComplex&) const;
    RLComplex operator / (const RLComplex&) const;

    RLComplex operator = (const RLComplex&);
    RLComplex& operator += (const RLComplex&);
    RLComplex& operator -= (const RLComplex&);
    RLComplex& operator *= (const RLComplex&);
    RLComplex& operator /= (const RLComplex&);


    RLComplex c_sqrt() const;
    RLComplex c_sqr() const;
    RLComplex c_exp() const;
    RLComplex c_log() const;
    RLComplex c_log10() const;
    RLComplex c_pow(const RLComplex &) const;
    RLComplex c_logn(const RLComplex &) const;


    RLComplex c_sin() const;
    RLComplex c_cos() const;
    RLComplex c_tan() const;
    RLComplex c_asin() const;
    RLComplex c_acos() const;
    RLComplex c_atan() const;


    RLComplex c_csc() const;
    RLComplex c_sec() const;
    RLComplex c_cot() const;
    RLComplex c_acsc() const;
    RLComplex c_asec() const;
    RLComplex c_acot() const;


    RLComplex c_sinh() const;
    RLComplex c_cosh() const;
    RLComplex c_tanh() const;
    RLComplex c_asinh() const;
    RLComplex c_acosh() const;
    RLComplex c_atanh() const;


    RLComplex c_csch() const;
    RLComplex c_sech() const;
    RLComplex c_coth() const;
    RLComplex c_acsch() const;
    RLComplex c_asech() const;
    RLComplex c_acoth() const;



  protected:
    float re;
    float im;
    RLComplex gonioHelper1(const byte) const;
    RLComplex gonioHelper2(const byte) const;
};

static const RLComplex one(1, 0);

#endif // _RL_ARDUINO_COMPLEX_H_
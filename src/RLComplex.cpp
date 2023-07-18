/*
RLArduinoComplex.cpp

Description
  RLComplex Number Library 

Author
  ReayLabs
*/

#include "RLComplex.h"

RLComplex::RLComplex(const float r, const float i) {
  re = r;
  im = i;
};

size_t RLComplex::printTo(Print& p) const
{
  size_t n = 0;
  n += p.print(re, 3);
  if (im >= 0) {
    n += p.print('+');
  }
  n += p.print(im, 3);
  n += p.print('j');
  return n;
};

String RLComplex::toString(int decimals)
{
  String s = String(re, decimals);
  if (im >= 0) {
    s += String('+');
  }  
  s += String(im, decimals) + String('j');
  return s;
};

void RLComplex::polar(const float modulus, const float phase)
{
  re = modulus * cos(phase);
  im = modulus * sin(phase);
}


RLComplex RLComplex::reciprocal() const
{
  float f = 1.0 / (re * re + im * im);
  float r = re * f;
  float i = -im * f;
  return RLComplex(r, i);
}

//
//  EQUALITIES
//
bool RLComplex::operator == (const RLComplex &c) const
{
  return (re == c.re) && (im == c.im);
}


bool RLComplex::operator != (const RLComplex &c) const
{
  return (re != c.re) || (im != c.im);
}


//
//  NEGATE
//
RLComplex RLComplex::operator - () const
{
  return RLComplex(-re, -im);
}


//
//  BASIC MATH
//
RLComplex RLComplex::operator + (const RLComplex &c) const
{
  return RLComplex(re + c.re, im + c.im);
}


RLComplex RLComplex::operator - (const RLComplex &c) const
{
  return RLComplex(re - c.re, im - c.im);
}


RLComplex RLComplex::operator * (const RLComplex &c) const
{
  float r = re * c.re - im * c.im;
  float i = re * c.im + im * c.re;
  return RLComplex(r, i);
}


RLComplex RLComplex::operator / (const RLComplex &c) const
{
  float f = 1.0/(c.re * c.re + c.im * c.im);
  float r = (re * c.re + im * c.im) * f;
  float i = (im * c.re - re * c.im) * f;
  return RLComplex(r, i);
}

RLComplex RLComplex::operator = (const RLComplex &c)
{
  re = c.re;
  im = c.im;
  return *this;
}

RLComplex& RLComplex::operator += (const RLComplex &c)
{
  re += c.re;
  im += c.im;
  return *this;
}


RLComplex& RLComplex::operator -= (const RLComplex &c)
{
  re -= c.re;
  im -= c.im;
  return *this;
}


RLComplex& RLComplex::operator *= (const RLComplex &c)
{
  float r = re * c.re - im * c.im;
  float i = re * c.im + im * c.re;
  re = r;
  im = i;
  return *this;
}


RLComplex& RLComplex::operator /= (const RLComplex &c)
{
  float f = 1.0/(c.re * c.re + c.im * c.im);
  float r = (re * c.re + im * c.im) * f;
  float i = (im * c.re - re * c.im) * f;
  re = r;
  im = i;
  return *this;
}


//
//  POWER FUNCTIONS
//
RLComplex RLComplex::c_sqr() const
{
  float r = re * re - im * im;
  float i = 2 * re * im;
  return RLComplex(r, i);
}


RLComplex RLComplex::c_sqrt() const
{
  float m = modulus();
  float r = sqrt(0.5 * (m + re));
  float i = sqrt(0.5 * (m - re));
  if (im < 0) i = -i;
  return RLComplex(r, i);
}


RLComplex RLComplex::c_exp() const
{
  float e = exp(re);
  return RLComplex(e * cos(im), e * sin(im));
}


RLComplex RLComplex::c_log() const
{
  float m = modulus();
  float p = phase();
  if (p > PI) p -= 2 * PI;
  return RLComplex(log(m), p);
}


RLComplex RLComplex::c_pow(const RLComplex &c) const
{
  RLComplex t = c_log();
  t = t * c;
  return t.c_exp();
}


RLComplex RLComplex::c_logn(const RLComplex &c) const
{
  RLComplex t = c;
  return c_log()/t.c_log();
}


RLComplex RLComplex::c_log10() const
{
  return c_logn(10);
}


//
//  GONIO I - SIN COS TAN
//
RLComplex RLComplex::c_sin() const
{
  return RLComplex(sin(re) * cosh(im), cos(re) * sinh(im));
}


RLComplex RLComplex::c_cos() const
{
  return RLComplex(cos(re) * cosh(im), -sin(re) * sinh(im));
}


RLComplex RLComplex::c_tan() const
{
  return c_sin() / c_cos();
}


RLComplex RLComplex::gonioHelper1(const byte mode) const
{
  RLComplex c = (one - this->c_sqr()).c_sqrt();
  if (mode == 0)
  {
    c = c + *this * RLComplex(0,-1);
  }
  else
  {
    c = *this + c * RLComplex(0,-1);
  }
  c = c.c_log() * RLComplex(0,1);
  return c;
}


RLComplex RLComplex::c_asin() const
{
  return gonioHelper1(0);
}


RLComplex RLComplex::c_acos() const
{
  return gonioHelper1(1);
}


RLComplex RLComplex::c_atan() const
{
  return (RLComplex(0,-1) * (RLComplex(re, im - 1)/RLComplex(-re, -im - 1)).c_log()) * 0.5;
}


//
//  GONIO II - CSC SEC COT
//
RLComplex RLComplex::c_csc() const
{
  return one / c_sin();
}


RLComplex RLComplex::c_sec() const
{
  return one / c_cos();
}


RLComplex RLComplex::c_cot() const
{
  return one / c_tan();
}


RLComplex RLComplex::c_acsc() const
{
  return (one / *this).c_asin();
}


RLComplex RLComplex::c_asec() const
{
  return (one / *this).c_acos();
}


RLComplex RLComplex::c_acot() const
{
  return (one / *this).c_atan();
}


//
//  GONIO HYPERBOLICUS I
//
RLComplex RLComplex::c_sinh() const
{
  return RLComplex(cos(im) * sinh(re), sin(im) * cosh(re));
}


RLComplex RLComplex::c_cosh() const
{
  return RLComplex(cos(im) * cosh(re), sin(im) * sinh(re));
}


RLComplex RLComplex::c_tanh() const
{
  return c_sinh() / c_cosh();
}


RLComplex RLComplex::gonioHelper2(const byte mode) const
{
  RLComplex c = c_sqr();
  if (mode == 0)
  {
    c += 1;
  }
  else
  {
    c -= 1;
  }
  c = (*this + c.c_sqrt()).c_log();
  return c;
}


RLComplex RLComplex::c_asinh() const
{
  return gonioHelper2(0);
}


RLComplex RLComplex::c_acosh() const
{
  return gonioHelper2(1);
}


RLComplex RLComplex::c_atanh() const
{
  RLComplex c = (*this + one).c_log();
  c = c - (-(*this - one)).c_log();
  return c * 0.5;
}


//
//  GONIO HYPERBOLICUS II
//
RLComplex RLComplex::c_csch() const
{
  return one / c_sinh();
}


RLComplex RLComplex::c_sech() const
{
  return one / c_cosh();
}


RLComplex RLComplex::c_coth() const
{
  return one / c_tanh();
}


RLComplex RLComplex::c_acsch() const
{
  return (one / *this).c_asinh();
}


RLComplex RLComplex::c_asech() const
{
  return (one / *this).c_acosh();
}


RLComplex RLComplex::c_acoth() const
{
  return (one / *this).c_atanh();
}

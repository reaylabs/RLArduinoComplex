/*
RLArduinoComplexZ.h

Description
    A class based on RLComplex to handle complex impedances

Author
  ReayLabs
*/

#ifndef _RL_ARDUINO_COMPLEX_Z_H_
#define _RL_ARDUINO_COMPLEX_Z_H_

#include "RLComplex.h"

//Class for a series resistor-inductor-capacitor
class RLComplexZ: public RLComplex
{
  public:
    explicit RLComplexZ (const float resistance = 0.0, const float inductance = 0.0, const float capacitance = 0.0, const float frequency = 0.0):RLComplex(0,0)
    {
        _r = resistance;
        _l = inductance;
        _c = capacitance;
        _f = frequency;
        _updateValues();
    }

    RLComplexZ operator = (const RLComplexZ& z) {
      _r = z._r;
      _l = z._l;
      _c = z._c;
      _f = z._f;
      return *this;
    }

    RLComplexZ& operator=(const RLComplex& other) {
      re = other.real();
      im = other.imag();
      return *this;
    }
    
    float cap() 
    {
      return _c;
    }

    float ind() 
    {
      return _l;
    }
    
    float freq() 
    {
      return _f;
    }

    float res() 
    {
      return _r;
    }
   
    void setCap(const float capacitance)
    {
      _c = capacitance;
      _updateValues();
    }

    void setFreq(const float frequency)
    {
      _f = frequency;
      _updateValues();
    }
    
    void setInd(const float inductance)
    {
      _l = inductance;
      _updateValues();
    }

    void setRes(const float resistance)
    {
      _r = resistance;
      _updateValues();
    }

  protected:
    float _r;
    float _l;
    float _c;
    float _f;
    void _updateValues() {
      im = _l * TWO_PI * _f ;
      if (_c != 0 && _f != 0) {
        im -= 1.0 / (_c * TWO_PI * _f);
      }
      re = _r;
    };
};

#endif // _RL_ARDUINO_COMPLEX_Z_H_
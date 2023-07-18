/*
RLComplexUnitTest.ino

Description
  Unit test of the RLComplex class using the AUnit framework.

Author
  ReayLabs
*/

#include "RLComplex.h"
#include "AUnit.h"

test(test_constructor)
{
  RLComplex c1(10.0, -2.0);
  RLComplex c2(3, 0);
  RLComplex c3(-10, 4);
  RLComplex c4(-5,-5);
  RLComplex c5;  // (0, 0)

  assertEqual(10.0, c1.real());
  assertEqual(-2.0, c1.imag());
  
  assertEqual( 3.0, c2.real());
  assertEqual( 0.0, c2.imag());
  
  assertEqual(-10.0,  c3.real());
  assertEqual(4.0,  c3.imag());

  assertEqual(-5.0, c4.real());
  assertEqual(-5.0, c4.imag());
  assertEqual(0.0, c5.real());
  assertEqual(0.0, c5.imag());
  

  // one is a default available var.
  assertEqual(1.0, one.real());
  assertEqual(0.0, one.imag());

  // polar notation setter.
  c1.polar(5.0, PI/4);
  assertNear(5.0, c1.modulus(), 0.0001);
  assertNear(PI/4, c1.phase(), 0.0001);
};


test(test_basic_math)
{
  RLComplex a(10.0, -2.5);
  RLComplex b(3, 1);

  RLComplex c1 = a + b;
  assertEqual(13.0, c1.real());
  assertEqual(-1.5, c1.imag());

  RLComplex c2 = a - b;
  assertEqual(7.0,  c2.real());
  assertEqual(-3.5, c2.imag());

  RLComplex c3 = a * b;
  assertEqual(32.5,  c3.real());
  assertEqual(2.5,  c3.imag());

  RLComplex c4 = a / b;
  assertEqual(2.75, c4.real());
  assertEqual(-1.75, c4.imag());

  RLComplex c5 = -a;
  assertEqual(-10.0, c5.real());
  assertEqual(2.5, c5.imag());

  a += b;
  assertEqual(13.0, a.real());
  assertEqual(-1.5, a.imag());

  a -= b;
  assertEqual(10.0,  a.real());
  assertEqual(-2.5, a.imag());

  a *= b;
  assertEqual(32.5,  a.real());
  assertEqual(2.5,  a.imag());

  a /= b;
  assertEqual(10.0, a.real());
  assertEqual(-2.5, a.imag());
};


test(test_basic_functions)
{
  RLComplex a;
  assertEqual(0.0, a.real());
  assertEqual(0.0, a.imag());

  a.set(5, 34);
  assertEqual(5.0, a.real());
  assertEqual(34.0, a.imag());

  a.setReal(10);
  assertEqual(10.0, a.real());
  assertEqual(34.0, a.imag());

  a.setImag(-2.5);
  assertEqual(10.0, a.real());
  assertEqual(-2.5, a.imag());

  float ph = a.phase();
  assertNear(-0.244979, ph, 0.0001);

  float mod = a.modulus();
  assertNear(10.3078, mod, 0.0001);

  RLComplex conj = a.conjugate();
  assertEqual(10.0, conj.real());
  assertEqual(2.5, conj.imag());

  RLComplex reci = a.reciprocal();
  assertNear(0.0941176, reci.real(), 0.0001);
  assertNear(0.0235294, reci.imag(), 0.0001);

  reci *= a;
  assertNear(1.0, reci.real(), 0.0001);
  assertNear(0.0, reci.imag(), 0.0001);
};


test(test_power_functions)
{
  RLComplex a(3, 4);
  RLComplex b;

  b = a.c_sqrt();
  assertEqual(2.0, b.real());
  assertEqual(1.0, b.imag());

  b = a.c_sqr();
  assertEqual(-7.0, b.real());
  assertEqual(24.0, b.imag());

  b = a.c_exp();
  assertNear(-13.1288, b.real(), 0.0001);
  assertNear(-15.2008, b.imag(), 0.0001);

  b = a.c_log();
  assertNear(1.60944, b.real(), 0.0001);
  assertNear(0.927295, b.imag(), 0.0001);

  b = a.c_log10();
  assertNear(0.69897, b.real(), 0.0001);
  assertNear(0.402719, b.imag(), 0.0001);

  b = a.c_pow(a);
  assertNear(-2.99799, b.real(), 0.0001);
  assertNear(0.623786, b.imag(), 0.0001);

  b = a.c_logn(a);
  assertEqual(1.0, b.real());
  assertEqual(0.0, b.imag());
};


test(test_gonio_functions_I)
{
  RLComplex a(3, 4);
  RLComplex b;

  b = a.c_sin();
  assertNear(3.85374, b.real(), 0.0001);
  assertNear(-27.0168, b.imag(), 0.0001);

  b = a.c_cos();
  assertNear(-27.0349, b.real(), 0.0001);
  assertNear(-3.85115, b.imag(), 0.0001);

  b = a.c_tan();
  assertNear(-0.000187318, b.real(), 0.0001);
  assertNear(0.999356, b.imag(), 0.0001);

  b = a.c_asin();
  assertNear(0.633984, b.real(), 0.0001);
  assertNear(2.30551, b.imag(), 0.0001);

  b = a.c_acos();
  assertNear(0.936813, b.real(), 0.0001);
  assertNear(-2.30551, b.imag(), 0.0001);

  b = a.c_atan();
  assertNear(1.44831, b.real(), 0.0001);
  assertNear(0.158997, b.imag(), 0.0001);
};


// Run the tests
void setup() {
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  aunit::TestRunner::run();
}

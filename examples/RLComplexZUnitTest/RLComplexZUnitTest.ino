/*
RLComplexZUnitTest.ino

Description
  Unit test of the RLComplexZ class using the AUnit framework.

Author
  ReayLabs
*/

#include "RLComplexZ.h"
#include "AUnit.h"

// Define tolerance variables for floating-point comparisons
const float toleranceResistance = 1e-6;
const float toleranceInductance = 1e-15;
const float toleranceCapacitance = 1e-15;
const float toleranceFrequency = 1e-6;

test(InitializationTest) {
  // Test the initialization values with tolerance
  RLComplexZ z(10.0, 1e-9, 1e-12, 1000.0);
  assertNear(z.res(), 10.0, toleranceResistance);
  assertNear(z.ind(), 1e-9, toleranceInductance);
  assertNear(z.cap(), 1e-12, toleranceCapacitance);
  assertNear(z.freq(), 1000.0, toleranceFrequency);

  RLComplexZ x;
  assertNear(x.real(), 0.0, toleranceResistance);
  assertNear(x.imag(), 0.0, toleranceResistance);

  RLComplexZ r(10000.0);
  assertNear(r.real(), 10000.0, toleranceResistance);
  assertNear(r.imag(), 0.0, toleranceResistance);
};

test(SettersAndGettersTest) {
  // Test the setter and getter methods with tolerance
  RLComplexZ z(10.0, 0.2, 0.001, 1000.0);
  z.setRes(5.0);
  assertNear(z.res(), 5.0, toleranceResistance);
  z.setInd(1e-9);
  assertNear(z.ind(), 1e-9, toleranceInductance);
  z.setCap(1e-12);
  assertNear(z.cap(), 1e-12, toleranceCapacitance);
  z.setFreq(500.0);
  assertNear(z.freq(), 500.0, toleranceFrequency);
};

test(AssignmentOperatorTest) {
  // Test the assignment operator with tolerance
  RLComplexZ z1(10.0, 2e-9, 1e-12, 1000.0);
  RLComplexZ z2(20.0, 3e-9, 2e-12, 2000.0);
  z1 = z2;
  assertNear(z1.res(), 20.0, toleranceResistance);
  assertNear(z1.ind(), 3e-9, toleranceInductance);
  assertNear(z1.cap(), 2e-12, toleranceCapacitance);
  assertNear(z1.freq(), 2000.0, toleranceFrequency);

  RLComplexZ r(12345.00);
  RLComplex w = r;
  assertNear(w.real(), 12345.0, toleranceResistance);
  assertNear(w.imag(), 0.0, toleranceResistance);
};

test(ImpedanceValues) {
  // Test impedance values with tolerance
  RLComplexZ z3(1000.0, 1e-9, 100e-12, 1.0e6);
  assertNear(z3.magnitude(), 1879.63, 0.01);
  assertNear(z3.magnitudeDB(), 65.481, 0.001);
  assertNear(z3.phaseDeg(), -57.858, 0.0001);
  assertNear(z3.phase(), -1.0098, 0.0001);
  assertNear(z3.real(), 1000.00, 0.0001);
  assertNear(z3.imag(), -1591.54, 0.01);
};

// Run the tests
void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.print("Library Version :");
  Serial.println(LIB_VERSION);
}

void loop() {
  aunit::TestRunner::run();
}

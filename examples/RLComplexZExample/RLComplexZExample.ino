/*
RLComplexZExample.ino

Description
  Example of the RLComplexZ class.

Author
  ReayLabs
*/

#include "RLComplexZ.h"

void setup() {
    Serial.begin(115200);
    while(!Serial);

    //Create the impedances
    float frequency = 1e3;
    float resistance = 1e3;
    float inductance = 1e-6;
    float capacitance = 1e-6;
    RLComplexZ z;
    RLComplexZ r(resistance);
    RLComplexZ l(0, inductance, 0, frequency);
    RLComplexZ c(0, 0, capacitance, frequency);
    RLComplexZ rc(resistance, 0, capacitance, frequency);
    RLComplexZ rl(resistance, inductance, 0, frequency);
    RLComplexZ rlc(resistance, inductance, capacitance, frequency);
    RLComplexZ lc(0, inductance, capacitance, frequency);

    // Print the complex values
    int digits = 3;
    Serial.println("\n*** Component Values *** "); 
    Serial.println("Z: " + z.toString(digits)); 
    Serial.print("R: "); Serial.println(r);   //print directly
    Serial.println("L: " + l.toString(digits)); //print using toString
    Serial.println("C: " + c.toString(digits));
    Serial.println("RC: " + rc.toString(digits));
    Serial.println("RL: " + rl.toString(digits));
    Serial.println("RLC: " + rlc.toString(digits));
    Serial.println("LC: " + lc.toString(digits));

    // Print the RLC values
    z = c;
    frequency = 1 / (TWO_PI * capacitance * resistance);
    z.setFreq(frequency);
    Serial.println("\n*** Capacitor Z Values ***");
    Serial.println("Frequency: " + String(frequency, digits));
    Serial.println("Complex Value: " + z.toString(digits));
    Serial.println("Magnitude: " + String(z.magnitude(),digits));
    Serial.println("Magnitude dB: " + String(z.magnitudeDB(),digits));
    Serial.println("Phase Rad: " + String(z.phase(),digits));
    Serial.println("Phase Deg: " + String(z.phaseDeg(),digits));

    //RC Filter Example
    Serial.println("\n*** RC Filter Example ***");
    Serial.println("FREQ\tMAG(dB)\tPhase(Deg)");
    float d = 10;
    for (int decade = 0; decade < 3; decade++) {
      for (int i = 1; i < 10; i++ ) {
        float f = d * i;
        c.setFreq(f);
        r.setFreq(f);
        z = c / (c + r);
        Serial.print(f,1);
        Serial.print("\t");
        Serial.print(z.magnitudeDB(),2);
        Serial.print("\t");
        Serial.println(z.phaseDeg(),2);
      }
      d *= 10;
    }
}
 
 void loop () {
 }
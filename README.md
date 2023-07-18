# RLArduinoComplex
Arduino library for complex mathematical operations and electrical impedance calculations based on the Complex library by Rob Tillaart.

The libary contains the base RLComplex class for making complex number calculations, and the derived RLComplexZ class which adds the ability to model electrical impedances.

## RC Filter Example
```C++
#include "RLComplexZ.h"

void setup() {
    //Open the serial port
    Serial.begin(115200);
    while(!Serial);

    //Set the filter values
    float resistance = 1e3;
    float inductance = 0;
    float capacitance = 1e-6;
    float frequency = 1.0 / (TWO_PI * resistance * capacitance); //-3dB frequency

    //Create the filter components
    RLComplexZ r(resistance);
    resistance = 0;
    RLComplexZ c(resistance, inductance, capacitance, frequency);
    RLComplex z;

    //Calculate the filter impedance
    z = c / (c + r);

    //Print the filter values 
    Serial.println("Frequency: " + String(frequency, 4));           //159.1549 Hz
    Serial.println("Complex Value: " + z.toString(3));              //0.500-0.500j
    Serial.println("Real: " + String(z.real(), 3));                 //0.500
    Serial.println("Imaginary: " + String(z.imag(), 3));            //-0.500
    Serial.println("Magnitude: " + String(z.magnitude(), 3));       //0.707
    Serial.println("Magnitude dB: " + String(z.magnitudeDB(), 1));  //-3.0 dB
    Serial.println("Phase Rad: " + String(z.phase(), 3));           //-0.785 rad
    Serial.println("Phase Deg: " + String(z.phaseDeg(), 1));        //-45.0 deg
}

void loop() {
}
```







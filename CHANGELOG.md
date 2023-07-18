# Change Log RLComplex and RLComplexZ

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.0] - 2023-07-14
- forked the Complex library 0.3.2 by Rob Tillaart
- changed the name to RLComplex. The Complex library would not compile on the ARM processor due to a naming conflict.
- modified the RLComplex.printTo function to include a + or - character between the im and re values. Changed the i to j for electrical engineers.
- Added the RLComplex.magnitude() function
- Added the RLComplex.magnitudeDb() function
- Added the RLComplex.toString() function
- Added the RLComplex.phaseDeg() function
- Added the RLComplexZ class for solving complex electric impedance circuits.
- Modified and added examples
- Modified the LICENSE file to include ReayLabs and changed the dates.
- Modified the README.md file to include the changes.
- Modified the library.properties file
- Added the unit tests
Team memebers: Ethan Bechtel, Grant Bouvin

This is the code for our headlight system. It is able to turn the car engine on and off
based on the ignition button and whether the driver sitting button is pressed. If the engine
is on then the headlights will be controlled by a dial with three positions: ON/OFF/AUTO.
The first two are self explanitory, ON means the headlights are on, and OFF means the headlights
are off. The AUTO position means that the car decides whether the headlights should be on or off
based on the ambient light levels. 

This code was based on the following repository: https://github.com/armBookCodeExamples/example_4-1-new

Testing results:
+---------------------------------------------------------------------------------------------------------------------------------------------------------+
| Ignition Subsystem                                                                                                                                      |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Specification                                                                                                                             | Test Result |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Start the engine (i.e., light the blue LED) while the driver’s seat is occupied and when the ignition button is pushed and then released. | Pass        |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Keep the engine running even if the driver should exit the vehicle.                                                                       | Pass        |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| When the engine is running, stop the engine when the ignition button is pushed                                                            | Pass        |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Headlight Subsystem                                                                                                                                     |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Specification                                                                                                                             | Test Result |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Dial correctly sets headlight mode (ie ON/OFF/AUTO)                                                                                       | Pass        |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| AUTO setting correctly sets headlights on or off based on light sensor input                                                              | Pass        |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Headlights delay turning on by one second and turning off by two seconds without compromising system responsiveness                       | Pass        |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+
| Headlights turn off when engine is turned off                                                                                             | Pass        |
+-------------------------------------------------------------------------------------------------------------------------------------------+-------------+

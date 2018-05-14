# ShotSecs
Created a little timer that will keep track of how long power (240v) is applied. Originally developed to measure Espresso shots time, but probably useful for other applications.
The usual warnings about tinkering with 240V AC apply!!!

### Introduction
The original idea was that the logic and PSA would be housed inside the espressomachine, and the 7 segment display would be glued/mounted to the exterior of the machine. Hence they are two separate parts connected by a 10-strand data cable
### Hardware
The hardware consists of a little PCB (Kicad schematic & layout included) that hold a Atmega328p, two transistors and 10 resistors to control the 7-segment display.
On the input side I used some resistors and a optocoupler to detect power applied.
PSU, Atmega, optocoupler, resistors and transistors is mounted on the same PCB (220V and 5 V), intended to be drowned in a resin box when donw.

#### Connections (240Volts)
The timer needs a regular 240V connection to power up the Atmega and display. In addition it needs a connection of the applied power
Connect either P-N-Pd or N-P-Nd on the tree terminal block.
Where   P = phase or live wire from 240V mains
        N = null or neutral wire from 240V mains
        Pd= Phase from device to be measured
        Nd= null from device to be measured


### Software
The software is written in AVR C. It essentially is a timer that runs while power is detected by the optocoupler. The display will 'hold' the last known value if power is stopped. On re-applying the power the timer will restart at 0.

Have fun and be careful.
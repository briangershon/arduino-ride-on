# Arduino-powered Ride-On

Maker: Brian Gershon, Jan 2014

We inherited an older version of a Disney Princess Activity Ride-On toy that was in good shape, but the electronics didn't work.

I tried to get things working, but wires were frail and battery wires were fried.

I decided to rip out the old electronics and wires, add an Arduino Pro Mini and a lot of solder and rewiring, and was able to repurpose its 6 buttons/switches/levers, 2 LEDs blinkers and speaker.

<img src="https://raw.github.com/briangershon/arduino-ride-on/master/images/photo1.jpg" width="400px" />

## Hardware

The Arduino Pro Mini was ideal because:

* It supports a generous power-saving mode, uses 3V (instead of 5V) and is small.

## Software

This Arduino code does three things:

* Support Arduino Mini Pro sleep mode to conserve battery. Powers down after about 30 seconds of no use.

* Toy's ignition switch powers it back up

* The main loop flashes the left/right blinkers slowly, then speeds up when a button pressed

* Keypress, power-up and power-down make different sound. Several buttons trigger more elaborate songs.

## Special thanks to these authors:

* [Mario Bros Tunes](http://www.linuxcircle.com/2013/03/31/playing-mario-bros-tune-with-arduino-and-piezo-buzzer/)

* [Arduino Sleep](http://playground.arduino.cc/Learning/arduinoSleepCode)

* [Arduino Tone example](http://arduino.cc/en/Tutorial/tone)

## Future improvements

* I used two different sound implementations, these could be merged.

* I'd like to spend more time hunting down better sounds, maybe leveraging [Play RTTTL Sounds with Arduino](http://letsmakerobots.com/node/20743) or even a more sophisticated sound system (SD card with sound files).

* A pressure sensor under the seat might be a fun addition, as well as adding more LEDs.

<img src="https://raw.github.com/briangershon/arduino-ride-on/master/images/photo2.jpg" width="400px" />

<img src="https://raw.github.com/briangershon/arduino-ride-on/master/images/photo3.jpg" width="400px" />

<img src="https://raw.github.com/briangershon/arduino-ride-on/master/images/photo4.jpg" width="400px" />


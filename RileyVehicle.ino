/*
  Riley's Disney Vehicle
  
  Pin 2 = Horn Button
  Pin 3 = Ignition Switch (eventually interrupt to wake from sleep)
  Pin 4 = Castle Button
  Pin 5 = Forward/Back switch
  Pin 6 = Front left flower button
  Pin 7 = Front right flower button
  Pin 8 = Speaker
  Pin 12 = Left turn signal LED
  Pin 13 = Right turn signal LED
 */
 
 #include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

const int buttonHorn = 2;
const int buttonIgnition = 3;
const int buttonCastle = 4;
const int buttonFrontBack = 5;
const int buttonLeftFlower = 6;
const int buttonRightFlower = 7;

int cyclesToFastBlink = 0;

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int green_led = 13;
const int red_led = 12;

int blink_delay = 1000;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(buttonHorn, INPUT);
  digitalWrite(buttonHorn, HIGH);  // enable pull-up

  pinMode(buttonIgnition, INPUT);
  digitalWrite(buttonIgnition, HIGH);  // enable pull-up

  pinMode(buttonCastle, INPUT);
  digitalWrite(buttonCastle, HIGH);  // enable pull-up

  pinMode(buttonFrontBack, INPUT);
  digitalWrite(buttonFrontBack, HIGH);  // enable pull-up

  pinMode(buttonLeftFlower, INPUT);
  digitalWrite(buttonLeftFlower, HIGH);  // enable pull-up

  pinMode(buttonRightFlower, INPUT);
  digitalWrite(buttonRightFlower, HIGH);  // enable pull-up

  // initialize the digital pin as an output.
  pinMode(green_led, OUTPUT);     
  pinMode(red_led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  
//  if (digitalRead(buttonHorn) == LOW) {
//    playHornMelody();
//  }

  if (digitalRead(buttonHorn) == LOW ||
    digitalRead(buttonIgnition) == LOW ||
    digitalRead(buttonCastle) == LOW ||
    digitalRead(buttonFrontBack) == LOW ||
    digitalRead(buttonLeftFlower) == LOW ||
    digitalRead(buttonRightFlower) == LOW
    ) {     
      if (cyclesToFastBlink == 0) {
        playHornMelody();
        cyclesToFastBlink = 10;
      }
  } 

  if (cyclesToFastBlink > 0) {
    blink_delay = 200;
    cyclesToFastBlink--;
  } else {
    blink_delay = 1000;
  }  

  digitalWrite(green_led, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(red_led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(blink_delay);               // wait for a second
  digitalWrite(green_led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(red_led, HIGH);    // turn the LED off by making the voltage LOW
  delay(blink_delay);               // wait for a second
}

void playHornMelody() {
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}


/*
  Riley's Disney Vehicle
  Author: Brian Gershon, Jan 2014
  
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
 
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "pitches.h"

const int buttonHorn = 2;
const int buttonIgnition = 3;
const int buttonCastle = 4;
const int buttonFrontBack = 5;
const int buttonLeftFlower = 6;
const int buttonRightFlower = 7;

int cyclesToFastBlink = 0;

const int green_led = 13;
const int red_led = 12;

int blink_delay = 1000;

const int MAX_CYCLES_UNTIL_SLEEP = 70;
int cyclesUntilSleep = 0;
boolean triggerWakeUpSound = false;

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

  pinMode(8, OUTPUT);//buzzer

  sleepNow();
}

// the loop routine runs over and over again forever:
void loop() {
  if (triggerWakeUpSound) {
    playWakeup();
    triggerWakeUpSound = false;
  }

  if (digitalRead(buttonHorn) == LOW) {
    playHornMelody();
  }

  if (digitalRead(buttonCastle) == LOW) {
    sing(1);
  }

  if (digitalRead(buttonFrontBack) == LOW) {
    sing(2);
  }

  if (digitalRead(buttonHorn) == LOW ||
    digitalRead(buttonIgnition) == LOW ||
    digitalRead(buttonCastle) == LOW ||
    digitalRead(buttonFrontBack) == LOW ||
    digitalRead(buttonLeftFlower) == LOW ||
    digitalRead(buttonRightFlower) == LOW
    ) {
      playKeypress();
      cyclesUntilSleep = MAX_CYCLES_UNTIL_SLEEP;  //reset countdown if button pressed
      if (cyclesToFastBlink == 0) {
        //playHornMelody();
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
  
  if (cyclesUntilSleep == 0) {
    playAboutToSleep();
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, LOW);
    sleepNow();
  }
  cyclesUntilSleep--;
}

void playAboutToSleep() {
  int wakeUpMelody[] = {
    NOTE_E4, NOTE_D4, NOTE_C4};
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 3; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/16;
    tone(8, wakeUpMelody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void playKeypress() {
    int noteDuration = 1000/16;
    tone(8, NOTE_C5, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
}

void playWakeup() {
  int wakeUpMelody[] = {
    NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4};
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 4; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/8;
    tone(8, wakeUpMelody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void playHornMelody() {
  // notes in the melody:
  int melody[] = {
    NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 8, 8, 4,4,4,4,4 };

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

/* SLEEP */

void sleepNow()         // here we put the arduino to sleep
{
    /* Now is the time to set the sleep mode. In the Atmega8 datasheet
     * http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
     * there is a list of sleep modes which explains which clocks and 
     * wake up sources are available in which sleep modus.
     *
     * In the avr/sleep.h file, the call names of these sleep modus are to be found:
     *
     * The 5 different modes are:
     *     SLEEP_MODE_IDLE         -the least power savings 
     *     SLEEP_MODE_ADC
     *     SLEEP_MODE_PWR_SAVE
     *     SLEEP_MODE_STANDBY
     *     SLEEP_MODE_PWR_DOWN     -the most power savings
     *
     * For now, we want as much power savings as possible, 
     * so we choose the according sleep modus: SLEEP_MODE_PWR_DOWN
     * 
     */  
     
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here

    sleep_enable();              // enables the sleep bit in the mcucr register
                                 // so sleep is possible. just a safety pin 

    /* Now is time to enable a interrupt. we do it here so an 
     * accidentally pushed interrupt button doesn't interrupt 
     * our running program. if you want to be able to run 
     * interrupt code besides the sleep function, place it in 
     * setup() for example.
     * 
     * In the function call attachInterrupt(A, B, C)
     * A   can be either 0 or 1 for interrupts on pin 2 or 3.   
     * 
     * B   Name of a function you want to execute at interrupt for A.
     *
     * C   Trigger mode of the interrupt pin. can be:
     *             LOW        a low level triggers
     *             CHANGE     a change in level triggers
     *             RISING     a rising edge of a level triggers
     *             FALLING    a falling edge of a level triggers
     *
     * In all but the IDLE sleep modes only LOW can be used.
     */

//    attachInterrupt(1,wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
//                                       // wakeUpNow when pin 2 gets LOW 
    attachInterrupt(1, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                       // wakeUpNow when pin 2 gets LOW 

    sleep_mode();                // here the device is actually put to sleep!!
                                 // 

    sleep_disable();             // first thing after waking from sleep:
                                 // disable sleep...
    detachInterrupt(1);          // disables interrupt 0 on pin 2 so the 
                                 // wakeUpNow code will not be executed 
                                 // during normal running time.
    delay(1000);                 // wat 2 sec. so humans can notice the
                                 // interrupt. 
                                 // LED to show the interrupt is handled
//    digitalWrite (interruptPin, LOW);      // turn off the interrupt LED

}

void wakeUpNow()        // here the interrupt is handled after wakeup
{
  //execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  cyclesUntilSleep = MAX_CYCLES_UNTIL_SLEEP;
  triggerWakeUpSound = true;
}

/* SOUND */

/*
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM
  by: Dipto Pratyaksa
  last updated: 31/3/13
*/
#define melodyPin 8

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

int song = 0;

void sing(int s){      
   // iterate over the notes of the melody:
   song = s;
   if(song==2){
     Serial.println(" 'Underworld Theme'");
     int size = sizeof(underworld_melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/underworld_tempo[thisNote];

       buzz(melodyPin, underworld_melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);

    }

   }else{

     Serial.println(" 'Mario Theme'");
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(melodyPin, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);
    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(green_led,HIGH);
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(green_led,LOW);

}

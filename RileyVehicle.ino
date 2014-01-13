/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int green_led = 13;
const int red_led = 12;

int blink_delay = 1000;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(buttonPin, INPUT);
  // initialize the digital pin as an output.
  pinMode(green_led, OUTPUT);     
  pinMode(red_led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {     
    // turn LED on:    
    blink_delay = 200;
  } 
  else {
    // turn LED off:
    blink_delay = 1000;
  }
  
  digitalWrite(green_led, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(red_led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(blink_delay);               // wait for a second
  digitalWrite(green_led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(red_led, HIGH);    // turn the LED off by making the voltage LOW
  delay(blink_delay);               // wait for a second
}

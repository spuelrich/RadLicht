//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 4;

#include "radlichttext.h";

volatile unsigned long last_time;
volatile unsigned long time;
volatile byte step;
//byte steps;
volatile unsigned long millis_per_step;
volatile unsigned int period_millis;
volatile unsigned int triggers;
void trigger () {

  last_time = time;
  time = millis();
  if (last_time == 0)
    return;

  period_millis = time - last_time;

  if (period_millis < 100) {
    time = last_time;
    return;
  }

  step = 0;
  millis_per_step = period_millis / steps;

  triggers++;
}



void setup() {
  triggers = 0;
  time = last_time = 0;
  attachInterrupt(0, trigger, CHANGE); // pin 2
  pinMode(13, OUTPUT);


  // DEBUG
  //millis_per_step = 10;
  //time = last_time = 1;

  //Serial.begin(9600);
  //Serial.println("hello");

  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}



void loop() {
  if (time == 0) return;
  if (last_time == 0) return;


  //count up routine
  /*
    for (int j = 0; j < 256; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(500);
    }
  */
  /*
    theval++;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, theval);
    digitalWrite(latchPin, HIGH);
    delay(50);
  */
  //Serial.println(millis_per_step);
  //Serial.println(radlichttext[step]);
  if (step >= steps) {
    step = 0;
    //Serial.println(period_millis);
  }

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, radlichttext[step]);
  //shiftOut(dataPin, clockPin, LSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);


  //analogWrite(11, i*5);
  //Serial.println(triggers);
  digitalWrite(13, digitalRead(13) ^ 1);
  delay(millis_per_step);
  step++;

}

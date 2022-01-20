/*
  Code by Rory Aartsen - Jan 2022
*/

// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Factory Image
//
// PCB v1.0
#include <Wire.h>
#include "Timers.h"
#define BOARD_VER 6
#include "programmable_air.h"
#include <Adafruit_NeoPixel.h>
#include "EEPROMAnything.h"
Adafruit_NeoPixel paPixels(3, 12, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

int state = UN_KNOWN;
int prevInput = 0;
boolean isLoopFinished = true;

#define MOTORS_ON 6
#define MOTORS_OFF 7

int calibratedPressure = 0;

void setup() {
  initializePins();
  pinMode(LED_BUILTIN, OUTPUT);
  pixels.begin();
  pixels.show();
  paPixels.begin();
  paPixels.show();
  Wire.begin();
  Serial.begin(9600);

}

void loop() {
  int pressure = readPressure();
  //delayWhileReadingPressure(200);
  int currentInput = serialEvent();

  if (currentInput != 0 && !isLoopFinished) {
    // If currrentInput != 0, the loop should run once (0 means stop)
    // And the loop is not finished yet, the code can run

    doBalloons();
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {

      isLoopFinished = true;
    }
  }
  // if pumping is done and no button is pressed, vent
  else if (isLoopFinished = true) {
    switchOffPumps();
    vent();
    state = VENTING;
  }
  Serial.println(pressure);
}

void doBalloons() {
  //if statement to make sure balloon doesn't blow up too much, but still blow up quickly
  if (readPressure() < 570) {
    // switch on pumps to 100% power
    switchOnPump(2, 100); // This last number is pump force 0-100%
    switchOffPump(1);
    blow();
    state = BLOWING;
    Serial.println("pressure lower than 550");
    readPressure();
  }

  else if (readPressure() > 569 && state == BLOWING) {
    // switch on pumps to 30% power
    switchOnPump(2, 35); // This last number is pump force 0-100%
    switchOffPump(1);
    blow();
    state = BLOWING;
    Serial.println("pressure higher than 550");
    readPressure();
  }
}


void error() {
  Serial.println("ERROR");
  for (int i = 0; i < 3; i++) {
    paPixels.setPixelColor(i, paPixels.Color(100, 0, 0));
  }
  paPixels.show();
  switchOffPumps();
  closeAllValves();
  while (1);
}

//void servoControl() {
//  unsigned long currentMillis = millis();
//
//  if (currentMillis - previousMillis >= interval) {
//    // save the last time you blinked the LED
//    previousMillis = currentMillis;
//    //    x = !x;
//    Serial.print("x = ");
//    Serial.println(x);
//
//    Wire.beginTransmission(9); // transmit to device #9
//    Wire.write(x);              // sends x
//    Wire.endTransmission();    // stop transmitting
//  }
//}

float serialEvent() {
  int input = Serial.read();
  if (input > 0) {
    isLoopFinished = false;
    previousMillis = millis();
  }
  switch (input) {
    case 0:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      isLoopFinished = true;
      break;
    case 1:
      digitalWrite(LED_BUILTIN, HIGH);
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
    case 2:
      digitalWrite(LED_BUILTIN, LOW);
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
    case 3:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
    case 4:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
    case 5:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
    case 6:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
    case 7:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      isLoopFinished = false;
      break;
    case 8:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
    case 9:
      Wire.beginTransmission(9); // transmit to device #9
      Wire.write(input);              // sends input
      Wire.endTransmission();    // stop transmitting
      break;
  }
  return input;
}

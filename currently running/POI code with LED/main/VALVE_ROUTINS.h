// Helper file that contains all routins for valves:
// initial setup, turning off/on and updating 
#include "Arduino.h"
#ifndef VALVE_ROUTINS_H
#define VALVE_ROUTINS_H
#include "CONSTANTS.h"

// ROUTINS
// switch off all valves
//-----------------------------------------------------------------
void off_all_valves() {
  digitalWrite(OE_Pin, HIGH);
  digitalWrite(dataPin, LOW);
  for (int j = 0; j < numValves; j++) {
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
  digitalWrite(OE_Pin, LOW);
}
//-----------------------------------------------------------------

// switch on all valves
//-----------------------------------------------------------------
void on_all_valves() {
  digitalWrite(OE_Pin, HIGH);
  digitalWrite(dataPin, HIGH);
  for (int j = 0; j < numValves; j++) {
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
  digitalWrite(OE_Pin, LOW);
}
//-----------------------------------------------------------------

// reverse 64-bit bool array 
//-----------------------------------------------------------------------------
void reverseArray(bool originalArray[64], bool reversedArray[64], int length) {
    for (int i = 0; i < length; i++) {
      reversedArray[i] = originalArray[length - 1 - i];
    }
}
//-----------------------------------------------------------------------------

// update valves
//-----------------------------------------------------------------
void update_valves(bool rowBuffer[]) {

  digitalWrite(OE_Pin, HIGH);
  for (int row = 0; row < numRows; row++) {
    for (int i = 0; i < valvesInRow; i++) {
      digitalWrite(dataPin, rowBuffer[i]);
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
    };
  };
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
  digitalWrite(OE_Pin, LOW);
}
//-----------------------------------------------------------------

// setup for valves - called in the setup part
//-----------------------------------------------------------------
void valveSetup() {
  pinMode(OE_Pin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // reset all valves
  digitalWrite(OE_Pin, HIGH);
  delay(100);
  digitalWrite(OE_Pin, LOW);

  delay(100);
  digitalWrite(ledPin, HIGH);
  on_all_valves();
  delay(1000);
  off_all_valves();
  digitalWrite(ledPin, LOW);
  delay(1000);
}
//-----------------------------------------------------------------
#endif /* VALVE_ROUTINS_H */
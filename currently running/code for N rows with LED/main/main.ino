// 28.12.23 - Illia Fortus, illia.fortus@mail.huji.ac.il
// simple arduino code for N rows  - different shapes
// THIS IS THE CURRENTLY RUNNING CODE - 28.12.23

#include <Arduino.h>
#include <string.h>
#include <SPI.h>
#include "CONSTANTS.h"  // include constants file

// SETUP
void setup() {
  //define pinmode
  pinMode(OE_Pin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // reset all valves enable pin
  digitalWrite(OE_Pin, HIGH);
  delay(10);
  digitalWrite(OE_Pin, LOW);

  off_all_valves();
  delay(10);
  // turn on all valves for 1 sec and then close
  digitalWrite(ledPin, HIGH);
  on_all_valves();
  delay(DELAYSHAPES);
  off_all_valves();
  digitalWrite(ledPin, LOW);
  delay(DELAYSHAPES);
}

// LOOP
void loop() {
  off_all_valves();  // reset all
  delay(100);        // delay of 100 ms

  draw_rows();
  off_all_valves();
  delay(DELAYSHAPES);

  draw_cross();
  off_all_valves();
  delay(DELAYSHAPES);

  draw_wave();
  off_all_valves();

  delay(10000);  // delay of 10 seconds
}

// switch off all valves
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

// switch on all valves
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

// write frames of 16
void write_frame(uint16_t frame_data, bool send, bool dir) {
  byte msb = highByte(frame_data);  // Extract the most significant byte (8 bits)
  shiftOut(dataPin, clockPin, MSBFIRST, msb);

  byte lsb = lowByte(frame_data);  // Extract the least significant byte (8 bits)
  shiftOut(dataPin, clockPin, MSBFIRST, lsb);

  if (dir) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, msb);
    shiftOut(dataPin, clockPin, MSBFIRST, lsb);

    if (send)
      digitalWrite(latchPin, HIGH);
  } else {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, lsb);
    shiftOut(dataPin, clockPin, LSBFIRST, msb);

    if (send)
      digitalWrite(latchPin, HIGH);
  }
}

// function to reverse bit order of uint_16t
//--------------------------------------------------------------------------
int16_t reverseValue(uint16_t val) {
  uint16_t reversedValue = 0;
  for (int i = 0; i < 16; i++) {
    if (val & (1 << i)) {
      reversedValue |= (1 << (15 - i));
    }
  }
  int row_reversed = static_cast<int>(reversedValue);  
  return row_reversed;
}
//--------------------------------------------------------------------------

// METHODS
void draw_rows() {
  draw_pattern(numElementsRows, rows_pattern);
}

void draw_cross() {
  draw_pattern(numElementsCross, cross_pattern);
}

void draw_wave() {
  draw_pattern(numElementsWave, wave_pattern);
}

// global function to write every pattern of 16, provide number of rows in the pattern (see CONSTANTS.h), and the pattern itself
//------------------------------------------------------------------------------------------------------------------------------
void draw_pattern(int numElements, uint16_t pattern[]) {
  for (byte rep = 0; rep < numRepetitions; rep++) {
    for (int row = 0; row < numElements; row++) {
      int row_reversed = reverseValue(pattern[row]);
      for (byte i = 0; i < numRows; i++) {
        if (i % 2 == 0) {  // if row is even
          write_frame(pattern[row], 0, 1);
        } else {  // if row is odd
          write_frame(row_reversed, 0, 1);
        }
      }
      // this is for the last row
      if (numRows % 2 == 0) {
        write_frame(row_reversed, 1, 1);
      } else {
        write_frame(pattern[row], 1, 1);
      }

      // now change LEDs - change the value for the desired delay from the start of the pattern
      if (row == 2) {
        digitalWrite(ledPin, HIGH);  // LED on
      }
      if (row == numElementsCross - 2) {
        digitalWrite(ledPin, LOW);  // LED off
      }
      delay(DELAYROWS);
    }
    off_all_valves();
    delay(DELAYREPS);
  }
}
//------------------------------------------------------------------------------------------------------------------------------
// end
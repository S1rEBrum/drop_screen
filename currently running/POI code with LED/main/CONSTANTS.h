// Helper file with all the constants and global variables
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>
/*
  ==========Arduino Nano pinout=========
                        _______
                   TXD-|       |-Vin (to 3v3/card reader) 
                   RXD-|       |-Gnd (to GND) || (to driver board)
                   RST-|       |-RST
                   GND-|       |-+5V (to driver board)
                    D2-|       |-A7
            (to EN) D3-|       |-A6
        (to Strobe) D4-|       |-A5
           (to CLK) D5-|       |-A4
          (to Data) D6-|       |-A3
                    D7-|       |-A2
                    D8-|       |-A1
            (to CS) D9-|       |-A0
                   D10-|       |-Ref
         (to MOSI) D11-|       |-3.3V
         (to MISO) D12-|       |-D13 (to CLK/card reader)
                        --USB--

*/

// PIN DEFINITIONS
//-----------------------------------------------------------------
#define OE_Pin 3
////Pin connected to DS of 74HC595
#define dataPin 6
//Pin connected to SH_CP of 74HC595
#define clockPin 5
//Pin connected to ST_CP of 74HC595
#define latchPin 4
//data pin
#define connectionPort 9  // Arduino port for data
// LED pin
#define ledPin 7
// Arduino Nano pin connected to SD card reader module
const int chipSelect = connectionPort;
//-----------------------------------------------------------------

// MAKE CHANGES HERE
//-----------------------------------------------------------------
#define numRows 32                // change for the desired number or rows working
const int DELAYROWS = 27;         // change for the desired delay between rows of the same image (in ms)
const bool printToSerial = true;  // change if you want to print the images to the serial monitor
const int maxImageCount = 10;     // change for the desired amount of images that can be read from SD card
//-----------------------------------------------------------------

// constants
#define valvesInRow 64
#define cardsinRow 4
const int numCards = cardsinRow * numRows;
const int numValves = numCards * 16;

// struct for BMP header
struct BMPHeader {
  uint16_t signature;
  uint32_t fileSize;
  uint32_t imageDataOffset;
  uint32_t width;
  uint32_t height;
};

// standartized parameters for the header
const uint16_t bmpSignature = 0x4D42;

// maximal image dimensions - 256 by 256 (to prevent overflow)
const uint16_t maxImageWidth = 255;
const uint16_t maxImageHeight = 255;

// arrray that saves all the images` names to get them later
String imageNames[maxImageCount];
int imageCount = 0;

// row bufer variables
bool rowBuffer[64];
bool reversedRowBuffer[64];
int width = 0;
int height = 0;

#endif /* CONSTANTS_H */
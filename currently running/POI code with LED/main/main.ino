/*
  28/12/23 - Illia Fortus, illia.fortus@mail.huji.ac.il

  Drop screen code - given images from microSD card turns them into rows of 64 bits 
  that consist of 0 and 1, then the rows are displayed using rows of valves. 

  IMPORTANT - change the version of SD.h library to 1.2.0. in Library Manager 
  for the code to work - later versions have bugs in some of the methods (seek(), etc)
*/
#include <SPI.h>
#include <SD.h>
#include "CONSTANTS.h"
#include "VALVE_ROUTINS.h"
#include "SD_ROUTINS.h"

// SETUP
void setup() {
  // start valve setup
  valveSetup();  // see VALVE_ROUTINS.h to check the function parameters

  // start SD card routins
  sd_routins();  // see SD_ROUTINS.h to check the function parameters
}

// LOOP
void loop() {
  // go over each image with steps to check validity
  for (int i = 0; i < imageCount; i++) {
    if (printToSerial) {
      Serial.print("Image filename: ");
      Serial.print(imageNames[i]);  // print the name of the file
      Serial.println("");
    };

    // open the file
    // there is a problem with some functions in the SD.h library, so to read the file
    // do not use FILE_READ flag and use O_READ | O_WRITE | O_CREAT
    File bmpFile = SD.open(imageNames[i], O_READ | O_WRITE | O_CREAT);
    if (!bmpFile) {
      if (printToSerial) {
        Serial.println("Failed to open BMP file");
      };
      continue;
    } else {
      if (printToSerial) {
        Serial.println("File read successfully.");
      };
    }

    // now check if the header of the file is valid
    BMPHeader bmpHeader;
    bmpFile.read((uint8_t*)&bmpHeader, sizeof(BMPHeader));
    if (bmpHeader.signature != bmpSignature) {
      if (printToSerial) {
        Serial.println("Invalid BMP file header.");
        // FOR DEBUG - uncomment 3 following lines to see
        // Serial.print(bmpHeader.signature);
        // Serial.println(" ");
        // Serial.print(bmpSignature);
      };
      continue;
    } else {
      if (printToSerial) {
        Serial.println("Header read successfully.");
      };
    }

    // check the image dimensions
    bmpFile.seek(18);  // Move to the width position in the header
    width = bmpFile.read() + (bmpFile.read() << 8) + (bmpFile.read() << 16) + (bmpFile.read() << 24);
    height = bmpFile.read() + (bmpFile.read() << 8) + (bmpFile.read() << 16) + (bmpFile.read() << 24);
    // display the values of width and height - optional
    if (printToSerial) {
      Serial.print("Width: ");
      Serial.println(width);
      Serial.print("Height: ");
      Serial.println(height);
    };

    // check if image dimensions exceed the limit
    if (width > maxImageWidth || height > maxImageHeight) {
      if (printToSerial) {
        // FOR DEBUG - uncomment 4 following lines to see
        // Serial.print(bmpHeader.width);
        // Serial.println(" ");
        // Serial.print(bmpHeader.height);
        // Serial.println(" ");
        Serial.println("Image dimensions exceed the maximum supported dimensions");
      };
      continue;
    } else {
      if (printToSerial) {
        Serial.println("Image dimensions are correct.");
      };
    }

    // begin reading the file
    //Serial.println(" ");
    bmpFile.seek(bmpHeader.width);

    //Read and process the image row by row
    for (int y = 0; y < height; y++) {
      // Read the row byte by byte
      for (int x = 0; x < width; x++) {
        uint32_t pixelData;
        bmpFile.read(&pixelData, sizeof(pixelData));

        // Convert the pixel data to a boolean value
        rowBuffer[x] = (pixelData != 0);
        //delay(1);
      }
      if (printToSerial) {
        if (y % 2 == 0) {
          for (int x = 0; x < width; x++) {
            Serial.print(rowBuffer[x]);  // print the values
          }
          Serial.println();
        }
      }

      // reverse the rowBuffer variable
      reverseArray(rowBuffer, reversedRowBuffer, 64);

      if (y % 2 == 0) {
        update_valves(rowBuffer);
      } else {
        update_valves(reversedRowBuffer);
      };
      delay(DELAYROWS);  // delay time between rows
      off_all_valves();


      if (y == 2) {
        digitalWrite(ledPin, HIGH);
      }
      if (y == height - 2) {
        digitalWrite(ledPin, LOW);
      }
    };

    // close the file
    if (printToSerial) {
      Serial.println(" ");
      Serial.println("Closing the file...");
      bmpFile.close();
    };

    off_all_valves();
    delay(1000);

    if (printToSerial) {
      Serial.println("-------------------------------------------------");
      Serial.println(" ");
    };

    delay(2000);
  }
  if (printToSerial) {
    Serial.println(" ");
    Serial.println("All images processed.");
    Serial.println(" ");
  };

  off_all_valves();

  delay(5000);
}

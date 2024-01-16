// Helper file that contains all the routins for the SD card initialization

#ifndef SD_ROUTINS_H
#define SD_ROUTINS_H

#include <SD.h>
#include <SPI.h>

// set up variables using the SD utility library functions:
Sd2Card card;
File root;

void sd_routins() {
  Serial.begin(9600);

  // info messages
  if (printToSerial) {
    Serial.print("\nInitializing SD card...");
  };

  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    if (printToSerial) {
      Serial.println("Initialization failed.");
    };
    return;
  } else {
    if (printToSerial) {
      Serial.println("Wiring is correct and a card is present.");
    };
  }

  // now start with reading the file
  //Serial.println(" ");
  SD.begin(connectionPort);  // begin at port 9

  // open the home directory of the card
  root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) {
      break;  // stop going over the files when there is no more
    }

    // because our images are not in the directory - we can pass all the directories
    // useful to pass the partition of the SD card
    if (entry.isDirectory()) {
      continue;
    }

    // go over the files
    String fileName = entry.name();
    if (fileName.endsWith(".BMP")) {
      // Store the filename in the array
      imageNames[imageCount] = fileName;
      imageCount++;
    }
    entry.close();
  }
}

#endif /* SD_ROUTINS_H */
#ifndef DISPLAY_ROUTINS_H
#define DISPLAY_ROUTINS_H
#include "CONST_N_GLOBAL.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c //initialize with the I2C Oled's addr 0x3C. Typically aliexpress, 0x3D Adafrout

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Start_Display(){
  display.begin(i2c_Address, true); // Address 0x3C default
  //display.setContrast (0); // dim display
  display.clearDisplay();
  display.display();

  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F(__FILE__ " " __DATE__ " " __TIME__));
  display.display();
  delay(5000);
  display.clearDisplay();
//  delay(500);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("START");
  display.display();
  delay(500);
  display.clearDisplay();
  display.display();
}

//-------------------
void Display_Pulse_N_Space_Time(){
  display.clearDisplay();
//  display.display();
  display.setCursor(0, 0);
  display.print("Pt=");
  display.print(pulse_time);
  display.println("ms");
  display.print("St=");
  display.print(space_time);
  display.println("ms");
  display.display();
}
//---------------------------



#endif /* DISPLAY_ROUTINS_H */

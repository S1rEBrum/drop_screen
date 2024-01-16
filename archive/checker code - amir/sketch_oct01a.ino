/*
 * Aug 2023 test code for 16 valve Amir BS. 
 * for used with 2 drivers pcb Drop Screen OCT 2022 Drives  (blue pcb mark water drop screen NOV 2022
 * not used EN^(pulldn by mistake res on board 
  *sequential, no space, (valve 1 to 16) pulses and then one space time befour next pulses train. 
 * Pulses start/continue according to switch/push button pressed
 * 2 50K pot (connect to A0, A1) used to set pulse time and space after cycle time 
 * Set board to Arduino Nano, 328 old boatloader 
 * for IO map / PINOUT see CONST_N_GLOBAL
 * 
 */
#include "CONST_N_GLOBAL.h"
//#include "Display_Routins.h"
//#include <Arduino.h>
//#include <string.h>
//#include <SPI.h>

//-----------------------
//Routins 
// ---------------switch off all valves 
void off_all_valves(int Num_of_valves){
  digitalWrite(SR_En_Pin, HIGH);   // make sure all output HI Z
  digitalWrite(SR_Data_Pin, LOW);   
  for (int j = 0; j < Num_of_valves; j++) {
    digitalWrite(SR_Clk_Pin, HIGH);   
    digitalWrite(SR_Clk_Pin, LOW);
  }
  digitalWrite(SR_St_Pin, HIGH);   
  digitalWrite(SR_St_Pin, LOW);   
  digitalWrite(SR_En_Pin, LOW);   // active all outputs
}
// ---------------switch on all valves -------------------------------------------------------------------
void on_all_valves(int Num_of_valves){
  digitalWrite(SR_En_Pin, HIGH);   // make sure all output HI Z
  digitalWrite(SR_Data_Pin, HIGH);   
  for (int j = 0; j < Num_of_valves; j++) {
    digitalWrite(SR_Clk_Pin, HIGH);   
    digitalWrite(SR_Clk_Pin, LOW);
  }
  digitalWrite(SR_Data_Pin, LOW);// finaly set data to low 
  digitalWrite(SR_St_Pin, HIGH);   
  digitalWrite(SR_St_Pin, LOW);   
  digitalWrite(SR_En_Pin, LOW);   // active all outputs
}
//----cycle single pulse on each valve - make sure reset(off)all valves befour---------------------------------------------
void cycle_all_valves(int Num_of_valves, uint32_t Pulse_time){
  digitalWrite(SR_En_Pin, HIGH);   // make sure all output HI Z
  digitalWrite(SR_Data_Pin, HIGH);// set first valve on    
  digitalWrite(SR_Clk_Pin, HIGH); // clock in the data   
  digitalWrite(SR_Clk_Pin, LOW); // 
  digitalWrite(SR_Data_Pin, LOW);// set data to low 
  digitalWrite(SR_St_Pin, HIGH); // strobe array to output buffer   
  digitalWrite(SR_St_Pin, LOW); //  
  //  Serial.print ("* ");
  digitalWrite(SR_En_Pin, LOW);   // active all outputs
  delay(Pulse_time); // output is active for this time 
  for (int j = 1; j <= Num_of_valves; j++) { // now cycle the pulse till its go out !!! 
    digitalWrite(SR_Clk_Pin, HIGH); // clock  the data   
    digitalWrite(SR_Clk_Pin, LOW); // 
    digitalWrite(SR_St_Pin, HIGH); // strob array to output buffer   
    digitalWrite(SR_St_Pin, LOW); //      
  //    Serial.print ("* ");
    delay(Pulse_time); // output is active for this time 
  } // done all cycle   
   // Serial.println (" done all valves ");
}  
//------------------------------------

void setup() {
  pinMode(SR_St_Pin, OUTPUT);
  pinMode(SR_Clk_Pin, OUTPUT);
  pinMode(SR_Data_Pin, OUTPUT);
  pinMode(SR_En_Pin, OUTPUT);
  digitalWrite(SR_En_Pin, HIGH);   // make sure all output HI Z  
  off_all_valves(Number_Of_Valves);
  //pimode changed from INPUT_PULLUP
  pinMode(PB_IN, OUTPUT);  
  //Start_Display();
  //Serial.begin(BAUDRATE);
  //delay (500);// wait to make sure serial begin
  //Serial.println(F(__FILE__ " " __DATE__ " " __TIME__));
  //Serial.println("START");  
  
}

void loop() {
  //pulse_time = analogRead(Pot_Pulse_time_in);
  //pulse_time = 10*(map(pulse_time, 0, 1023, Min_Pulse_time, Max_Pulse_time)/10);// round/trunc (integer) last digit - cation with math operation order 
  //space_time = analogRead(Pot_Space_time_in);
  //space_time = 100*(map(space_time, 0, 1023, Min_Space_time, Max_Space_time)/100);//round/trunc (integer) last 2 digits - cation with math operation order 
  pulse_time = 100;
  space_time = 100 ;
  //Display_Pulse_N_Space_Time();
  //byte in_pb = digitalRead (PB_IN);
  //if (in_pb == LOW) {// pb prease 
//    Serial.println("Start pulse cycle");
//    display.println("Now Pulse");
//    display.display();
    //off_all_valves(Number_Of_Valves);
    cycle_all_valves(Number_Of_Valves, pulse_time);
    delay(space_time);
//    Serial.println("done pulse cycle");
//    Serial.println("=============================================================");
//    Display_Pulse_N_Space_Time();
//    display.println("Waiting");
//    display.display();
    //delay (space_time);
    //}
}

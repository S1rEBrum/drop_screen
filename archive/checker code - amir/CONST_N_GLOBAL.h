
#ifndef CONST_N_GLOBAL_H
#define CONST_N_GLOBAL_H
#include <Arduino.h>
//#define BAUDRATE    (115200)    //
/*
 *==========Arduino Nano pinout====== 
 *                      _______
 *                 TXD-|       |-Vin 
 *                 RXD-|       |-Gnd to driver board  
 *                 RST-|       |-RST
 *                 GND-|       |-+5V To driver board  
 *       Switch/PB, D2-|       |-A7
 *         To EN^,  D3-|       |-A6
 *       To Strobe, D4-|       |-A5 ,SCL (to Display) 
 *          To Clk, D5-|       |-A4 ,SDA (to Display) 
 *         To Data, D6-|       |-A3
 *                  D7-|       |-A2
 *                  D8-|       |-A1, 50K pot 2 
 *                  D9-|       |-A0, 50K pot 1
 *                 D10-|       |-Ref
 *                 D11-|       |-3.3V   
 *                 D12-|       |-D13
 *                      --USB--        
 * 
 * 
 */
 
 // const and global
const int Number_Of_Valves =16; // 
const uint32_t Max_Pulse_time = 1000 ; // ms
const uint32_t Min_Pulse_time = 10 ; // ms 
const uint32_t Max_Space_time = 10000 ; // ms
const uint32_t Min_Space_time = 100 ; // ms 

uint32_t pulse_time = Min_Pulse_time;
uint32_t space_time = Min_Space_time;

// IO MAPPING
#define SR_St_Pin (4) // 74HC565 shift register strob pin (12) - active high (low/hig/low pulse shift Sr vector to outputs)make sure set low during "push"data in
#define SR_Clk_Pin (5)// 74HC565 shift clock pin (11) - active high (low/hig/low pulse shift data in) make sure initaly set to low 
#define SR_Data_Pin (6)// 74HC565 Data in pin (14)  
#define SR_En_Pin (3)// 74HC565 out put enable pin (13) - active low 

#define PB_IN (2)// switch/pushbutton input ative low - puled up 

#define Pot_Pulse_time_in (A0) // input from potentiometer to set pulse time 
#define Pot_Space_time_in (A1) // input from potentiometer to set space time 

#define INTERNAL_LED (13)

#define BAUDRATE    (115200)    //





bool Use_Serial = true ; //  print to serial (set monitor to same boudrate)
bool Use_Display = true ; // display on SH106 (make sure Display I2C address and DATA nad Clock conection)  




#endif /* CONSTANTS_H */

/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Hault_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#define DEBUG // debug flag
// for BlueTooth
#include<SoftwareSerial.h>

// for RFID
#include <SPI.h>
#include <MFRC522.h>

/*===========================define pin & create module object================================*/
// BlueTooth
#define Rx 10
#define Tx 11
SoftwareSerial BT_test(Rx,Tx);   // TX,RX on bluetooth module, 請按照自己車上的接線寫入腳位
// L298N, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
#define MotorR_I1     4 //定義 I1 接腳（右）往前
#define MotorR_I2     2 //定義 I2 接腳（右）往後
#define MotorL_I3     3 //定義 I3 接腳（左）往前
#define MotorL_I4     7 //定義 I4 接腳（左）往後
#define MotorL_PWML    6 //定義 ENA (PWM調速) 接腳
#define MotorR_PWMR    5 //定義 ENB (PWM調速) 接腳
// 循線模組, 請按照自己車上的接線寫入腳位
#define L1   A0  // Define Left Most Sensor Pin
#define L2   A1  // Define Left Middle Sensor Pin
#define L3   A2  // Define Middle Left Sensor Pin
#define R3   A3  // Define Middle Right Sensor Pin
#define R2   A4  // Define Right Middle Sensor Pin
#define R1   A5  // Define Right Most Sensor Pin
// RFID, 請按照自己車上的接線寫入腳位 //NOT YET
#define RST_PIN      100        // 讀卡機的重置腳位
#define SS_PIN       101      // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
/*===========================define pin & create module object===========================*/

/*===========================declare function prototypes===========================*/
// search graph
void Search_Mode();
// wait for command
void Hault_Mode();
void SetState();
/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
// Import header files
#include "RFID.h"
#include "track.h"
#include "bluetooth.h"
#include "node.h"
BT_CMD _cmd = NOTHING;
void setup()
{
   //bluetooth initialization
   BT_test.begin(9600);
   //Serial window
   Serial.begin(9600);
   //RFID initial
   SPI.begin();
   mfrc522.PCD_Init();
   //L298N pin
   pinMode(MotorR_I1,   OUTPUT);
   pinMode(MotorR_I2,   OUTPUT);
   pinMode(MotorL_I3,   OUTPUT);
   pinMode(MotorL_I4,   OUTPUT);
   pinMode(MotorL_PWML, OUTPUT);
   pinMode(MotorR_PWMR, OUTPUT);
   //tracking pin
   pinMode(L1, INPUT);
   pinMode(L2, INPUT);
   pinMode(L3, INPUT);
   pinMode(R3, INPUT);
   pinMode(R2, INPUT);
   pinMode(R1, INPUT); 
   
#ifdef DEBUG
  Serial.println("Start!");
#endif

}// setup


// initalize parameter
double vL = 80, vR = 80 ;
bool system_begin = 0 ;
// variables for 循線模組
int l1 = 0, l2 = 0, l3 = 0, r3 = 0, r2 = 0, r1 = 0 ;
// variable for motor power
int _Tp = 80 ;
// enum for car states, 不懂得可以自己google C++ enum
enum ControlState
{
   HAULT_STATE,
   SEARCH_STATE,
};
ControlState _state = HAULT_STATE;
// enum for bluetooth message, reference in bluetooth.h line 2


void loop()
{
  Serial.print("serial.avail:");
  Serial.println(BT_test.available());
   // search graph
   if(_state == SEARCH_STATE) Search_Mode();
   // wait for command
   else if(_state == HAULT_STATE){
    while(1){
      Serial.print("serial.avail:");
  Serial.println(BT_test.available());
      }};
   SetState();
}// loop

void SetState()
{
  // TODO:
  // 1. Get command from bluetooth
  // 2. Change state if need
  if( !(digitalRead(L1) || digitalRead(L2) || digitalRead(L3) || digitalRead(R3) || digitalRead(R2) || digitalRead(R1)) ){
    _state = HAULT_STATE ;
    char temp = 'e' ;
    send_msg(temp) ;
    //report through bluetooth
  } // meet dead end
  else if( digitalRead(L1) && digitalRead(L2) && digitalRead(L3) && digitalRead(R3) && digitalRead(R2) && digitalRead(R1) ){
    _state = HAULT_STATE ;
    char temp = 'n' ;
    send_msg(temp) ;
    //report through bluetooth
  } // meet node 
  else{
    _state = SEARCH_STATE ;
  }
  
}// SetState

void Hault_Mode()
{
  // TODO: let your car stay still
  MotorWriting( 0, 0) ;
  Serial.print(" hault_mode ");
  _cmd = NOTHING ;
  while(1){
    //Serial.print("bt has avail:");
    //Serial.println(BT_test.available());
    _cmd = ask_BT() ;
    //Serial.print("after ask: ") ;
    //Serial.println(_cmd) ;
    if( _cmd != NOTHING ) break ;
  }
  Serial.print(" read something ") ;
  if( _cmd == _left ) turn_left();
  else if( _cmd == _right ) turn_right();
  else if( _cmd == _around ) turn_around();
  else if( _cmd == _through ) go_through();

  
  
}// Hault_Mode

void Search_Mode()
{
  // TODO: let your car search graph(maze) according to bluetooth command from computer(python code)
  tracking(digitalRead(L1), digitalRead(L2), digitalRead(L3), digitalRead(R3), digitalRead(R2), digitalRead(R1));
  MotorWriting( vL, vR);
}
// Search_Mode
/*===========================define function===========================*/
Arduino:1.8.12 (Mac OS X), 開發板:"Arduino Uno"

loading libs from /Users/wang/Documents/Arduino/libraries: reading dir /Users/wang/Documents/Arduino/libraries: open /Users/wang/Documents/Arduino/libraries: operation not permitted

開發板 Arduino Uno 編譯錯誤。

This report would have more information with
"Show verbose output during compilation"
option enabled in File -> Preferences.

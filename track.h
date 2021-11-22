/***************************************************************************/
// File			  [track.h]
// Author		  [Erik Kuo]
// Synopsis		[Code used for tracking]
// Functions  [MotorWriting, tracking]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>

/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/

/*===========================import variable===========================*/
int extern _Tp;
double extern vL, vR ;
/*===========================import variable===========================*/

// Write the voltage to motor.
void MotorWriting(double vL, double vR) {
  // TODO: use L298N to control motor voltage & direction
  bool r = 0, l = 0 ;
  //suppose 1, 2 == r 
  //suppose 3, 4 == l
  if( vR < 0 ){
    r = 1 ;
    vR = -vR ; 
  }
  if( vL < 0 ){
    l = 1 ;
    vL = -vL ;
  }
  analogWrite(MotorR_PWMR, vR);
  analogWrite(MotorL_PWML, vL);
  //往前 右輪
  digitalWrite(MotorR_I1, !r);
  //往後 右輪
  digitalWrite(MotorR_I2, r);
  //往前 左輪
  digitalWrite(MotorL_I3, !l);
  //往後 左輪
  digitalWrite(MotorL_I4, l);
}// MotorWriting

// P/PID control Tracking
void tracking(int l1,int l2,int l3,int r3,int r2,int r1){
  //TODO: complete your P/PID tracking code
  double left_on_line, right_on_line ; 
  l1 = digitalRead(L1);
  l2 = digitalRead(L2);
  l3 = digitalRead(L3);
  //0~2 == left
  r3 = digitalRead(R3);
  r2 = digitalRead(R2);
  r1 = digitalRead(R1);
  //3~5 == right
  left_on_line = l1 * 200 + l2 * 80 + l3 * 0 ;
  right_on_line = r1 * 200 + r2 * 80 + r3 * 0 ;
  if( l1 + l2 + l3) left_on_line /= ( l1 + l2 + l3) ;
  if( r1 + r2 + r3) right_on_line /= ( r1 + r2 + r3) ;
  //大轉彎 減速
  int turn_slow = 0 ;
  if( l1 || r1 ) turn_slow = 40 ; 

  vL = _Tp ;
  vR = _Tp ;
  vL += ( right_on_line / 2 - turn_slow );
  vL -= ( left_on_line / 2 - turn_slow );
  vR += ( left_on_line / 2 - turn_slow );
  vR -= ( right_on_line / 2 - turn_slow );

  
 }// tracking

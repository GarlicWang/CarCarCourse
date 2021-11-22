/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on yout own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>

/*===========================import variable===========================*/
int extern l1, l2, l3, r3, r2, r1 ;
int extern _Tp;
double extern vL, vR ;
/*===========================import variable===========================*/

// TODO: add some function to control your car when encounter a node
// here are something you can try: left_turn, right_turn... etc.
void turn_left(){
    vL = -60 ;
    vR = 80 ;
    MotorWriting( vL, vR ) ;
    delay( 800 ) ;
}
void turn_right(){
    vL = 80 ;
    vR = -60 ;
    MotorWriting( vL, vR ) ;
    delay( 800 ) ;
}
void turn_around(){
    vL = 100 ;
    vR = -80 ;
    MotorWriting( vL, vR ) ;
    delay( 800 ) ;
}
void go_through(){
    vL = 80 ;
    vR = 80 ;
    MotorWriting( vL, vR ) ;
    delay( 1000 ) ;
}

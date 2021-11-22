/***************************************************************************/
// File			  [bluetooth.h]
// Author		  [Erik Kuo]
// Synopsis		[Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 2*/

#include<SoftwareSerial.h>
enum BT_CMD {
  NOTHING,
  _left,
  _right,
  _around,
  _through,
  _begin,
  // TODO: add your own command type here
};

BT_CMD ask_BT(){
    BT_CMD message = NOTHING;
    char cmd;
    Serial.print("Bt is avail:");
      Serial.println(BT_test.available());
      cmd = BT_test.read();
      Serial.print("bt.read is:");
    Serial.println(cmd);
     
    if(BT_test.available()){  //whether got data
      // TODO:
      // 1. get cmd from SoftwareSerial object: BT
      // 2. link bluetooth message to your own command type
      //Serial.print("Bt is avail:");
      //Serial.println(BT.available());
      Serial.print("bt read is:");
      cmd = BT_test.read();
      Serial.println(BT_test.read());
      if(cmd == 'a')message = _left;
      else if(cmd == 'd')message = _right;
      else if(cmd == 's')message = _around;
      else if(cmd == 'w')message = _through;
      else if(cmd == 'B')message = _begin;

    }
    //Serial.print("cmd : ");
    //Serial.println(cmd);
    return message;
}// ask_BT

// send msg back through SoftwareSerial object: BT
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg)
{
     // TODO:
     if(msg == 'n' )BT_test.write('n');//node
     if(msg == 'e' )BT_test.write('e');//endnode
     //if(msg==r)BT.write('r');//on the road
}// send_msg

// send UID back through SoftwareSerial object: BT
void send_byte(byte *id, byte& idSize) {
  for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
    BT_test.write(id[i]);
  }
  #ifdef DEBUG
  Serial.print("Sent id: ");
  for (byte i = 0; i < idSize; i++) {  // Show UID consequently.
    Serial.print(id[i], HEX);
  }
  Serial.println();
  #endif
}// send_byte

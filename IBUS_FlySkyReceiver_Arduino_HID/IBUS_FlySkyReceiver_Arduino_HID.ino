/*
   FlySky IBUS Arduino receiver with HID output
   Channels:
   #0 - Roll
   #1 - Pitch
   #2 - Throttle
   #3 - Yaw
   #4 - Aux 1
   #5 - Aux 2
*/

#include "FlySkyIBus.h"
#include <SoftwareSerial.h>
#include <Joystick.h>

volatile int values[6] = {0, 0, 0, 0, 0, 0};

#define rxPin 10
#define txPin 11
SoftwareSerial mySerial(rxPin, txPin);

void setup()
{
  Joystick.begin(true);
  //Serial.begin(115200); // for debuging
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(115200);
  IBus.begin(mySerial);
}

void loop()
{
  IBus.loop();
  // Read state of all axis
  for (int i = 0; i < 6; i++) {
    values[i] = IBus.readChannel(i);
    //Serial.print(values[i]);
    //Serial.print(" ");
  }
  //Serial.print(" | ");
  //Serial.println(" ");
  //Serial.println("-----------");

  // Map stick positions to Joystick values
  values[0] = map(values[0], 1000, 2000, -127, 127); //Roll
  values[1] = map(values[1], 1000, 2000, -127, 127); //Pitch
  values[2] = map(values[2], 1000, 2000, 0, 255);    //Throttle
  values[3] = map(values[3], 1000, 2000, 0, 255);    //Yaw
  values[4] = map(values[4], 1000, 2000, 0, 1);      //Aux 1
  values[5] = map(values[5], 1000, 2000, 0, 1);      //Aux 2

  // Assign Joystick values to joystick object
  Joystick.setXAxis(byte(values[0]));
  Joystick.setYAxis(byte(values[1]));
  Joystick.setThrottle(byte(values[2]));
  Joystick.setRudder(byte(values[3]));
  Joystick.setButton(0, values[4]);
  Joystick.setButton(1, values[5]);

  // Loop through new values, debugging purposes
  /*
  for (int i = 0; i < 6; i++) {
    Serial.print(values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  */
}

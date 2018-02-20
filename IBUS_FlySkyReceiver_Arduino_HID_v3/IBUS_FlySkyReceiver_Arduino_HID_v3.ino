/*
   FlySky IBUS Arduino receiver with HID output
   v2 upgraded to 8 channels
   Channels:
   #0 - Roll
   #1 - Pitch
   #2 - Throttle
   #3 - Yaw
   #4 - Aux 1
   #5 - Aux 2
   #6 - Aux 3
   #7 - Aux 4
*/

#include "FlySkyIBus.h"
#include <SoftwareSerial.h>
#include <Joystick.h>

volatile int values[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#define rxPin 10
#define txPin 11
SoftwareSerial mySerial(rxPin, txPin);

// Joystick setup details
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 32, 0,
  true, true, false, false, false, false,
  true, true, false, false, false);


void setup()
{
  Joystick.begin(true);
  //Serial.begin(115200); // for debuging
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(115200);
  IBus.begin(mySerial);
/*
  Joystick.setXAxisRange(1000, 2000);
  Joystick.setYAxisRange(1000, 2000);
  Joystick.setThrottleRange(1000, 2000);
  Joystick.setRudderRange(1000, 2000);
  */
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setThrottleRange(0, 1023);
  Joystick.setRudderRange(0, 1023);
}

void loop()
{
  IBus.loop();
  // Read state of all axis
  for (int i = 0; i < 8; i++) {
    values[i] = IBus.readChannel(i);
    //Serial.print(values[i]);
    //Serial.print(" ");
  }
  //Serial.print(" | ");
  //Serial.println(" ");
  //Serial.println("-----------");

  // Map switch positions to JoystickButton states
  values[0] = map(values[0], 1000, 2000, 0, 1023);      //Aux 1
  values[1] = map(values[1], 1000, 2000, 0, 1023);      //Aux 2
  values[2] = map(values[2], 1000, 2000, 0, 1023);      //Aux 3
  values[3] = map(values[3], 1000, 2000, 0, 1023);      //Aux 4
  values[4] = map(values[4], 1000, 2000, 0, 1);      //Aux 1
  values[5] = map(values[5], 1000, 2000, 0, 1);      //Aux 2
  values[6] = map(values[6], 1000, 1500, 0, 1);      //Aux 3
  values[7] = map(values[7], 1000, 2000, 0, 1);      //Aux 4

  // Assign Joystick values to joystick object
  Joystick.setXAxis(values[0]);
  Joystick.setYAxis(values[1]);
  Joystick.setThrottle(values[2]);
  Joystick.setRudder(values[3]);
  Joystick.setButton(0, values[4]);
  Joystick.setButton(1, values[5]);
  Joystick.setButton(2, values[6]);
  Joystick.setButton(3, values[7]);

  // Loop through new values, debugging purposes
/*
  for (int i = 0; i < 8; i++) {
    Serial.print(values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
*/
}

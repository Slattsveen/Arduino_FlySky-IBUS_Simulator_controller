# Arduino_FlySky-IBUS_Simulator_controller
This project uses an Arduino Micro to decode and emulate a joystick device for use with quadcopter simulators. 
Builds on the following libraries, they are needed for my sketch to work:

FlySky Ibus decoder by aanon4: https://github.com/aanon4/FlySkyIBus

Joystick library by Matthew Heironimus - http://mheironimus.blogspot.no/2016/11/arduino-joystick-library-version-20.html - https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0


Components:
- 1 Arduino micro (should work directly on a Leonardo as well, can probably be adapted to other models also)
- 1 FlySky IBUS receiver (tested with the FS-RX2A Pro https://www.banggood.com/2_4G-Compatible-FS-RX2A-Pro-Receiver-for-FS-I6-FS-I6X-FS-I6S-FS-TM8-FS-TM10-FS-I10-Transmitter-p-1145881.html?rmmds=myorder&cur_warehouse=CN)
- FlySky radio controller (I use the FS-i6)

Setting up:
I use SoftwareSerial to read the incoming ibus channel on pin 10.
IBUS - pin 10
Vcc - 5V
Gnd - Gnd


Disclaimer: I share this code with the community, I will not be developing it further unless I wish to change something for myself. Feel free to copy and modify as you wish.

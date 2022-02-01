/*
CSC 492
BIOMETRIC LOCK PROGRAM
By
Ryan Lemmon, Shane Riggar, Luke Tingley, and Andrew Yankovich
Emails:
LEM8289@calu.edu, RIG6382@calu.edu, TIN2093@calu.edu, YAN6326@calu.edu
This is the main code funciton for the Biometric Lock Senior Project
This document was initially created on 24-1-22.

TODO:
list what ports are going to what external parts. this should be known and common for every accessory.
GOOD LINKS:
https://docs.arduino.cc/learn/electronics/lcd-displays for LCD
https://arduinogetstarted.com/tutorials/arduino-keypad for keypad
https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library library for fingerprint sensor
https://www.arduino.cc/en/Reference/SD library included for SD card


THINGS TO KEEP IN MIND:
~comment literally everything
~leave no stone unturned. make this readable code (except when prototyping of course)
*/

//****INCLUDES****
//system master includes

//LCD includes
#include <LiquidCrystal.h>
//Keypad includes
#include <Keypad.h>
//fingerprint sensor includes
//this one's external and must be included. not sure how to yet tho.

//lock includes
//this might just be sending power to the lock to unlock and lock it... make functions for this.

//sd card slot includes
#include <SPI.h>
#include <SD.h>
//misc includes

//****CONSTANTS / PORT DEFINITIONS****
//LCD ports
//        reset   enable  d4       d5       d6       d7
const int rs = 4, en = 6, d4 = 10, d5 = 11, d6 = 12, d7 = 13; //make these different when we get the board... 

//****STRUCT DEFINITIONS****


//****GLOBAL VARIABLES / CLASSES****


LiquidCrystal lcd(rs,en,d4,d5,d6,d7)

//****FUNCTIONS AND DEFINITIONS****
void farts(int poop = 69)
{
  poop+=420;
  return poop;
}

/*
****FUNCTIONS TODO:****

****END FUNCTIONS TODO****
 */
//**************MAIN FUNCTIONS**************
//**INIT SETUP**
void setup() {
  // put your setup code here, to run once:

}

//**MAIN LOOP**
//highly possible we don't even use this since it will be "solid state"...
//see what exactly on a hardware level this code does(????)
//is there any benefit to using this other than our own stuff(??)
//specifically for the sleep mode
void loop() {
  // put your main code here, to run repeatedly:

}

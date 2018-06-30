#include <SoftwareSerial.h>
#include <TheThingsNetwork.h>
#include "keys.h"

const char *appEui = "70B3D57ED0010252";
const char *appKey = "4A6017C1BBCEAE8667976F7495DDADE7";
    
#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868
    
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

// software serial #1: RX = digital pin 10, TX = digital pin 11
SoftwareSerial portOne(10, 11);

bool waiting = false;

void setup() {
  
  loraSerial.begin(57600);
  debugSerial.begin(9600);
  
  portOne.begin(9600);
  // Initialize LED output pin
  pinMode(LED_BUILTIN, OUTPUT);
    
  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);
    
  debugSerial.println("-- STATUS");
  //ttn.showStatus();
  debugSerial.println("-- JOIN");
  //ttn.join(appEui, appKey);
  debugSerial.println("-- CALIBRATE ACCEL");
  calibrateAccel();
  // listen to software port
   delay(1000); // Give it time to send a response or you'll get nothing!  
  // while there is data coming in, read it
  // and send to the hardware serial port:
  
  portOne.listen();
}

int loopcount = 0;

void loop() {
 debugSerial.println("-- LOOP"+String(loopcount));
 loopcount++;
 delay(1000);
  if(!waiting || loopcount==50) {
    Serial.println("Querying devices...");
    waiting = true;
    portOne.write(13);
    loopcount = 0;
  }
  while (portOne.available() > 0) {
    byte data[1];
    data[0] = portOne.read();
    Serial.println("Received:"+ String(data[0]));
    loopcount = 0;
    // Send it off
    //ttn.sendBytes(data, sizeof(data));
    while(checkMotion()) delay(3000);
    while(!checkMotion()) delay(3000);
    waiting = false;
  }    
}

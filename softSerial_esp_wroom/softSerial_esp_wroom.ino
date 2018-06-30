/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <HardwareSerial.h>

HardwareSerial MySerial(1);
int scanTime = 30; //In seconds

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup() {
  Serial.begin(115200);
  MySerial.begin(9600, SERIAL_8N1, 25, 26);
  BLEDevice::init("");
  Serial.println("Initialized!");
}

void loop() {
  Serial.println("MySerial available is:" + String(MySerial.available()));
  while (MySerial.available() > 0) {
    uint32_t byteFromSerial = MySerial.read();
    Serial.println("received:" + String(byteFromSerial));
    if(byteFromSerial == 13) {
      uint32_t count = scanDevices();
      MySerial.write(count);
    }
  }
  // put your main code here, to run repeatedly:
  delay(2000);
}

int scanDevices() {
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->setActiveScan(false);
  return foundDevices.getCount();
}


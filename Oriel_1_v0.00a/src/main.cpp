#include <Arduino.h>
#include <OrielFirmware.h>

OrielFirmware deviceFirmware;

void setup() {
  Serial.begin(115200);
  deviceFirmware.beginFirmwareInitialization();
}

void loop() {
  
}
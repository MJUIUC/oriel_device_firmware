#include <Arduino.h>
#include <OrielFirmware.h>

OrielFirmware deviceFirmware;

void setup() {
  Serial.begin(115200);
  deviceFirmware.beginFirmwareInitialization();
}

void loop() {
  // Serial.printf("web server active: %s\n", deviceFirmware.internalWebServerActive? "Yes" : "No");
}
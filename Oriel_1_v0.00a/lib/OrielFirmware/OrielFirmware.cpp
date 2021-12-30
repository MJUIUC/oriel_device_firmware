#include <OrielFirmware.h>

void OrielFirmware::initDeviceFirmware() {
  Serial.begin(115200);
  this->displayController.initDisplay();
  delay(1500);
  this->displayController.clearDisplay();
  this->displayController.print("Initializing Device...\n");
  this->beginSDCard();
  this->beginWiFiConnection();
}

void OrielFirmware::beginSDCard(){
  this->displayController.print("SD Card: ");
  if(this->fileController.initSDCard()) {
    this->displayController.print("Found Card.\n");
    return;
  }
  this->displayController.print("Failed.\n");
}

void OrielFirmware::beginWiFiConnection(){
  this->displayController.print("WiFi: ");
  if (this->networkController.initWiFi(this->network_ssid, this->network_password)) {
    this->displayController.print("connection established.\n\n");
    this->displayController.print("@: ");
    this->displayController.print(this->network_ssid);
    this->displayController.printReturn();
    return;
  }
  this->displayController.print("Failed.\n");
}

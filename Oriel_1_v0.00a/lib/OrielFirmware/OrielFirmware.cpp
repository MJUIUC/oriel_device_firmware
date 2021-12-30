#include <OrielFirmware.h>

void OrielFirmware::initDevice() {
  Serial.begin(115200);
  this->displayController.initDisplay();
  this->fileController.initSDCard();
}

void OrielFirmware::applyDeviceConfig(struct DeviceConfig *deviceConfig){

}

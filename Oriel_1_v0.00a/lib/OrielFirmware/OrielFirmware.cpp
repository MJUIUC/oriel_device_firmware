#include <OrielFirmware.h>

void OrielFirmware::initDevice() {
  Serial.begin(115200);
  this->displayController.initDisplay();
}

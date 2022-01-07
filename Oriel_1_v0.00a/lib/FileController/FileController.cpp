#include <FileController.h>

bool FileController::initSDCard(){
    if (!SD.begin(SD_CS))
    {
      Serial.print("SD Card initialisation failed!\n");
      return false;
    } else {
      Serial.print("\r\nSD Card initialisation success!\n");
      return true;
    }
}

bool FileController::initSPIFFS(){
  if(!SPIFFS.begin()) {
    Serial.print("SPIFFS initialization failed!\n");
    return false;
  } else {
    Serial.print("SPIFFS initialization success!\n");
    return true;
  }
}
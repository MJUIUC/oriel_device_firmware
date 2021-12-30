#include <FileController.h>

void FileController::initSDCard(){
    if (!SD.begin(SD_CS))
    {
        Serial.println("SD Card initialisation failed!");
        while (1)
        {
            delay(50);
            yield();
        }
    }
    Serial.println("\r\nSD Card initialisation success!");
}

void FileController::updateFileControllerState(FileControllerState state){
  this->fileControllerState = state;
}

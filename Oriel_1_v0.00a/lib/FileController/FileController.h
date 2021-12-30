#ifndef FILE_CONTROLLER_h
#define FILE_CONTROLLER_h

#include <Arduino.h>
#include <SD.h>
#include <FS.h>

#define SD_CS 14

enum FileControllerState {
  OPEN,
  CLOSED
};

class FileController {
  private:
    void updateFileControllerState(FileControllerState state);
  public:
    FileControllerState fileControllerState = CLOSED;
    void initSDCard();
};

#endif /* _FILE_CONTROLLER_H_ */
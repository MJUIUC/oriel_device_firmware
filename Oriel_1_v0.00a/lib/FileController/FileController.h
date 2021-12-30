#ifndef FILE_CONTROLLER_h
#define FILE_CONTROLLER_h

#include <Arduino.h>
#include <SD.h>
#include <FS.h>
#include <Common.h>
#include <ArduinoJson.h>

#define SD_CS 14
#define JSON_FILE_BUFFER 512

class FileController {
  public:
    bool initSDCard();
    DeviceConfig* parseDeviceConfigJson(char * device_config_filepath);
};

#endif /* _FILE_CONTROLLER_H_ */
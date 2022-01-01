#ifndef FILE_CONTROLLER_h
#define FILE_CONTROLLER_h

#include <Arduino.h>
#include <SD.h>
#include <FS.h>
#include <DeviceConfig.h>
#include <HardwarePins.h>
#include <ArduinoJson.h>

#define JSON_FILE_BUFFER 512

#define DEVICE_CONFIG_FILEPATH "/.device_config.json"

class FileController {
  public:
    bool initSDCard();
    DeviceConfig* parseDeviceConfigJson(char * device_config_filepath);
};

#endif /* _FILE_CONTROLLER_H_ */
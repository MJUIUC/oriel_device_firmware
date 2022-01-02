#ifndef FILE_CONTROLLER_h
#define FILE_CONTROLLER_h

#include <Arduino.h>
#include <SD.h>
#include <FS.h>
#include <DeviceConfig.h>
#include <HardwarePins.h>
#include <ArduinoJson.h>

#define DEVICE_CONFIG_FILE_PATH "/.device_config.json"
#define ORIEL_CONFIG_FILE_PATH "/.oriel_config.json"
#define DIGITAL_ASSETS_FOLDER_PATH "/digital_assets"

typedef enum {
  JSON,
  JPEG,
  GIF,
  PNG,
} FileExtensionTypes;

class FileController {
  public:
    bool initSDCard();
    DeviceConfig* parseDeviceConfigJson(char * device_config_filepath);
    /**
     * @brief Save Data String As File
     * 
     * Saves a strng of data as a file to the given path, with the given extension.
     */
    File *saveDataStringAsFile(const char * data, const char* path, FileExtensionTypes fileType);
};

#endif /* _FILE_CONTROLLER_H_ */
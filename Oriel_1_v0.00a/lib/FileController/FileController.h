#ifndef FILE_CONTROLLER_h
#define FILE_CONTROLLER_h

#include <Arduino.h>
#include <SD.h>
#include <FS.h>
#include <DeviceConfig.h>
#include <OrielConfig.h>
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
  NO_MATCH
} FileExtensionTypes;

class FileController {
  public:
    bool initSDCard();
    DeviceConfig* parseDeviceConfigJson(char * device_config_filepath);
    OrielConfig* parseOrielConfigJson(char * oriel_config_filepath);
    /**
     * @brief Save Data String As File
     * 
     * Saves a strng of data as a file to the given path. Returns a pointer
     * to the file if successful, and NULL if not.
     */
    File *saveDataStringAsFile(const char * data, const char* path);

    String transposeFileExtensionType(FileExtensionTypes extension){
      switch(extension){
        case JSON: return ".json";
        case JPEG: return ".jpeg";
        case GIF: return ".gif";
        case PNG: return ".png";
        default: return "no_match";
      }
    }
};

#endif /* _FILE_CONTROLLER_H_ */
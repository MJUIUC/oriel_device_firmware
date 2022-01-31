#ifndef FILE_CONTROLLER_h
#define FILE_CONTROLLER_h

#include <Arduino.h>
#include <SPIFFS.h>
#include <SD.h>
#include <FS.h>
#include <WiFiCredentials.h>
#include <Common.h>
#include <OrielDeviceConfig.h>
#include <HardwarePins.h>
#include <ArduinoJson.h>

#define DEVICE_CONFIG_FILE_PATH "/.oriel_device_config.json" // device configuration saved to spiffs
#define WIFI_JSON_FILE_PATH "/wifi.json" // saved to spiffs
#define DIGITAL_ASSETS_FOLDER_PATH "/digital_assets" // folder location of downloaded assets
#define DIGITAL_ASSETS_SYNC_FILE_PATH "/.oriel_digital_asset_sync.json" // json file of digital asset contract address token id pairings. saved to SD

typedef enum {
  JSON,
  JPEG,
  GIF,
  PNG,
  NO_MATCH
} FileExtensionTypes;

class FileController {
  public:
    WiFiCredentials* parseWiFiJsonFromSpiffs(char * wifi_json_filepath);
    OrielDeviceConfig* parseOrielConfigJson(char * oriel_config_filepath);
    bool initSDCard();
    bool initSPIFFS();
    // returns false if it failed to write a file
    bool writeWifiCredentialsToSPIFFS(WiFiCredentials *wifiCredentials);
    /**
     * @brief Save Data String As File
     * 
     * Saves a strng of data as a file to the given path. Returns a pointer
     * to the file if successful, and NULL if not.
     */
    File *saveDataStringAsFile(const char * data, const char* path);

    String fileExtensionTypeToString(FileExtensionTypes extension){
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
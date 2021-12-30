#include <FileController.h>

bool FileController::initSDCard(){
    if (!SD.begin(SD_CS))
    {
        Serial.println("SD Card initialisation failed!");
        return false;
        while (1)
        {
            delay(50);
            yield();
        }
    }
    Serial.println("\r\nSD Card initialisation success!");
    return true;
}

DeviceConfig *FileController::parseDeviceConfigJson(char * device_config_filepath){
  File deviceConfigJson = SD.open(device_config_filepath, FILE_READ);
  DynamicJsonDocument doc(deviceConfigJson.size() + JSON_FILE_BUFFER);

  String raw_json = "";
  while(deviceConfigJson.available()){
      String c = deviceConfigJson.readString();
      raw_json += c;
  }

  DeserializationError error = deserializeJson(doc, raw_json);
  if (error) {
    // TODO: Handle. Returning a null value for now
    return NULL;
  } else {
    DeviceConfig n_config = {
      (char *)doc["network_ssid"],
      (char *)doc["network_password"],
      (char *)doc["opperating_wallet_address"],
      (char *)doc["firmware_version"],
      (unsigned long) doc["latest_server_sync_timestamp_ms"],
      (unsigned long) doc["latest_firmware_update_timestamp_ms"]
    };
    return &n_config;
  }
}

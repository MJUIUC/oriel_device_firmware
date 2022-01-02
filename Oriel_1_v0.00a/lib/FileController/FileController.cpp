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
  // file size doesn't matter I guess
  DynamicJsonDocument doc(ESP.getMaxAllocHeap());

  String raw_json = "";
  while(deviceConfigJson.available()){
      String c = deviceConfigJson.readString();
      raw_json += c;
  }
  // Serial.printf("Raw json: %s\n\n", raw_json.c_str());
  DeserializationError error = deserializeJson(doc, raw_json);
  if (error) {
    // TODO: Handle. Returning a null value for now
    Serial.printf("Config Parse Error: %s\n", error.c_str());
    return NULL;
  } else {
    DeviceConfig *n_config = new DeviceConfig(
      doc["network_ssid"].as<const char *>(),
      doc["network_password"].as<const char *>(),
      doc["opperating_wallet_address"].as<const char *>(),
      doc["oriel_device_id"].as<const char *>(),
      doc["firmware_version"].as<const char *>(),
      doc["latest_server_sync_timestamp_ms"].as<const char *>(),
      doc["latest_firmware_update_timestamp_ms"].as<const char *>()
    );
    return n_config;
  }
}

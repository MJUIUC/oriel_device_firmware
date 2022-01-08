#include <FileController.h>

WiFiCredentials *FileController::parseWiFiJsonFromSpiffs(char * wifi_json_filepath){
  if (!SPIFFS.exists(WIFI_JSON_FILE_PATH)) {
    return NULL;
  } else {
    File wifiJson = SPIFFS.open(WIFI_JSON_FILE_PATH, FILE_READ);

    DynamicJsonDocument doc(ESP.getMaxAllocHeap());

    String raw_json = "";

    while(wifiJson.available()) {
      String c = wifiJson.readString();
      raw_json += c;
    }

    DeserializationError error = deserializeJson(doc, raw_json);

    if (error) {
      Serial.printf("Config Parse Error: %s\n", error.c_str());
      return NULL;
    } else {
      WiFiCredentials *n_credentials = new WiFiCredentials(
        doc["network_ssid"].as<const char *>(),
        doc["network_password"].as<const char *>()
      );
      return n_credentials;
    }
  }
}

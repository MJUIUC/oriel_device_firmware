#include <FileController.h>

WiFiCredentials *FileController::parseWiFiJsonFromSpiffs(char * wifi_json_filepath){
  if (!SPIFFS.exists(WIFI_JSON_FILE_PATH)) {
    return NULL;
  } else {
    File wifiJson = SPIFFS.open(WIFI_JSON_FILE_PATH, FILE_READ);
    delay(500);
    DynamicJsonDocument doc(ESP.getMaxAllocHeap());

    String raw_json = "";

    while(wifiJson.available()) {
      String c = wifiJson.readString();
      raw_json += c;
    }

    Serial.printf("wifijson body: %s\n", raw_json.c_str());

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

// Writes a wifi.json file to SPIFFS
bool FileController::writeWifiCredentialsToSPIFFS(WiFiCredentials *wifiCredentials){
  if (SPIFFS.exists(WIFI_JSON_FILE_PATH)) {
    SPIFFS.remove(WIFI_JSON_FILE_PATH);
    delay(200);
  }

  File credential_file = SPIFFS.open(WIFI_JSON_FILE_PATH, FILE_WRITE);
  delay(200);
  if (!credential_file) {
    Serial.println("Error opening wifijson file for writing!\n\n");
    return false;
  }
  int bytes_written = credential_file.printf("%s", wifiCredentials->wifi_credentials_body);

  credential_file.close();
  if (bytes_written > 0) {
    Serial.printf("wifi config wrote: %f\n\n", bytes_written);
    return true;
  } else {
    return false;
  }
}

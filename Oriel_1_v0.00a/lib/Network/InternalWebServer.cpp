#include <InternalWebServer.h>

bool InternalWebServer::checkHardwareFree(){
  return WiFi.isConnected();
}

bool InternalWebServer::initWiFiApMode(){
  if (this->checkHardwareFree()) {
    // decide what to do when already connected?
    return false;
  } else {
    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP(this->device_ssid, this->device_password);
    this->softAPIP = WiFi.softAPIP();
    return true;
  }
}

void InternalWebServer::notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page not found");
}

void InternalWebServer::startInternalWebService(){
  if (this->initWiFiApMode()) {
    
    this->webServer->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html");
    });

    this->webServer->on("/scripts.js", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/scripts.js");
    });

    this->webServer->on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/styles.css");
    });

    this->webServer->on("/device_information.json", HTTP_GET, [this](AsyncWebServerRequest *request){
      
    });

    this->webServer->on(
      "/update_wifi_credentials",
      HTTP_POST,
      [](AsyncWebServerRequest *request){},
      NULL,
      [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){ 
        String* incoming_data_stirng = new String("");
        for (size_t i = 0; i < len; i++){
          *incoming_data_stirng += (char)data[i];
        }

        DynamicJsonDocument doc(ESP.getMaxAllocHeap());
        DeserializationError error = deserializeJson(doc, *incoming_data_stirng);
        
        if (error) {
          String message = "internal web server error: " + (String)error.c_str();
          Serial.printf("internal web server error: %s\n", error.c_str());
          request->send(400, "text/json", message);
        } else {
          const char *potential_ssid = doc["network_ssid"].as<const char *>();
          const char *potential_password = doc["network_password"].as<const char *>();
          Serial.printf("request body: %s\n\n", incoming_data_stirng->c_str());  
          this->potentialWifiCredentials = new WiFiCredentials(potential_ssid, potential_password, incoming_data_stirng->c_str());
          request->send(200, "text", (String)"Updating new credentials. Please close this window.");
        }
      });

    this->webServer->onNotFound(this->notFound);
    this->webServer->begin();
    this->internalWebServerActive = true;
  }
}

void InternalWebServer::killInternalWebService(){
  this->internalWebServerActive = false;
  this->webServer->end();
}

void InternalWebServer::stopWifiHardware(){
  WiFi.mode(WIFI_MODE_NULL);
}

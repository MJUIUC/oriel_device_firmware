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

    this->webServer->onNotFound(this->notFound);
    this->webServer->begin();
  }
}
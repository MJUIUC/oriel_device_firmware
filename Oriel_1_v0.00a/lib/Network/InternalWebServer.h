#ifndef INTERNAL_WEB_SERVER_h
#define INTERNAL_WEB_SERVER_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class InternalWebServer {
  public:
    AsyncWebServer *webServer = new AsyncWebServer(80);

    const char * device_ssid = "Oriel Mira 1";
    const char * device_password = "orielmira";

    IPAddress softAPIP;

    bool checkHardwareFree();
    bool initWiFiApMode();

    static void notFound(AsyncWebServerRequest *request);

    void startInternalWebService();
};

#endif /* _INTERNAL_WEB_SERVER_H_ */
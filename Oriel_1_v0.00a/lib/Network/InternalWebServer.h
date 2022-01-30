#ifndef INTERNAL_WEB_SERVER_h
#define INTERNAL_WEB_SERVER_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiCredentials.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class InternalWebServer
{
public:
  AsyncWebServer *webServer = new AsyncWebServer(80);

  const char *device_ssid = "Oriel Mira 1";
  const char *device_password = "orielmira";
  bool internalWebServerActive = false;

  /*
    These wifi credentials are set on a post request
    to the internal web service. It starts out as NULL, and only
    changes when the endpoint is called with sufficiend credentials.
  */
  WiFiCredentials *potentialWifiCredentials;

  IPAddress softAPIP;

  bool checkHardwareFree();
  bool initWiFiApMode();
  void stopWifiHardware();

  static void notFound(AsyncWebServerRequest *request);

  void startInternalWebService();
  void killInternalWebService();
};

#endif /* _INTERNAL_WEB_SERVER_H_ */
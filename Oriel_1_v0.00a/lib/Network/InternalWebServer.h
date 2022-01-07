#ifndef INTERNAL_WEB_SERVER_h
#define INTERNAL_WEB_SERVER_h

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class InternalWebServer {
  public:
    AsyncWebServer webServer(80);
};

#endif /* _INTERNAL_WEB_SERVER_H_ */
#ifndef NETWORK_CONTROLLER_h
#define NETWORK_CONTROLLER_h

#include <WiFi.h>

class NetworkController {
  private:
    int wireless_network_connection_timeout = 5;
  public:
    wl_status_t network_connection_status = WL_DISCONNECTED;
    wl_status_t getAndSetConnectionStatus();
    bool initWiFi(const char * ssid, const char * password);
    void dissableWiFi();
};

#endif /* _NETWORK_CONTROLLER_H_ */
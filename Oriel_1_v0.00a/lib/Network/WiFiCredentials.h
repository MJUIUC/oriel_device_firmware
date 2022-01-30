#ifndef WIFI_CREDENTIALS_h
#define WIFI_CREDENTIALS_h

#include <Arduino.h>

class WiFiCredentials {
  public:
    WiFiCredentials();
    WiFiCredentials(const char * ssid, const char * password);
    WiFiCredentials(const char * ssid, const char * password, const char * wifi_credentials_body);
    const char * wifi_network_ssid;
    const char * wifi_network_password;
    const char * wifi_credentials_body;
};

#endif /* _WIFI_CREDENTIALS_H_ */
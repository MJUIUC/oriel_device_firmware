#ifndef WIFI_CREDENTIALS_h
#define WIFI_CREDENTIALS_h

class WiFiCredentials {
  public:
    WiFiCredentials();
    WiFiCredentials(const char * ssid, const char * password);
    const char * wifi_network_ssid;
    const char * wifi_netowrk_password;
};

#endif /* _WIFI_CREDENTIALS_H_ */
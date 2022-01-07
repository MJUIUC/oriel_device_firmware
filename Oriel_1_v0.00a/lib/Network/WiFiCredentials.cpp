#include <WiFiCredentials.h>

WiFiCredentials::WiFiCredentials(){}
WiFiCredentials::WiFiCredentials(const char * ssid, const char * password){
  this->wifi_network_ssid = ssid;
  this->wifi_netowrk_password = password;
}

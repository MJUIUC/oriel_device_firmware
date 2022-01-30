#include <WiFiCredentials.h>

WiFiCredentials::WiFiCredentials(){}
WiFiCredentials::WiFiCredentials(const char * ssid, const char * password){
  this->wifi_network_ssid = ssid;
  this->wifi_network_password = password;
}
WiFiCredentials::WiFiCredentials(const char * ssid, const char * password, const char * wifi_credentials_body) {
  this->wifi_network_ssid = ssid;
  this->wifi_network_password = password;
  this->wifi_credentials_body = wifi_credentials_body;
}

#include <NetworkController.h>

bool NetworkController::initWiFi(const char * ssid, const char * password) {
    int seconds = this->wireless_network_connection_timeout;
    Serial.printf("ssid: %s\n", ssid);
    Serial.printf("password: %s\n", password);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        if (seconds == 0)
        {
            return false;
        }
        Serial.print('.');
        seconds--;
        delay(1000);
    }
    Serial.println(WiFi.localIP());
    return true;
}

wl_status_t NetworkController::getAndSetConnectionStatus(){
  this->network_connection_status = WiFi.status();
  return this->network_connection_status;
}

void NetworkController::dissableWiFi(){
  WiFi.disconnect();
}
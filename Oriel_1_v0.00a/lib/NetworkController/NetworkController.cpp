#include <NetworkController.h>

bool NetworkController::initWiFi(char * ssid, char * password) {
    int seconds = this->wireless_network_connection_timeout;
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
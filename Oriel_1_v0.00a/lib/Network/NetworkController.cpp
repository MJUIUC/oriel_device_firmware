#include <NetworkController.h>

const char *NetworkController::getUserAgent()
{
  String *u_a = new String((String)"Oriel_" + (String)DEVICE_NAME + (String)"/firmware_version: " + (String)FIRMWARE_VERSION + (String)"(ESP32; Espressif framework)");
  const char *tmp = u_a->c_str();
  return tmp;
}

/* SEVER REQUEST FUNCTIONS */
const char *NetworkController::makeServerRequest(const char *url, RequestOptions *options)
{
  if (wifiClient.connect(options->host_server_name, options->host_server_port))
  {
    String request_method = options->requestMethodTranspose(options->request_method);
    String response_body = "";
    wifiClient.print(request_method + url + " HTTP/1.1\r\n" +
                     "Host: " + options->host_server_name + "\r\n" +
                     "Connection: " + options->connection_header + "\r\n" +
                     "User-Agent: " + options->user_agent_header + "\r\n" +
                     "\r\n");

    while (wifiClient.connected() || wifiClient.available())
    {
      String line = wifiClient.readStringUntil('\n');
      Serial.println(line);
      // Capture headers here
      if (line.equals("\r"))
      {
        break;
      }
    }

    while (wifiClient.available())
    {
      char l = wifiClient.read();
      response_body += l;
    }
    wifiClient.stop();
    return (const char *)response_body.c_str();
  } else {
    Serial.print("server connection error \n");
    return NULL;
  }
}

/* HARDWARE FUNCTIONS */
bool NetworkController::initWiFi(const char *ssid, const char *password, wifi_mode_t mode)
{
  int seconds = this->wireless_network_connection_timeout;
  Serial.printf("ssid: %s\n", ssid);
  Serial.printf("password: %s\n", password);
  WiFi.mode(mode);
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

wl_status_t NetworkController::getAndSetConnectionStatus()
{
  this->network_connection_status = WiFi.status();
  return this->network_connection_status;
}

void NetworkController::dissableWiFi()
{
  WiFi.disconnect();
}
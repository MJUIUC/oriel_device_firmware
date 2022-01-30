#ifndef ORIEL_SERVER_CLIENT_CONTROLLER_h
#define ORIEL_SERVER_CLIENT_CONTROLLER_h

#include <WiFi.h>
#include <WiFiClient.h>
#include <DeviceConfig.h>
#include <ArduinoJson.h>
#include <FileController.h>

typedef enum {
  GET,
  POST,
} RequestMethod;

class RequestOptions {
  public:
    RequestOptions();
    RequestOptions(
      RequestMethod request_method,
      bool should_download_result,
      const char * host_server_name,
      int host_server_port,
      /* Header Strings */
      const char * user_agent_header,
      const char * connection_header
    );

      RequestMethod request_method;
      String request_method_string;
      const char * download_path;
      const char * host_server_name;
      int host_server_port;
      /* Header Strings */
      const char * user_agent_header;
      const char * connection_header; 

    String requestMethodTranspose(RequestMethod method){
      switch(method){
        case GET: return (String)"GET ";
        case POST: return (String)"POST ";
        default: return (String)"GET ";
      }
    }
};

class OrielServerClientController {
  private:
    int wireless_network_connection_timeout = 5;
  public:
    WiFiClient wifiClient;
    wl_status_t network_connection_status = WL_DISCONNECTED;
    wl_status_t getAndSetConnectionStatus();
    // TODO: these might belong in orile config, or wifi config
    const char * oriel_server_hostname = "192.168.1.239";
    uint16_t oriel_server_portnumber = 8080;

    IPAddress *connected_ip = new IPAddress;
    
    bool initWiFiStationMode(const char * ssid, const char * password);
    bool dissableWiFiStationMode();

    const char * getUserAgent();
    /**
     * @brief Make Server Request
     * 
     * Makes a request to a server given a set of request options.
     * One method type downloads a request and returns the resulting JSON string.
     * The other, saves the resulting string to a file.
     * 
     * @param url 
     * @param options 
     * @return String 
     */
    const char *makeServerRequest(const char * url, RequestOptions *options);
    File *makeServerRequest(const char * url, const char * downlaod_path, RequestOptions *options);
};

#endif /* _ORIEL_SERVER_CLIENT_CONTROLLER_H_ */
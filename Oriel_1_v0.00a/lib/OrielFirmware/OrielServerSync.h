#ifndef ORIEL_SERVER_SYNC_h
#define ORIEL_SERVER_SYNC_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <NetworkController.h>
#include <DeviceConfig.h>

class OrielServerSync {
  private:
    DeviceConfig *deviceConfig;
    NetworkController networkController;
    const char * oriel_server_hostname = "192.168.1.239";
    uint16_t oriel_server_portnumber = 8080;
  public:
    OrielServerSync();
    OrielServerSync(DeviceConfig *device_config);
    void requestOrielConfigJson();
    bool *requestShouldSyncBool();
};

#endif /* _ORIEL_SERVER_SYNC_H_ */
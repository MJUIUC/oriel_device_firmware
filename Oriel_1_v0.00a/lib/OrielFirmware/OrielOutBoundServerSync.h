#ifndef ORIEL_SERVER_SYNC_h
#define ORIEL_SERVER_SYNC_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <NetworkController.h>
#include <DeviceConfig.h>
#include <WalletDefinitions.h>
#include <FileController.h>

class OrielOutBoundServerSync {
  private:
    NetworkController *networkController;
    FileController *fileController;
    OrielConfig *orielConfig;
    const char * oriel_server_hostname = "192.168.1.239";
    uint16_t oriel_server_portnumber = 8080;
  public:
    OrielOutBoundServerSync();
    OrielOutBoundServerSync(OrielConfig *orielConfig, FileController *file_controller, NetworkController *network_controller);
    void requestOrielConfigJson();
    bool *requestShouldSyncBool();
};

#endif /* _ORIEL_SERVER_SYNC_H_ */
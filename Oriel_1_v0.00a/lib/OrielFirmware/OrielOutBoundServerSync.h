#ifndef ORIEL_SERVER_SYNC_h
#define ORIEL_SERVER_SYNC_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <OrielServerClientController.h>
#include <DeviceConfig.h>
#include <WalletDefinitions.h>
#include <FileController.h>

class OrielOutBoundServerSync {
  private:
    OrielServerClientController *orielServerClientController;
    FileController *fileController;
    OrielConfig *orielConfig;
  public:
    OrielOutBoundServerSync();
    OrielOutBoundServerSync(OrielConfig *orielConfig, FileController *fileController, OrielServerClientController *orielServerClientController);
    void requestOrielConfigJson();
    bool *requestShouldSyncBool();
};

#endif /* _ORIEL_SERVER_SYNC_H_ */
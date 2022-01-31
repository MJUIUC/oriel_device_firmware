#ifndef ORIEL_SERVER_SYNC_h
#define ORIEL_SERVER_SYNC_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <DigitalAsset.h>
#include <OrielServerClientController.h>
#include <WalletDefinitions.h>
#include <FileController.h>

class OrielOutBoundServerSync {
  private:
    OrielServerClientController *orielServerClientController;
    FileController *fileController;
    OrielDeviceConfig *orielDeviceConfig;
  public:
    OrielOutBoundServerSync();
    OrielOutBoundServerSync(OrielDeviceConfig *orielConfig, FileController *fileController, OrielServerClientController *orielServerClientController);
    void establishOrielServerConnection();
    void requestOrielConfigJson();
    bool requestShouldSyncBool();
};

#endif /* _ORIEL_SERVER_SYNC_H_ */
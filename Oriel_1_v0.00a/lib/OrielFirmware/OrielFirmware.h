/**
 * @file OrielFirmware.h
 * @author Marcus Jefferson (marcus@orielware.com)
 * @brief Main wrapper class covering all core device logic and definitions
 * @version 0.00a
 * @date 2021-12-29
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef ORIEL_FIRMWARE_h
#define ORIEL_FIRMWARE_h

#include <Arduino.h>

#include <GraphicsController.h>
#include <FileController.h>
#include <NetworkController.h>

#include <OrielServerSync.h>

#include <DeviceConfig.h>
#include <HardwarePins.h>

class OrielFirmware {
  private:
    /* firmware initialization routines */
    void beginSDCard();
    void beginWiFiConnection();
    void initializeDeviceConfig();
    bool isDevicePowerSufficientForWifi();
  
  public:
    DeviceConfig *deviceConfiguration;
    FirmwareState currentFirmwareState = IMAGE_CYCLING;
    /* firmware controller classes */
    GraphicsController graphicsController;
    FileController fileController;
    NetworkController networkController;

    /* Routine Classes */
    OrielServerSync *serverSync;

    void beginFirmwareInitialization();
    void beginOrielServerSync();
    bool applyDeviceConfig();

    PowerState getDevicePowerState(){
      float vRead = (analogRead(VOLTAGE_CHECK_PIN) * 3.3) / 4095;
      delay(500);
      Serial.printf("vRead: %f\n", vRead);
      if (vRead > 1.2) {
        return PLUGIN;
      } else {
        return BATTERY;
      }
    };
};

#endif /* _ORIEL_FIRMWARE_H_ */
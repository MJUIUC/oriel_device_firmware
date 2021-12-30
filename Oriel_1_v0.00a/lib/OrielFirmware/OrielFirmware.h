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
#include <DisplayController.h>
#include <FileController.h>
#include <NetworkController.h>
#include <Common.h>

class OrielFirmware {
  private:
    char * network_ssid = "Hide yo kids, Hide yo Wifi";
    char * network_password = "Peachpanda33";
    char * opperating_wallet_address;
    char * firmware_version = FIRMWARE_VERSION;
    unsigned long latest_server_sync_timestamp_ms;
    unsigned long latest_firmware_update_timestamp_ms;

    void beginSDCard();
    void beginWiFiConnection();
    void establishPowerState();
  public:
    FirmwareState currentFirmwareState = IMAGE_CYCLING;
    PowerState currentPowerState = BATTERY;
    /* firmware controller classes */
    DisplayController displayController;
    FileController fileController;
    NetworkController networkController;

    void initDeviceFirmware();
    void applyDeviceConfig(struct DeviceConfig *deviceConfig);
};

#endif /* _ORIEL_FIRMWARE_H_ */
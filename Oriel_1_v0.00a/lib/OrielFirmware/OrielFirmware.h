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

#define DEVICE_VERSION 1
#define FIRMWARE_VERSION "0.00a"

enum DeviceStates {
  IMAGE_CYCLING,
  SERVER_SYNCING
};

struct DeviceConfig {
  char * network_ssid;
  char * network_password;
  char * opperating_wallet_address;
  char * firmware_version;
  unsigned long latest_server_sync_timestamp_ms;
  unsigned long latest_firmware_update_timestamp_ms;
};

class OrielFirmware {
  private:
    char * network_ssid;
    char * network_password;
    char * opperating_wallet_address;
    char * firmware_version = FIRMWARE_VERSION;
    unsigned long latest_server_sync_timestamp_ms;
    unsigned long latest_firmware_update_timestamp_ms;
  public:
    DeviceStates defaultDeviceState = IMAGE_CYCLING;
    DisplayController displayController;
    FileController fileController;

    void initDevice();
    void applyDeviceConfig(struct DeviceConfig *deviceConfig);
};

#endif /* _ORIEL_FIRMWARE_H_ */
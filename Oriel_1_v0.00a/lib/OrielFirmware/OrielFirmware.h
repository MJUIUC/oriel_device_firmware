/**
 * @file OrielFirmware.h
 * @author Marcus Jefferson (you@domain.com)
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

#define DEVICE_VERSION "1.00"
#define FIRMWARE_VERSION "0.00a"

enum DeviceStates {
  OFF,
  ON,
  CHARGING,
  SYNCING
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
  public:
    DeviceConfig deviceConfig;
    DeviceStates deviceState;
    DisplayController displayController;

    void initDevice();
};

#endif /* _ORIEL_FIRMWARE_H_ */
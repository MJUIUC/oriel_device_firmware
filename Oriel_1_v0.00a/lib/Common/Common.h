#ifndef COMMON_h
#define COMMON_h

#include <Arduino.h>

#define DEVICE_VERSION 1
#define FIRMWARE_VERSION "0.00a"

#define VOLTAGE_CHECK_PIN 27

enum FirmwareState {
  IMAGE_CYCLING,
  SERVER_SYNCING
};

enum PowerState {
  BATTERY,
  PLUGIN
};

/**
 * DisplayTheme
 * ------------
 * General display properties for the device. Defines
 * the theme of the basic device UI.
 */
struct DisplayTheme {
  uint16_t background_color;
  uint16_t text_color;
};

struct DeviceConfig {
  char * network_ssid;
  char * network_password;
  char * opperating_wallet_address;
  char * firmware_version;
  unsigned long latest_server_sync_timestamp_ms;
  unsigned long latest_firmware_update_timestamp_ms;
};

#endif /* _COMMON_H_ */
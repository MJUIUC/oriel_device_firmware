#ifndef DEVICE_CONFIG_h
#define DEVICE_CONFIG_h

#include <Arduino.h>

#define DEVICE_NAME "MIRA"
#define DEVICE_VERSION 1.0
#define FIRMWARE_VERSION "0.00a"

enum FirmwareState
{
  IMAGE_CYCLING,
  SERVER_SYNCING
};

enum PowerState
{
  BATTERY,
  PLUGIN
};

/**
 * DisplayTheme
 * ------------
 * General display properties for the device. Defines
 * the theme of the basic device UI.
 */
struct DisplayTheme
{
  uint16_t background_color;
  uint16_t text_color;
};

class DeviceConfig
{
public:
  DeviceConfig();
  DeviceConfig(
      const char *network_ssid,
      const char *network_password,
      const char *opperating_wallet_address,
      const char *oriel_device_id,
      const char *firmware_version,
      const char *latest_server_sync_timestamp_ms,
      const char *latest_firmware_update_timestamp_ms);

  const char *network_ssid;
  const char *network_password;
  const char *oriel_device_id;
  const char *opperating_wallet_address;
  const char *firmware_version;
  const char *latest_server_sync_timestamp_ms;
  const char *latest_firmware_update_timestamp_ms;

  void printSelfToSerial();
};

#endif /* _DEVICE_CONFIG_H_ */
#define ORIEL_DEVICE_CONFIG_h
#ifndef ORIEL_DEVICE_CONGIF_h

#include <Arduino.h>
#include <DigitalAsset.h>

class OrielDeviceConfig {
public:
  OrielDeviceConfig();
  OrielDeviceConfig(
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

  // Current list of digital assets on device.
  DigitalAssetList *digital_assets;

  // Check this if we need to update (write new json file) the config after an opperation.
  bool shouldUpdateDeviceConfig = false;
  // Check this if we need to update (write new json file) the asset list after an opperation.
  bool shouldUpdateAssetList = false;

  void printSelfToSerial();
};

#endif /* _ORIEL_DEVICE_CONFIG_H_ */
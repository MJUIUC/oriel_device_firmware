#define ORIEL_CONFIG_h
#ifndef ORIEL_CONGIF_h

#include <Arduino.h>

class DigitalAsset {
  public:
    const char * name;
};

class OrielConfig {
public:
  OrielConfig();
  OrielConfig(
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

#endif /* _ORIEL_CONFIG_H_ */
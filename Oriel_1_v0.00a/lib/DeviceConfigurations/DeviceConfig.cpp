#include <DeviceConfig.h>

DeviceConfig::DeviceConfig(){}

DeviceConfig::DeviceConfig(
    const char *network_ssid,
    const char *network_password,
    const char *opperating_wallet_address,
    const char *firmware_version,
    const char * latest_server_sync_timestamp_ms,
    const char * latest_firmware_update_timestamp_ms)
{
  this->network_ssid = network_ssid;
  this->network_password = network_password;
  this->opperating_wallet_address = opperating_wallet_address;
  this->firmware_version = firmware_version;
  this->latest_server_sync_timestamp_ms = latest_server_sync_timestamp_ms;
  this->latest_firmware_update_timestamp_ms = latest_firmware_update_timestamp_ms;
}

void DeviceConfig::printSelfToSerial(){
  Serial.print("--Device Config--\n\n");
  Serial.printf("ssid: %s\n",this->network_ssid);
  Serial.printf("password: %s\n",this->network_password);
  Serial.printf("wallet address: %s\n",this->opperating_wallet_address);
  Serial.printf("firmware version: %s\n",this->firmware_version);
  Serial.printf("latest_sync: %s\n",this->latest_server_sync_timestamp_ms);
  Serial.printf("latest_fw_update: %s\n",this->latest_firmware_update_timestamp_ms);
}

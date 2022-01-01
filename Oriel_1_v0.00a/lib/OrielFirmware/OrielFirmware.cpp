#include <OrielFirmware.h>

/* !!! BEGIN DEVICE INITIALIZATION FUNCTIONS !!! */

/**
 * @brief Initialize Device Firmware
 * 
 */
void OrielFirmware::beginFirmwareInitialization()
{
  Serial.begin(115200);
  this->graphicsController.initDisplay();
  delay(1500);
  this->graphicsController.clearDisplay();
  this->graphicsController.Display->print("Initializing Device Firmware\n\n");
  this->beginSDCard();
  this->initializeDeviceConfig();
  if (this->isDevicePowerSufficientForWifi()) {
    this->beginWiFiConnection();
    // call sync routine class
  } else {

  }
}

/**
 * @brief Begin SD Card
 * 
 */
void OrielFirmware::beginSDCard()
{
  this->graphicsController.Display->print("sd: ");
  if (this->fileController.initSDCard())
  {
    this->graphicsController.Display->print("found card.\n");
    return;
  }
  this->graphicsController.Display->print("failed.\n");
}

/**
 * @brief Initialize Device Config
 * 
 * Sets the device config from the SD card upon startup.
 * 
 */
void OrielFirmware::initializeDeviceConfig()
{
  this->graphicsController.Display->print("device config:");
  if(this->applyDeviceConfig()){
    this->graphicsController.Display->print("applied successfully\n");
  } else {
    this->graphicsController.Display->print("Error!\n");
  }
}

/**
 * @brief Begin WiFi Connections
 * 
 * Enables the devices' WiFi hardware.
 */
void OrielFirmware::beginWiFiConnection()
{
  this->graphicsController.Display->print("WiFi: ");
  if (this->networkController.initWiFi(this->deviceConfiguration->network_ssid, this->deviceConfiguration->network_password))
  {
    this->graphicsController.Display->print("connection established.\n\n");
    this->graphicsController.Display->print("@: ");
    this->graphicsController.Display->printf("%s\n", this->deviceConfiguration->network_ssid);
    return;
  }
  this->graphicsController.Display->print("Failed.\n");
}

/* !!! END DEVICE INITIALIZATION FUNCTIONS !!! */

/**
 * @brief Apply Device Config
 *
 * Applies a DeviceConfig struct to Oriel Firmware
 * Main Settings.
 */
bool OrielFirmware::applyDeviceConfig()
{
  DeviceConfig *d_c = this->fileController.parseDeviceConfigJson(DEVICE_CONFIG_FILEPATH);
  if (d_c == NULL)
  {
    return false;
  }
  else
  {
    this->deviceConfiguration = d_c;
    return true;
  }
}

bool OrielFirmware::isDevicePowerSufficientForWifi(){
  return this->getDevicePowerState() == PLUGIN;
}

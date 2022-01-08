#include <OrielFirmware.h>

/* !!! BEGIN DEVICE INITIALIZATION FUNCTIONS !!! */

/**
 * @brief Initialize Device Firmware
 * 
 * This function is run at device start to initialize
 * all hardware components necessary to start the device.
 * It also calls functions foy syncronizing the device with
 * an oriel server.
 * 
 */
void OrielFirmware::beginFirmwareInitialization()
{
  this->graphicsController.initDisplay();
  delay(1500);
  this->graphicsController.clearDisplay();
  this->graphicsController.Display->print("Initializing Device Firmware\n\n");
  bool spiffsInitialized = this->fileController.initSPIFFS();
  this->graphicsController.Display->printf("spiffs initialized: %s\n", spiffsInitialized? "true" : "false");
  WiFiCredentials *wifiCredentials = this->fileController.parseWiFiJsonFromSpiffs(WIFI_JSON_FILE_PATH);
  if (this->isDevicePowerSufficientForWifi()) {
    
    // does the device have wifi credentials?
    if(wifiCredentials){
      // start oriel config sync
      this->beginWiFiConnection(wifiCredentials->wifi_network_ssid, wifiCredentials->wifi_netowrk_password);
      if(!this->serverSync->requestShouldSyncBool()) return; /* if no sync needed, leave setup */
    } else {
      // start web server and wait for user to save input. then restart device.
      if (internalWebServer.initWiFiApMode()) {
        this->graphicsController.clearDisplay();
        this->graphicsController.Display->printf("starting internal server\n\n");
        this->internalWebServer.startInternalWebService();
        this->graphicsController.Display->printf("device_ssid: %s\n", this->internalWebServer.device_ssid);
        this->graphicsController.Display->printf("device_password: %s\n\n", this->internalWebServer.device_password);
        this->graphicsController.Display->printf("navigate to the following\n");
        this->graphicsController.Display->printf("ip: %s", this->internalWebServer.softAPIP.toString().c_str());
        this->internalWebServerActive = true;
      }
    }
  }
}


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
void OrielFirmware::beginWiFiConnection(const char * ssid, const char * password)
{
  this->graphicsController.Display->print("WiFi: ");
  if (this->orielServerClientController.initWiFiStationMode(ssid, password))
  {
    this->graphicsController.Display->print("connection established.\n\n");
    this->graphicsController.Display->print("@: ");
    this->graphicsController.Display->printf("%s\n\n", ssid);
    return;
  }
  this->graphicsController.Display->print("Failed.\n");
}

/* !!! END DEVICE INITIALIZATION FUNCTIONS !!! */

void OrielFirmware::beginOrielServerSync(){
  this->graphicsController.Display->print("begin server sync?: ");
  bool *_p_should_sync_with_service = this->serverSync->requestShouldSyncBool();
  if (_p_should_sync_with_service) {
    bool should_perform_sync = *_p_should_sync_with_service;
    String s = should_perform_sync ? "yes" : "no";
    this->graphicsController.Display->printf("%s\n", (const char*)s.c_str());

    // call sync to download oriel_config.json
    if (should_perform_sync) {
      this->graphicsController.Display->print("downloading oriel_config.json\n");
      this->serverSync->requestOrielConfigJson();
    }

  } else {
    this->graphicsController.Display->print("no\n");
  }
}

bool OrielFirmware::isDevicePowerSufficientForWifi(){
  return this->getDevicePowerState() == PLUGIN;
}

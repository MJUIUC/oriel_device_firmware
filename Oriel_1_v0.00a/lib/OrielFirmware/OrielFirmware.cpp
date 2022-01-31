#include <OrielFirmware.h>

/* !!! BEGIN MAIN FIRMWARE INIT FUNCTION !!! */

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
  this->graphicsController.Display->printf("spiffs initialized: %s\n", spiffsInitialized ? "true" : "false");
  WiFiCredentials *wifiCredentials = this->fileController.parseWiFiJsonFromSpiffs(WIFI_JSON_FILE_PATH);
  if (this->isDevicePowerSufficientForWifi())
  {
    OrielDeviceConfig *orielDeviceConfig; /* TODO: parse current config from spiffs */
    // does the device have wifi credentials?
    if (wifiCredentials)
    {
      orielDeviceConfig = new OrielDeviceConfig(
        wifiCredentials->wifi_network_ssid,
        wifiCredentials->wifi_network_password,
        DEVICE_OWNER_WALLET_ADDRESS,
        ORIEL_NETWORK_DEVICE_ID,
        FIRMWARE_VERSION,
        "10000000",
        "10000000");
      // try to establish a connection with given config
      this->graphicsController.Display->print("network credentials found\n");
      this->graphicsController.Display->print("establishing connection...\n");
      if (this->beginAccessPointConnection(wifiCredentials->wifi_network_ssid, wifiCredentials->wifi_network_password))
      {
        if (!this->beginSDCard())
          return; /* if no sd card present, leave setup */

        // Setup firmware classes which require SD

        OrielOutBoundServerSync *orielServerSync = new OrielOutBoundServerSync(orielDeviceConfig, &this->fileController, &this->orielServerClientController);

        if (!orielServerSync->requestShouldSyncBool())return; /* if no sync needed, leave setup */
        delay(500);
        orielServerSync->requestOrielConfigJson();
        
        DigitalAsset *temp = orielDeviceConfig->digital_assets->head;
        while(temp != NULL) {
          Serial.printf("contract address: %s, token_id: %s\n", temp->contract_address, temp->token_id);
          temp = temp->next;
        }

        // return on sync routine end
        return;
      }
      else
      {
        // This should be a choice if there's already content present on device
        this->graphicsController.Display->print("failed establishing netowrk connection\n");
        delay(1000);
      }
    }
    orielDeviceConfig = new OrielDeviceConfig(
        "unset",
        "unset",
        DEVICE_OWNER_WALLET_ADDRESS,
        DEVICE_NAME,
        FIRMWARE_VERSION,
        "10000000",
        "10000000");
    // If there are no network credentials, or we couldn't establish connection, run the internal server.
    if (internalWebServer.initWiFiApMode())
    {
      this->graphicsController.clearDisplay();
      this->graphicsController.Display->printf("starting internal server\n\n");
      this->internalWebServer.startInternalWebService();
      this->graphicsController.Display->printf("device_ssid: %s\n", this->internalWebServer.device_ssid);
      this->graphicsController.Display->printf("device_password: %s\n\n", this->internalWebServer.device_password);
      this->graphicsController.Display->printf("navigate to the following\n");
      this->graphicsController.Display->printf("ip: %s\n", this->internalWebServer.softAPIP.toString().c_str());

      // While the server is active, listen for changes in the firmware
      while (this->internalWebServer.internalWebServerActive)
      {
        // Potential wifi credentials recieved by client. Set and restart device
        if (this->internalWebServer.potentialWifiCredentials)
        {
          this->graphicsController.clearDisplay();
          this->graphicsController.Display->setCursor(0, 0);
          this->graphicsController.Display->print("Recieved Wifi Credentials\n\n");
          this->graphicsController.Display->printf("ssid: %s\n", this->internalWebServer.potentialWifiCredentials->wifi_network_ssid);
          this->graphicsController.Display->printf("password: %s\n\n", this->internalWebServer.potentialWifiCredentials->wifi_network_password);
          delay(200);
          this->internalWebServer.killInternalWebService();
          this->internalWebServer.stopWifiHardware();
          this->graphicsController.Display->print("Saving credentials...\n");
          if (this->fileController.writeWifiCredentialsToSPIFFS(this->internalWebServer.potentialWifiCredentials))
          {
            this->graphicsController.Display->print("credentials updated successfully...\n");
          }
          else
          {
            this->graphicsController.Display->print("failed to write credentials...\n");
          }

          this->graphicsController.Display->print("restarting device in: ");
          int cursor_x = this->graphicsController.Display->getCursorX();
          int cursor_y = this->graphicsController.Display->getCursorY();
          int seconds = 10;
          while (seconds > 0)
          {
            this->graphicsController.Display->fillRect(cursor_x, cursor_y, cursor_x + 5, 1, this->graphicsController.defaultTheme.background_color);
            this->graphicsController.Display->setCursor(cursor_x, cursor_y);
            this->graphicsController.Display->printf("%i", seconds);
            delay(1000);
            --seconds;
          }
          ESP.restart();
        }
      }
    }
  }
}

/* !!! END MAIN FIRMWARE INIT FUNCTION !!! */

bool OrielFirmware::beginSDCard()
{
  this->graphicsController.Display->print("sd: ");
  if (this->fileController.initSDCard())
  {
    this->graphicsController.Display->print("found card.\n");
    return true;
  }
  this->graphicsController.Display->print("failed.\n");
  return false;
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
  if (this->applyDeviceConfig())
  {
    this->graphicsController.Display->print("applied successfully\n");
  }
  else
  {
    this->graphicsController.Display->print("Error!\n");
  }
}

/**
 * @brief Begin WiFi Connections
 *
 * Attempts to connect the device to an Access Point
 * provided by the onboard wifi configuration json.
 * This file is set by user intput through the internal
 * web server.
 *
 * returns true if a connection is established, and false otherwise.
 */
bool OrielFirmware::beginAccessPointConnection(const char *ssid, const char *password)
{
  this->graphicsController.Display->print("WiFi: ");
  if (this->orielServerClientController.initWiFiStationMode(ssid, password))
  {
    this->graphicsController.Display->print("connection established.\n\n");
    this->graphicsController.Display->printf("on network: %s\n", ssid);
    return true;
  }
  this->graphicsController.Display->print("connection failed.\n");
  return false;
}

/* !!! END DEVICE INITIALIZATION FUNCTIONS !!! */

void OrielFirmware::beginOrielServerSync(OrielOutBoundServerSync *serverSync)
{
  this->graphicsController.Display->print("begin server sync?: ");
  bool should_sync_with_service = serverSync->requestShouldSyncBool();
  if (should_sync_with_service)
  {
    bool should_perform_sync = should_sync_with_service;
    String s = should_perform_sync ? "yes" : "no";
    this->graphicsController.Display->printf("%s\n", (const char *)s.c_str());

    // call sync to download oriel_config.json
    if (should_perform_sync)
    {
      this->graphicsController.Display->print("downloading oriel_config.json\n");
      serverSync->requestOrielConfigJson();
    }
  }
  else
  {
    this->graphicsController.Display->print("no\n");
  }
}

bool OrielFirmware::isDevicePowerSufficientForWifi()
{
  return this->getDevicePowerState() == PLUGIN;
}

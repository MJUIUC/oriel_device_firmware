#include <OrielOutBoundServerSync.h>

OrielOutBoundServerSync::OrielOutBoundServerSync(){};
OrielOutBoundServerSync::OrielOutBoundServerSync(OrielDeviceConfig *orielConfig, FileController *fileController, OrielServerClientController *orielServerClient)
{
  this->orielDeviceConfig = orielConfig;
  this->fileController = fileController;
  this->orielServerClientController = orielServerClient;
};

// server returns true if device is ready for sync
bool OrielOutBoundServerSync::requestShouldSyncBool()
{
  String user_agent_string = (String)this->orielServerClientController->getUserAgent();
  RequestOptions *requestOptions = new RequestOptions(
      GET, false, this->orielServerClientController->oriel_server_hostname,
      this->orielServerClientController->oriel_server_portnumber, user_agent_string.c_str(),
      "close");

  String url = "/device/sync_ready.json?wallet_address=" + (String)this->orielDeviceConfig->opperating_wallet_address +
                "&device_id=" + (String)this->orielDeviceConfig->oriel_device_id;

  const char *server_response_body = this->orielServerClientController->makeServerRequest(url.c_str(), requestOptions);
  // Serial.printf("server response: %s\n\n", server_response_body);
  if (!server_response_body)
  {
    String error_msg = requestOptions->request_method_string + ": " + (String)url + " Failed!";
    Serial.printf("%s\n", error_msg.c_str());
    return false;
  } else {
    DynamicJsonDocument doc(ESP.getMaxAllocHeap());
    Serial.printf("server response: %s\n", server_response_body);
    DeserializationError error = deserializeJson(doc, server_response_body);
    
    if (error) {
      Serial.printf("Config Parse Error: %s\n", error.c_str());
      return false;
    } else {
      return doc["device_sync_ready"].as<bool>();
    }
  }
}

void OrielOutBoundServerSync::requestOrielConfigJson() {
  // TODO: Request oriel_config json and downlaod it to a file.
  String user_agent_string = (String)this->orielServerClientController->getUserAgent();
  RequestOptions requestOptions = RequestOptions(
      GET, false, this->orielServerClientController->oriel_server_hostname,
      this->orielServerClientController->oriel_server_portnumber, user_agent_string.c_str(),
      "close");
  
  String url = "/device/oriel_config.json?wallet_address=" + (String)this->orielDeviceConfig->opperating_wallet_address +
                "&device_id=" + (String)this->orielDeviceConfig->oriel_device_id;
  
  const char *server_response_body = this->orielServerClientController->makeServerRequest(url.c_str(), &requestOptions);
  // Serial.printf("oriel_config.json: %s\n", server_response_body);
  // File *oriel_config_json_file = this->fileController->parseOrielConfigJson(ORIEL_CONFIG_FILE_PATH);
  DynamicJsonDocument doc(ESP.getMaxAllocHeap());
  // Serial.printf("server response: %s\n", server_response_body);
  DeserializationError error = deserializeJson(doc, server_response_body);
  
  if (error) {
    Serial.printf("Config Parse Error : %s\n", error.c_str());
    return;
  } else {
    
    const char * timestamp = doc["download_timestamp"].as<const char *>();
    JsonArray asset_references = doc["asset_references"].as<JsonArray>();
    int asset_count = doc["number_of_assets"].as<int>();
    DigitalAssetList *assets = new DigitalAssetList();
    for (JsonObject o: asset_references) {
        const char * contract_address = o["asset_contract_address"].as<const char *>();
        const char * token_id = o["asset_token_id"].as<const char *>();
        DigitalAsset *asset = new DigitalAsset(contract_address, token_id);
        // Serial.printf("asset contract address: %s\n", asset->contract_address);
        // Serial.printf("token: %s\n", asset->token_id);
        assets->addAssetToList(asset);
    }
    this->orielDeviceConfig->digital_assets = assets;
    this->orielDeviceConfig->latest_server_sync_timestamp_ms = timestamp;
    this->orielDeviceConfig->shouldUpdateDeviceConfig = true;
    this->orielDeviceConfig->shouldUpdateAssetList = true;
  }
}

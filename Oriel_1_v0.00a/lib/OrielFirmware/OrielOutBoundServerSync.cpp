#include <OrielOutBoundServerSync.h>

OrielOutBoundServerSync::OrielOutBoundServerSync(){};
OrielOutBoundServerSync::OrielOutBoundServerSync(OrielConfig *orielConfig, FileController *fileController, OrielServerClientController *orielServerClient)
{
  this->orielConfig = orielConfig;
  this->fileController = fileController;
  this->orielServerClientController = orielServerClient;
};

bool *OrielOutBoundServerSync::requestShouldSyncBool()
{
  String user_agent_string = (String)this->orielServerClientController->getUserAgent();
  RequestOptions requestOptions = RequestOptions(
      GET, false, this->orielServerClientController->oriel_server_hostname,
      this->orielServerClientController->oriel_server_portnumber, user_agent_string.c_str(),
      "close");

  String url = "/device/sync_ready.json?wallet_address=" + (String)this->orielConfig->opperating_wallet_address +
                "&device_id=" + (String)this->orielConfig->oriel_device_id;
  const char *server_response_body = this->orielServerClientController->makeServerRequest(url.c_str(), &requestOptions);
  if (!server_response_body)
  {
    String error_msg = requestOptions.request_method_string + ": " + (String)url + " Failed!";
    Serial.printf("%s\n", error_msg.c_str());
    return NULL;
  } else {
    DynamicJsonDocument doc(ESP.getMaxAllocHeap());
    Serial.printf("server response: %s\n", server_response_body);
    DeserializationError error = deserializeJson(doc, server_response_body);
    
    if (error) {
      Serial.printf("Config Parse Error: %s\n", error.c_str());
      return NULL;
    } else {
      bool ready = doc["device_sync_ready"].as<bool>();
      bool *_p = (bool *)malloc(sizeof(bool));
      *_p = ready;
      return _p;
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
  
  String url = "/device/oriel_config.json?wallet_address=" + (String)this->orielConfig->opperating_wallet_address +
                "&device_id=" + (String)this->orielConfig->oriel_device_id;
  
  const char *server_response_body = this->orielServerClientController->makeServerRequest(url.c_str(), &requestOptions);
  Serial.printf("oriel_config.json: %s\n", server_response_body);
  // File *oriel_config_json_file = this->fileController->parseOrielConfigJson(ORIEL_CONFIG_FILE_PATH);
  
}

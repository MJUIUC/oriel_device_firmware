#include <OrielServerSync.h>

OrielServerSync::OrielServerSync(){};
OrielServerSync::OrielServerSync(DeviceConfig *device_config)
{
  this->deviceConfig = device_config;
};

bool *OrielServerSync::requestShouldSyncBool()
{
  String user_agent_string = (String)this->networkController.getUserAgent();
  RequestOptions requestOptions = RequestOptions(
      GET, false, this->oriel_server_hostname,
      this->oriel_server_portnumber, user_agent_string.c_str(),
      "close");

  String url = "/device/sync_ready.json?wallet_address=" + (String)this->deviceConfig->opperating_wallet_address +
                "&device_id=" + (String)this->deviceConfig->oriel_device_id;
  const char *server_response_body = this->networkController.makeServerRequest(url.c_str(), &requestOptions);
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

void OrielServerSync::requestOrielConfigJson() {
  // TODO: Request oriel_config json and downlaod it to a file.
}

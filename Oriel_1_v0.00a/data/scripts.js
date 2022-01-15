const wifiCredentialsSSIDInput = document.getElementById("ssid-input");
const wifiCredentialsPasswordInput = document.getElementById("password-input");
const wifiCredentialsSubmitButton = document.getElementById("wifi-credentials-submit-button");

function submitWifiCredentials(event){
  const network_ssid = wifiCredentialsSSIDInput.value;
  const network_password = wifiCredentialsPasswordInput.value;

  alert(`cur window url: ${getServerUrl()}`);

  if (network_ssid.length === 0 || network_password.length === 0) {
    alert("please enter a full network id and password");
  } else {
    const json_request_payload = {network_ssid, network_password};
    makeInternalServerRequest(
      "POST",
     `${getServerUrl()}update_wifi_credentials`,
      JSON.stringify(json_request_payload)
      ).then(res => {
        console.log(res);
      }).catch(err => {
        alert("Request Error!");
        console.log(err);
      });
  }
}

function makeInternalServerRequest(method, url, payload){
  return new Promise((resolve, reject) => {
    const xhttp = new XMLHttpRequest();
    xhttp.open(method, url, true);
    xhttp.onreadystatechange = function () {
      if (this.readyState == XMLHttpRequest.DONE && this.status == 200) {
        // Typical action to be performed when the document is ready:
        resolve({status: this.status, message: "request completed"});
      } else if (this.readyState == XMLHttpRequest.DONE && this.status != 200) {
        reject({status: this.status, message: "request failed"});
      }
    };

    if (payload) {
      xhttp.send(payload);
    } else {
      xhttp.send();
    }
  });
}

function getServerUrl(){
  const cur_url = window.location.href;
  return cur_url;
}

wifiCredentialsSubmitButton.addEventListener("click", submitWifiCredentials);

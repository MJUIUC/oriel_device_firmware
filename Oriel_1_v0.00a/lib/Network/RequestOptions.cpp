#include <OrielServerClientController.h>

RequestOptions::RequestOptions(){};

RequestOptions::RequestOptions(
      RequestMethod request_method,
      bool should_download_result,
      const char * host_server_name,
      int host_server_port,
      /* Header Strings */
      const char * user_agent_header,
      const char * connection_header)
{
  this->request_method = request_method;
  this->request_method_string = this->requestMethodTranspose(request_method);
  this->download_path = download_path;
  this->host_server_name = host_server_name;
  this->host_server_port = host_server_port;
  this->user_agent_header = user_agent_header;
  this->connection_header = connection_header;
};

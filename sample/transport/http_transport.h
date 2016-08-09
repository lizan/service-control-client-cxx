/* Copyright 2016 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef SERVICE_CONTROL_CLIENT_CXX_SAMPLE_HTTP_TRANSPORT_H
#define SERVICE_CONTROL_CLIENT_CXX_SAMPLE_HTTP_TRANSPORT_H

#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include "google/api/servicecontrol/v1/service_controller.pb.h"
#include "google/protobuf/stubs/logging.h"
#include "google/protobuf/stubs/status.h"
#include "include/service_control_client.h"

using ::google::api::servicecontrol::v1::CheckRequest;
using ::google::api::servicecontrol::v1::CheckResponse;
using ::google::api::servicecontrol::v1::ReportRequest;
using ::google::api::servicecontrol::v1::ReportResponse;

namespace google {
namespace service_control_client {
namespace sample {
namespace transport {

class LibCurlTransport {
 public:
  LibCurlTransport(std::string server_url, std::string service_name,
                   std::string token) {
    check_url_ = server_url + "/v1/services/" + service_name + ":check";
    report_url_ = server_url + "/v1/services/" + service_name + ":report";
    std::stringstream ss;
    ss << "Authorization: Bearer " << token;
    auth_token_header_ = ss.str();
    curl_global_init(CURL_GLOBAL_DEFAULT);
  }

  ~LibCurlTransport() { curl_global_cleanup(); };

  void Check(const ::google::api::servicecontrol::v1::CheckRequest& request,
             ::google::api::servicecontrol::v1::CheckResponse* response,
             TransportDoneFunc on_done);

  void Report(const ::google::api::servicecontrol::v1::ReportRequest& request,
              ::google::api::servicecontrol::v1::ReportResponse* response,
              TransportDoneFunc on_done);

 private:
  std::string auth_token_header_;
  std::string check_url_;
  std::string report_url_;
};

}  // namespace transport
}  // namespace sample
}  // namespace service_control_client
}  // namespace google

#endif  // SERVICE_CONTROL_CLIENT_CXX_SAMPLE_HTTP_TRANSPORT_H

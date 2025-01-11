#include "Controller.h"
#include <httplib.h>
#include <spdlog/common.h>

std::unordered_map<std::string, std::function<void(const httplib::Request&, httplib::Response&)>> Controller::entries = {};

void Controller::defaultResponse (const httplib::Request& req, httplib::Response& res) {
  Logger::getInstance()->logger->log(spdlog::level::warn, "handler name not found in the controller");
}

std::function<void(const httplib::Request&, httplib::Response&)> Controller::handle(std::string key) {
  if (auto search = entries.find(key); search != entries.end()) {
    return search->second;
  } else {
    return defaultResponse;
  }
}

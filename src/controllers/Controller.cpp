#include "Controller.h"
#include <httplib.h>
#include <spdlog/common.h>

void Controller::defaultResponse (const httplib::Request& req, httplib::Response& res) {
  Logger::getInstance()->logger->log(spdlog::level::warn, "handler name not found in the controller");
}

std::function<void(const httplib::Request&, httplib::Response&)> Controller::handleBy (std::string key) {
  if (auto search = entries.find(key); search != entries.end()) {
    return search->second;
  } else {
    return defaultResponse;
  }
}

void Controller::registerCallback (std::string key, std::function<void(const httplib::Request&, httplib::Response&)> cb) {
  if (auto search = entries.find(key); search != entries.end()) {
    Logger::getInstance()->logger->log(spdlog::level::err, "CONTROLLER key exists");
    assert(false);
  } else {
    entries[key] = cb;
  }
}

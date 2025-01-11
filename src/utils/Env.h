#ifndef SRC_UTILS_ENV_H
#define SRC_UTILS_ENV_H

#include <cassert>
#include <optional>
#include <spdlog/common.h>
#include <stdexcept>
#include <string>
#include "Logger.h"

class Env {
  public:
    template <typename T>
    static std::optional<T> get (std::string key);
};

template <typename T>
std::optional<T> Env::get(std::string key) {
  static_assert(std::is_same<T, std::string>::value || std::is_same<T, int>::value || 
      std::is_same<T, float>::value || std::is_same<T, bool>::value, "Env::get() does not accept this type");

  const char* ret = std::getenv(key.c_str());
  if (ret == NULL) {
    return {};
  } else {
    try {
      if constexpr (std::is_same<T, int>::value) {
        return std::stoi(ret);
      } else if constexpr (std::is_same<T, std::string>::value) {
        return ret;
      } else if constexpr (std::is_same<T, float>::value) {
        return std::stof(ret);
      } else if constexpr (std::is_same<T, bool>::value) {
        std::string str = ret;
        return (str.compare("true") || str.compare("1") || str.compare("True")) ? true : false;
      } 
    } catch (std::invalid_argument& ex) {
      assert(false);
    } catch (std::out_of_range& ex) {
      assert(false);
    }
  }
}

#endif 

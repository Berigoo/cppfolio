#include "Env.h"
#include <cassert>
#include <stdexcept>

template <typename T>
std::optional<T> Env::get(std::string key) {
  const char* ret = std::getenv(key.c_str());
  if (ret == NULL) {
    return {};
  } else {
    try {
      if (std::is_same<T, int>::value) {
        return std::stoi(ret);
      } else if (std::is_same<T, std::string>::value) {
        return ret;
      } else if (std::is_same<T, float>::value) {
        return std::stof(ret);
      } else if (std::is_same<T, bool>::value) {
        std::string str = ret;
        return (str.compare("true") || str.compare("1") || str.compare("True")) ? true : false;
      } else {
        static_assert(false, "Env::get() does not accept this type");
      }
    } catch (std::invalid_argument& ex) {
      assert(false);
    } catch (std::out_of_range& ex) {
      assert(false);
    }
  }
}

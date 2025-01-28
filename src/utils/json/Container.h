#ifndef SRC_UTILS_JSON_CONTAINER_H
#define SRC_UTILS_JSON_CONTAINER_H

#include "nlohmann/json.hpp"
#include <functional>
#include <iostream>
#include <vector>
#include "../Logger.h"

//TODO switch to map
template<typename T>
class Container : public std::vector<T> {
  public:
    const Container<T> get(std::function<bool(const T&)> cb = nullptr);
    const std::optional<T> find(int id);
    void json(nlohmann::json& out);
};


template<typename T>
const Container<T> Container<T>::get(std::function<bool(const T&)> cb) {
  Container<T> ret;
  auto it = this->begin();
      /*Logger::getInstance()->logger->info("size {}", this->size());*/
  if (cb) {
    while (it != this->end()) {
      if (cb(*it)) {
        ret.push_back(*it);
      }
      ++it;
    }
  }else {
    return *this;
  }

  return ret;
}

template<typename T>
void Container<T>::json(nlohmann::json& out) {
  auto it = this->begin();

  int count = 0;
  while (it != this->end()) {
    out.push_back(*it);
    ++it;
  }
}

template<typename T>
const std::optional<T> Container<T>::find(int id) {
  auto it = this->begin();

  while (it != this->end()) {
    if ((*it)["id"] == id) {
      return *it;
    }
    ++it;
  }

  return {};
}

#endif //SRC_UTILS_JSON_CONTAINER_H

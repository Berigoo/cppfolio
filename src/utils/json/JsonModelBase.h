#ifndef SRC_UTILS_JSON_JSONMODELBASE_H
#define SRC_UTILS_JSON_JSONMODELBASE_H

#include "nlohmann/detail/input/parser.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <type_traits>

enum FIELD_OPT {
  NONE      = 0x00,
  REQUIRED  = 0x01
};

struct Field {
  const char* key;
  unsigned int opt = 0;

};

class JsonModelBase {
  public:
    template<typename KeyType>
      nlohmann::json& operator[](KeyType&& key);
    template<typename T, typename InputType>
    static JsonModelBase parse(InputType&& i, const bool allow_exception = true,
        const bool ignore_comments = false);

    void operator=(nlohmann::json&& val);
    void operator=(nlohmann::json& val);
    operator std::string() const;

  protected:
    JsonModelBase() = default;

    nlohmann::json json;
    std::vector<Field> constraints;

    void setConstraints(std::vector<Field>&& constraints);

  private:
    //TODO is it effecient ?
    bool cb(int depth, nlohmann::detail::parse_event_t event,
        nlohmann::json& parsed);
};

template<typename KeyType>
nlohmann::json& JsonModelBase::operator[](KeyType&& key) {
  return json[key];
}

template<typename T, typename InputType>
JsonModelBase JsonModelBase::parse(InputType&& i, const bool allow_exception,
    const bool ignore_comments) {
  static_assert(std::is_base_of_v<JsonModelBase, T>);

  T result;
  JsonModelBase& cast = dynamic_cast<JsonModelBase&>(result);
  cast.json = nlohmann::json::parse(i, [&](int depth, nlohmann::detail::parse_event_t event,
        nlohmann::json& parsed){
      if (event == nlohmann::json::parse_event_t::key) {
        for(const auto& constraint : cast.constraints) {
          if (nlohmann::json(constraint.key) == parsed) {
            return true;
          }
        }
        return false;
      }
      return true;
      }, allow_exception, ignore_comments);

  //TODO is it effecient ?
  for (const auto& constraint : cast.constraints) {
    if ((constraint.opt & REQUIRED) != 0) {
      assert(cast.json.contains(constraint.key)); //TODO 
    }
  }

  return result;
}

#endif //SRC_UTILS_JSON_JSONMODELBASE_H

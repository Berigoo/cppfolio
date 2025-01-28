#ifndef SRC_UTILS_JSON_JSONMODELBASE_H
#define SRC_UTILS_JSON_JSONMODELBASE_H

#include "Container.h"
#include "nlohmann/detail/input/parser.hpp"
#include "nlohmann/detail/json_custom_base_class.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <type_traits>
#include <vector>

enum FIELD_OPT {
  NONE      = 0x00,
  REQUIRED  = 0x01
};

struct Field {
  const char* key;
  unsigned int opt = 0;

};

//TODO derive from json_basic class 
class JsonModelBase : public nlohmann::basic_json<> {
  public:
    virtual ~JsonModelBase() = default;

    template<typename T, typename InputType>
    static T parse(InputType&& i, const bool allow_exception = true,
        const bool ignore_comments = false);
    template<typename T, typename InputType>
      static Container<T> parseArray(InputType&& i, const bool allow_exception = true,
          const bool ignore_comments = false);

  protected:
    JsonModelBase() = default;

    static std::vector<Field> constraints();

  private:
    //TODO is it effecient ?
    bool cb(int depth, nlohmann::detail::parse_event_t event,
        nlohmann::json& parsed);
};

template<typename T, typename InputType>
T JsonModelBase::parse(InputType&& i, const bool allow_exception,
    const bool ignore_comments) {
  static_assert(std::is_base_of_v<JsonModelBase, T>);

  parser_callback_t f = nullptr;
  if (T::constraints().size() > 0) {
    f = [&](int depth, nlohmann::detail::parse_event_t event,
        nlohmann::json& parsed){
      if (event == nlohmann::json::parse_event_t::key) {
        for(const auto& constraint : T::constraints()) {
          if (nlohmann::json(constraint.key) == parsed) {
            return true;
          }
        }
        return false;
      }
      return true;
    };
  }

  T result;
  result.update(nlohmann::json::parse(i, std::move(f), allow_exception, ignore_comments));

  //TODO is it effecient ?
  for (const auto& constraint : result.constraints()) {
    if ((constraint.opt & REQUIRED) != 0) {
      assert(result.contains(constraint.key)); //TODO 
    }
  }

  return result;
}

//TODO nested object parse
template<typename T, typename InputType>
Container<T> JsonModelBase::parseArray(InputType&& i, const bool allow_exception,
    const bool ignore_comments) {
  static_assert(std::is_base_of_v<JsonModelBase, T>);

  Container<T> cont;
  parser_callback_t f = nullptr;
  if (T::constraints().size() > 0) {
    f = [&](int depth, nlohmann::detail::parse_event_t event,
        nlohmann::json& parsed){
      if (event == nlohmann::json::parse_event_t::key) {
        for(const auto& constraint : T::constraints()) {
          if (nlohmann::json(constraint.key) == parsed) {
            return true;
          }
        }
        return false;
      } else if (event == nlohmann::json::parse_event_t::object_end) {
        //TODO is it effecient ?
        for (const auto& constraint : T::constraints()) {
          if ((constraint.opt & REQUIRED) != 0) {
            assert(parsed.contains(constraint.key)); //TODO 
          }
        }
        T entry;
        entry.update(parsed);
        cont.push_back(entry);
        return true;
      }
      return true;
    };
  }

  nlohmann::json::parse(i, std::move(f), allow_exception, ignore_comments);
  return cont;
}

#endif //SRC_UTILS_JSON_JSONMODELBASE_H

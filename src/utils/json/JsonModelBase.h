#ifndef SRC_UTILS_JSON_JSONMODELBASE_H
#define SRC_UTILS_JSON_JSONMODELBASE_H

#include "Container.h"
#include "nlohmann/detail/input/parser.hpp"
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

template<typename Child>
class JsonModelBase : public nlohmann::basic_json<> {
  public:
    template<typename InputType>
      static Child parse(InputType&& i, const bool allow_exception = true,
          const bool ignore_comments = false);
    template<typename InputType>
      static Container<Child> parseArray(InputType&& i, const bool allow_exception = true,
          const bool ignore_comments = false);

  protected:
    JsonModelBase() = default;

    static std::vector<Field> constraints;
};

template<typename Child>
template<typename InputType>
Child JsonModelBase<Child>::parse(InputType&& i, const bool allow_exception,
    const bool ignore_comments) {
  static_assert(std::is_base_of_v<JsonModelBase, Child>);

  Child res;
  parser_callback_t f = nullptr;
  if (Child::constraints.size() > 0) {
    f = [&](int depth, nlohmann::detail::parse_event_t event,
        nlohmann::json& parsed){
      if (event == nlohmann::json::parse_event_t::key) {
        for(const auto& constraint : Child::constraints) {  //TODO around O(n_key*n_constrains)
          if (nlohmann::json(constraint.key) == parsed) {
            return true;
          }
        }
        return false;
      }
      return true;
    };
  }

  Child result;
  result.update(nlohmann::json::parse(i, std::move(f), allow_exception, ignore_comments));

  for (const auto& constraint : result.constraints) {
    if ((constraint.opt & REQUIRED) != 0) {
      assert(result.contains(constraint.key)); //TODO throw error | callback
    }
  }

  return result;
}

//TODO nested object parse
template<typename Child>
template<typename InputType>
Container<Child> JsonModelBase<Child>::parseArray(InputType&& i, const bool allow_exception,
    const bool ignore_comments) {
  static_assert(std::is_base_of_v<JsonModelBase, Child>);

  Container<Child> cont;
  parser_callback_t f = nullptr;
  if (Child::constraints.size() > 0) {
    f = [&](int depth, nlohmann::detail::parse_event_t event,
        nlohmann::json& parsed){
      if (event == nlohmann::json::parse_event_t::key) {
        for(const auto& constraint : Child::constraints) {
          if (nlohmann::json(constraint.key) == parsed) {
            return true;
          }
        }
        return false;
      } else if (event == nlohmann::json::parse_event_t::object_end) {
        //TODO what if nested obj
        for (const auto& constraint : Child::constraints) {
          if ((constraint.opt & REQUIRED) != 0) {
            assert(parsed.contains(constraint.key)); //TODO throw error | callback
          }
        }
        Child entry;
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

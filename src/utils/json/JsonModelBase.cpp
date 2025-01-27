#include "JsonModelBase.h"
/**/
/*JsonModelBase::JsonModelBase(const value_t v) : nlohmann::json(v) {};*/
/*JsonModelBase::JsonModelBase(iterator first, iterator last) : nlohmann::json(first, last) {};*/
/*JsonModelBase::JsonModelBase(const_iterator first, const_iterator last) : nlohmann::json(first, last) {};*/
/*JsonModelBase::JsonModelBase(const basic_json& other) : nlohmann::json(other) {};*/
/*JsonModelBase::JsonModelBase(basic_json&& other) noexcept : nlohmann::json(other) {};*/

void JsonModelBase::operator=(nlohmann::json&& val) {
  json = val;
}

void JsonModelBase::operator=(nlohmann::json& val) {
  json = val;
}

JsonModelBase::operator std::string() const {
  return json;
}

bool JsonModelBase::cb(int depth, nlohmann::detail::parse_event_t event,
    nlohmann::json& parsed) {
  if (event == nlohmann::json::parse_event_t::key) {
    for(const auto& constraint : constraints) {
      if (nlohmann::json(constraint.key) == parsed) {
        return true;
      }
    }
    return false;
  }
  return true;
}

void JsonModelBase::setConstraints(std::vector<Field>&& constraints) {
  this->constraints = constraints;
}

#include "Views.h"

template<>
std::vector<Field> JsonModelBase<Views>::constraints = {
  {"id", REQUIRED},
  {"title", REQUIRED},
  {"path", REQUIRED},
  {"tags", NONE},
  {"date", REQUIRED},
};

void Views::update(const_reference j, bool merge_objects) {
  this->JsonModelBase<Views>::update(j, merge_objects);
  std::stringstream ss;
  std::ifstream file((*this)["path"]);
  assert(file.is_open());                  //TODO
  ss << file.rdbuf();
  content = ss.str();
  file.close();
}

const char* Views::getContent() {
  return content.c_str();
}

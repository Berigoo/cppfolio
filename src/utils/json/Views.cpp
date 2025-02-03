#include "Views.h"

template<>
std::vector<Field> JsonModelBase<Views>::constraints = {
  {"id", REQUIRED},
  {"title", REQUIRED},
  {"path", REQUIRED},
  {"tags", NONE},
  {"date", REQUIRED},
};

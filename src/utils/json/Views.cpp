#include "Views.h"

std::vector<Field> Views::constraints() {
  return {
    {"id", REQUIRED},
    {"title", REQUIRED},
    {"path", REQUIRED},
    {"tags", NONE},
    {"date", REQUIRED},
  };
}

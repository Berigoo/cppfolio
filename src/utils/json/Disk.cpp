#include "Disk.h"

std::vector<Field> Disk::constraints() {
  return {
    {"path", REQUIRED},
    {"name", REQUIRED}
  };
}

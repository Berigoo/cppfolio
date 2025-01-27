#include "Disk.h"

Disk::Disk() : JsonModelBase() {
  setConstraints({
      {"path", REQUIRED},
      {"name", REQUIRED}
      });
}

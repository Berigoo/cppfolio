#include "Disk.h"

//TODO rework flow
Disk::Disk() : JsonModelBase() {
  setConstraints({
      {"path", REQUIRED},
      {"name", REQUIRED}
      });
}

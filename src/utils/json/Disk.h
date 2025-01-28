#ifndef SRC_UTILS_JSON_DISK_H
#define SRC_UTILS_JSON_DISK_H

#include "JsonModelBase.h"

class Disk : public JsonModelBase {
  public:
    Disk() = default;

    static std::vector<Field> constraints();
};

#endif 

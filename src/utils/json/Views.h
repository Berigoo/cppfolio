#ifndef SRC_UTILS_JSON_VIEWS_H
#define SRC_UTILS_JSON_VIEWS_H

#include "JsonModelBase.h"

class Views : public JsonModelBase {
  public:
    Views() = default;

    static std::vector<Field> constraints();
};


#endif //SRC_UTILS_JSON_VIEWS_H

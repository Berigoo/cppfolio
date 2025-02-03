#ifndef SRC_UTILS_JSON_VIEWS_H
#define SRC_UTILS_JSON_VIEWS_H

#include "JsonModelBase.h"
#include "inja/inja.hpp"

class Views final: public JsonModelBase<Views> {
  public:
    Views() = default;

    void update(const_reference j, bool merge_objects=false);
    const char* getContent();

  private:
    std::string content;
};


#endif //SRC_UTILS_JSON_VIEWS_H

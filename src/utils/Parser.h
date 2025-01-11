#ifndef SRC_UTILS_PARSER_H
#define SRC_UTILS_PARSER_H

#include <inja/inja.hpp>

class Parser {
  private:
    Parser () = default;
  public:
    static std::string parse(std::string path, inja::json data=nullptr);
};

#endif 

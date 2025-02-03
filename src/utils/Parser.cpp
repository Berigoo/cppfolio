#include "Parser.h"

static inja::Environment env = {};

//TODO in-memory template
std::string Parser::parse (std::string path, inja::json data) {
  return env.render(env.parse_template(path), data); 
}

#include "Parser.h"

static inja::Environment env = {};

std::string Parser::parse (std::string path, inja::json data) {
  return env.render(env.parse_template(path), data);
}

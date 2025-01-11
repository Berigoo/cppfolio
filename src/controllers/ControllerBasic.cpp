#include "ControllerBasic.h"

static void view (const httplib::Request& req, httplib::Response& res);

ControllerBasic::ControllerBasic () {
  registerCallback("view", view);
}

void view (const httplib::Request& req, httplib::Response& res) {
  res.set_content(Parser::parse(Path::relative("src/views/index.html")), "text/html");
}

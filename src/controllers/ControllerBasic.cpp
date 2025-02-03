#include "ControllerBasic.h"

static void view (const httplib::Request& req, httplib::Response& res);

static std::string sIndexContent;

ControllerBasic::ControllerBasic () {
  std::ifstream file(Path::relative("src/views/index.html"));
  assert(file.is_open());       //TODO
  std::stringstream ss;
  ss << file.rdbuf();
  sIndexContent = ss.str();

  registerCallback("view", view);
}

void view (const httplib::Request& req, httplib::Response& res) {
  res.set_content(sIndexContent, "text/html");
}

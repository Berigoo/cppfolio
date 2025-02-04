#include "Router.h"
#include <spdlog/common.h>

bool Router::isConstructed = false;

Router::Router () {
  assert(!isConstructed);

  Server::GET("/", (Controller::Instance<ControllerBasic>())->handleBy("view"));

  Server::GET(R"(/blog(:?/)?)", (Controller::Instance<ControllerBlog>())->handleBy("view"));
  Server::GET(R"(/blog/(\d+))", (Controller::Instance<ControllerBlog>())->handleBy("get"));

  isConstructed = true;
}

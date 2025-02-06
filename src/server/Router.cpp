#include "Router.h"
#include <spdlog/common.h>

bool Router::isConstructed = false;

Router::Router () {
  assert(!isConstructed);

  Server::GET("/", (Controller::Instance<ControllerBasic>())->handleBy("view"));

  Server::GET(R"(/blog(:?/)?)", (Controller::Instance<ControllerBlog>())->handleBy("view"));
  Server::GET(R"(/blog/(\d{1,3}))", (Controller::Instance<ControllerBlog>())->handleBy("get"));

  isConstructed = true;
}

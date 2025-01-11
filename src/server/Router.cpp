#include "Router.h"
#include <spdlog/common.h>

bool Router::isConstructed = false;

Router::Router () {
  assert(!isConstructed);

  Server::GET("/", (Controller::Instance<ControllerBasic>())->handleBy("view"));
  isConstructed = true;
}

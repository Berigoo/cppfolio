#include "Router.h"

Router::Router () {
  assert(!isConstructed);

  Server::GET("/", (Controller::Instance<ControllerBasic>())->handleBy("view"));
  isConstructed = true;
}

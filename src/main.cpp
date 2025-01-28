#include "server/Router.h"
#include "server/Server.h"

int main () {
  Server::setup();

  Router route;

  Server::listen();
}

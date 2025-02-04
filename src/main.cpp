#include "server/Router.h"
#include "server/Server.h"

int main () {
  Server::setup(); //TODO add routes

  Router route;

  Server::listen();
}

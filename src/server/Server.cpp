#include "Server.h"

bool Server::isStarted = false;

Server::Server () {
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  std::optional<std::string> crt = Env::get<std::string>("SERVER_SSL_CERT");
  std::optional<std::string> key = Env::get<std::string>("SERVER_SSL_KEY");
  assert(crt.has_value() && key.has_value());

  server = std::make_unique<httplib::SSLServer>(crt, key);
#else 
  server = std::make_unique<httplib::Server>();
#endif 
}

void Server::routeGET (std::string& pattern, std::function<void(const httplib::Request&, httplib::Response&)> cb){
  server->Get(pattern, cb);
}

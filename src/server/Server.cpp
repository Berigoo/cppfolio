#include "Server.h"

static bool isInitialized = false;
static bool isStarted = false;

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  std::unique_ptr<httplib::SSLServer> server; 
#else 
  std::unique_ptr<httplib::Server> server;
#endif 


void Server::setup () {
  assert(!isInitialized);
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  std::optional<std::string> crt = Env::get<std::string>("SERVER_SSL_CERT");
  std::optional<std::string> key = Env::get<std::string>("SERVER_SSL_KEY");
  assert(crt.has_value() && key.has_value());

  server = std::make_unique<httplib::SSLServer>(crt.value(), key.value());
#else 
  server = std::make_unique<httplib::Server>();
#endif 
  
  server->set_mount_point("/public", Path::relative("public"));

  isInitialized = true;
}

//TODO multithread
void Server::listen () {
  assert(isInitialized);
  if (!isStarted) {
    std::optional<std::string> host = Env::get<std::string>("SERVER_HOST");
    std::optional<int> port = Env::get<int>("SERVER_PORT");
    assert(host.has_value() && port.has_value());

    isStarted = true;
    Logger::getInstance()->logger->log(spdlog::level::info, "Server on: {}{}:{}", 
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
        "https://"       
#else
        "http://"
#endif 
        , host.value(), port.value());

    server->listen(host.value(), port.value());
  }
}

void Server::GET (std::string pattern, std::function<void(const httplib::Request&, httplib::Response&)> cb){
  assert(isInitialized);
  server->Get(pattern, cb);
}

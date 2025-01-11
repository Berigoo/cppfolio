#ifndef SRC_SERVER_SERVER_H
#define SRC_SERVER_SERVER_H

#include <httplib.h>
#include <optional>
#include "../utils/Env.h"
#include "../utils/Logger.h"

class Server {
  protected:
    Server ();

  public:
    static void setup ();
    static void listen ();
    static void GET (std::string pattern, std::function<void(const httplib::Request&, httplib::Response&)> cb);
};

#endif //SRC_SERVER_SERVER_H

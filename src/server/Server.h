#ifndef SRC_SERVER_SERVER_H
#define SRC_SERVER_SERVER_H

#include <httplib.h>
#include <optional>
#include "../utils/Env.h"
#include "../utils/Logger.h"
#include "../utils/Path.h"
#include "../utils/json/Disk.h"
#include "../utils/json/Views.h"
#include "inja/inja.hpp"

class Server {
  protected:
    Server ();

  public:
    static void setup ();
    static void listen ();
    static void GET (std::string pattern, std::function<void(const httplib::Request&, httplib::Response&)> cb);
};

#endif //SRC_SERVER_SERVER_H

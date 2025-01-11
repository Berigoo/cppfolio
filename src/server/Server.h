#include <httplib.h>
#include "../utils/Env.h"

class Server {
  private:
    static bool isStarted;
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    std::unique_ptr<httplib::SSLServer> server;
#else
    std::unique_ptr<httplib::Server> server;
#endif
  protected:
    Server ();

  public:
    static Server& getInstance ();
    void routeGET (std::string& pattern, std::function<void(const httplib::Request&, httplib::Response&)> cb);
};

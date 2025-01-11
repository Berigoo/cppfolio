#include <functional>
#include <unordered_map>
#include <httplib.h>
#include "../utils/Logger.h"

class Controller {
  private:
    static void defaultResponse (const httplib::Request& req, httplib::Response& res);

  protected:
    Controller () = default;

    static std::unordered_map<std::string, std::function<void(const httplib::Request&, httplib::Response&)>> entries;
    
    virtual void setup () = 0;

  public:
    static std::function<void(const httplib::Request&, httplib::Response&)> handle (std::string key);
};

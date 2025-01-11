#ifndef SRC_CONTROLLERS_CONTROLLER_H
#define SRC_CONTROLLERS_CONTROLLER_H

#include <functional>
#include <unordered_map>
#include <httplib.h>
#include <inja/inja.hpp>
#include "../utils/Logger.h"
#include "../utils/Parser.h"
#include "../utils/Path.h"

class Controller {
  private:
    static void defaultResponse (const httplib::Request& req, httplib::Response& res);

  protected:
    Controller () = default;
    virtual ~Controller () = default;

    std::unordered_map<std::string, std::function<void(const httplib::Request&, httplib::Response&)>> entries;

    
    void registerCallback (std::string key, std::function<void(const httplib::Request& req, httplib::Response& res)>);
  public:
    std::function<void(const httplib::Request&, httplib::Response&)> handleBy (std::string key);

    template <typename T>
    static T* Instance ();
};

template <typename T>
T* Controller::Instance () {
  static_assert(std::is_base_of_v<Controller, T>);
  static T instance;
  return &instance;
}

#endif 

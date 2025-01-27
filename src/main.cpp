#include "server/Router.h"
#include "server/Server.h"
#include "utils/json/Disk.h"

int main () {
  std::ifstream file(Path::relative("src/config/disk.json"));
  assert(file);

  std::stringstream ss;
  ss << file.rdbuf();

  nlohmann::json data = {
    {"base_path", Path::relative(".")}
  };
  
  std::string s = inja::render(ss.str(), data);

  Logger::getInstance()->logger->info(s);
  auto disks = JsonModelBase::parse<Disk>(s);
  std::cout << std::setw(4) << disks["path"] << '\n';

  Server::setup();

  Router route;

  Server::listen();
}

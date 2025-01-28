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
  
  std::stringstream os;
  inja::render_to(os, ss.str(), data);

  auto disksArr = JsonModelBase::parseArray<Disk>(os);
  std::cout << disksArr.size() << '\n';
  for (auto const& disk : disksArr) {
    std::cout << std::setw(4) << disk << '\n';
  }

  Server::setup();

  Router route;

  Server::listen();
}

#include "Path.h"
static const std::string TAG = "PATH";


std::filesystem::path Path::root = PROJECT_ROOT;

std::string Path::relative (std::string path) {
  Logger::getInstance()->logger->log(spdlog::level::debug, "root: {}", root.c_str());
  Logger::getInstance()->logger->log(spdlog::level::debug, "path: {}", path.c_str());
  std::filesystem::path p = root / path;
  std::string rel = std::filesystem::relative(p, std::filesystem::current_path());
  //TODO
  assert(rel.compare(""));

  return rel;
}

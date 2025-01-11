#include "Logger.h"

Logger::Logger () {
  std::filesystem::path logFile = PROJECT_ROOT;
  logFile = logFile / "storage/logs/default.log";
  if (!std::filesystem::exists(logFile)) {
    std::ofstream file{logFile};
    file.close();
  }

  // to console & file
  logger = std::make_shared<spdlog::logger>("logger");
  logger->sinks().push_back(
      std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
      );
  logger->sinks().push_back(
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile.c_str())
      );
#ifdef NDEBUG
  logger->set_level(spdlog::level::warn);
#else 
  logger->set_level(spdlog::level::trace);
#endif
}

Logger* Logger::getInstance() {
  static Logger instance;

  return &instance;
}

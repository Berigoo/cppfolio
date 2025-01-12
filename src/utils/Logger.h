#ifndef SRC_UTILS_LOGGER_H
#define SRC_UTILS_LOGGER_H

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include <fstream>
#include "Path.h"

class Logger {
  protected:
    Logger ();

  public:
    std::shared_ptr<spdlog::logger> logger;

    static Logger* getInstance ();
};

#endif //SRC_UTILS_LOGGER_H

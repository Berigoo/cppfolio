#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

class Logger {
  protected:
    Logger ();

  public:
    std::shared_ptr<spdlog::logger> logger;

    static Logger* getInstance ();
};


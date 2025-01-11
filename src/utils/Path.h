#include <filesystem>
#include "Logger.h"

namespace fs = std::filesystem;

class Path {
  protected:
    Path () = default;

    static fs::path root;

  public:
    /**
     * @brief get relative path from where program executed to specified path
     *
     * @param path target path
     */
    static std::string relative (std::string path);
};

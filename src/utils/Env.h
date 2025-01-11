#include <optional>
#include <string>

class Env {
  public:
    template <typename T>
    static std::optional<T> get (std::string key);
};

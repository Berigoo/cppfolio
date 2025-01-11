#include "utils/Path.h"
#include <iostream>

int main () {
  std::cout << "Current path: " << Path::relative("src/models") << '\n';
}

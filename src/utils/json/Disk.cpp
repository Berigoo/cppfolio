#include "Disk.h"

template<>
std::vector<Field> JsonModelBase<Disk>::constraints = {
    {"path", REQUIRED},
    {"name", REQUIRED}
};

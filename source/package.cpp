#include "package.h"
#include <cstdio>
#include <sys/stat.h>

namespace upgrades {
bool Package::validate(const Upgrade& upgrade, const std::string& path) {
    if (upgrade.titleId.size() != 16) return false;
    struct stat st{};
    if (stat(path.c_str(), &st) != 0 || st.st_size <= 0) return false;
    return true;
}
}

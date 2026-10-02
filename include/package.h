#pragma once
#include "upgrade_types.h"
#include <string>

namespace upgrades {
class Package {
public:
    static bool validate(const Upgrade& upgrade, const std::string& path);
};
}

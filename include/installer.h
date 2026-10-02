#pragma once
#include "upgrade_types.h"
#include <string>

namespace upgrades {
class Installer {
public:
    InstallResult install(const Upgrade& upgrade, const std::string& stagedPath);
};
}

#pragma once
#include "upgrade_types.h"
#include <string>
#include <vector>

namespace upgrades {
class Catalog {
public:
    bool load(const std::string& path);
    bool loadLocalUpgrades(const std::string& root);
    const std::vector<Upgrade>& entries() const { return entries_; }
private:
    std::vector<Upgrade> entries_;
};
}

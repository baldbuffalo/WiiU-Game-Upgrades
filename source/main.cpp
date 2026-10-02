#include <whb/proc.h>
#include <whb/log.h>
#include <whb/sdcard.h>
#include <cstdio>
#include "catalog.h"

int main(int, char**) {
    WHBProcInit();
    WHBLogCafeInit();
    WHBLogPrintf("[WUGU] WiiU Game Upgrades starting");

    const std::string upgradeRoot = "sd:/wiiu/apps/WiiUGameUpgrades/upgrades";
    upgrades::Catalog catalog;

    if (!WHBMountSdCard()) {
        WHBLogPrintf("[WUGU] SD card mount failed");
    } else if (!catalog.loadLocalUpgrades(upgradeRoot)) {
        WHBLogPrintf("[WUGU] upgrades directory not found: %s", upgradeRoot.c_str());
    } else {
        WHBLogPrintf("[WUGU] detected %u local upgrade(s)",
                     static_cast<unsigned>(catalog.entries().size()));

        for (const auto& upgrade : catalog.entries()) {
            WHBLogPrintf("[WUGU] upgrade: %s | title=%s | version=%s | package=%s",
                         upgrade.name.c_str(),
                         upgrade.titleId.c_str(),
                         upgrade.version.c_str(),
                         upgrade.packageUrl.c_str());
        }
    }

    WHBLogPrintf("[WUGU] automatic upgrade-file detection initialized");

    while (WHBProcIsRunning()) {
        WHBProcDrawDone();
        WHBProcWaitForShutdown();
    }

    WHBLogCafeDeinit();
    WHBProcShutdown();
    return 0;
}

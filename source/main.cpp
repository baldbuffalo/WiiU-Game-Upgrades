#include <whb/proc.h>
#include <whb/log.h>
#include <whb/sdcard.h>
#include <cstdio>
#include "catalog.h"
#include "package.h"
#include "installer.h"

int main(int, char**) {
    WHBProcInit();
    WHBLogCafeInit();
    WHBLogPrintf("[WUGU] WiiU Game Upgrades starting");

    upgrades::Catalog catalog;
    if (WHBMountSdCard() && catalog.load("sd:/wiiu/apps/WiiUGameUpgrades/catalog.json")) {
        WHBLogPrintf("[WUGU] catalog loaded: %u entries",
                     static_cast<unsigned>(catalog.entries().size()));
    } else {
        WHBLogPrintf("[WUGU] catalog not found");
    }

    WHBLogPrintf("[WUGU] application architecture initialized");

    while (WHBProcIsRunning()) {
        WHBProcDrawDone();
        WHBProcWaitForShutdown();
    }

    WHBLogCafeDeinit();
    WHBProcShutdown();
    return 0;
}

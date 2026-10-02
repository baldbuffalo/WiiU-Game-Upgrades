#include "installer.h"
#include <cstdio>

namespace upgrades {
InstallResult Installer::install(const Upgrade& upgrade, const std::string& stagedPath) {
    (void)upgrade;
    (void)stagedPath;
    std::fprintf(stderr, "[WUGU] installer backend not yet bound to an Aroma-supported persistent title mechanism\n");
    return InstallResult::InstallerUnavailable;
}
}

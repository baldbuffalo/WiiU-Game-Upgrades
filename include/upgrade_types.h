#pragma once
#include <cstdint>
#include <string>

namespace upgrades {

struct Upgrade {
    std::string id;
    std::string name;
    std::string titleId;
    std::string version;
    std::string minimumBaseVersion;
    std::string packageUrl;
    std::string sha256;
    std::string changelog;
};

enum class InstallResult {
    Success,
    InvalidPackage,
    WrongTitle,
    DownloadFailed,
    HashMismatch,
    InstallerUnavailable,
    InstallFailed
};

}

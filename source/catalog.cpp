#include "catalog.h"
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

namespace upgrades {

static std::string value(const char* object, const char* key) {
    const char* p = std::strstr(object, key);
    if (!p) return {};
    p = std::strchr(p, ':');
    if (!p) return {};
    ++p;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == '"') ++p;
    const char* end = std::strchr(p, '"');
    if (!end) return {};
    return std::string(p, end - p);
}

static bool isDirectory(const std::string& path) {
    struct stat st{};
    return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

static bool isFile(const std::string& path) {
    struct stat st{};
    return stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode) && st.st_size > 0;
}

static bool readManifest(const std::string& path, Upgrade& u) {
    FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return false;
    std::fseek(f, 0, SEEK_END);
    const long size = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    if (size <= 0 || size > 1024 * 1024) {
        std::fclose(f);
        return false;
    }

    std::string data(static_cast<size_t>(size), '\0');
    const size_t read = std::fread(data.data(), 1, data.size(), f);
    std::fclose(f);
    if (read != data.size()) return false;

    const char* p = data.c_str();
    u.id = value(p, "\"id\"");
    u.name = value(p, "\"name\"");
    u.titleId = value(p, "\"titleId\"");
    u.version = value(p, "\"version\"");
    u.minimumBaseVersion = value(p, "\"minimumBaseVersion\"");
    u.packageUrl = value(p, "\"packageUrl\"");
    u.sha256 = value(p, "\"sha256\"");
    u.changelog = value(p, "\"changelog\"");
    return !u.id.empty() && !u.titleId.empty();
}

bool Catalog::load(const std::string& path) {
    entries_.clear();
    Upgrade u;
    if (!readManifest(path, u)) return false;
    entries_.push_back(std::move(u));
    return true;
}

bool Catalog::loadLocalUpgrades(const std::string& root) {
    entries_.clear();

    DIR* dir = opendir(root.c_str());
    if (!dir) return false;

    while (dirent* entry = readdir(dir)) {
        if (entry->d_name[0] == '.') continue;

        const std::string gameDir = root + "/" + entry->d_name;
        if (!isDirectory(gameDir)) continue;

        const std::string manifest = gameDir + "/upgrade.json";
        const std::string package = gameDir + "/update.zip";

        if (!isFile(manifest) || !isFile(package)) continue;

        Upgrade u;
        if (!readManifest(manifest, u)) continue;

        // A local package is automatically selected when packageUrl is empty.
        if (u.packageUrl.empty())
            u.packageUrl = package;

        entries_.push_back(std::move(u));
    }

    closedir(dir);
    return true;
}

}

#include "catalog.h"
#include <cstdio>
#include <cstring>

namespace upgrades {

static std::string value(const char* object, const char* key) {
    const char* p = std::strstr(object, key);
    if (!p) return {};
    p = std::strchr(p, ':');
    if (!p) return {};
    ++p;
    while (*p == ' ' || *p == '\t' || *p == '"') ++p;
    const char* end = std::strchr(p, '"');
    if (!end) return {};
    return std::string(p, end - p);
}

bool Catalog::load(const std::string& path) {
    entries_.clear();
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
    std::fread(data.data(), 1, data.size(), f);
    std::fclose(f);

    const char* p = data.c_str();
    while ((p = std::strstr(p, ""id""))) {
        Upgrade u;
        u.id = value(p, ""id"");
        u.name = value(p, ""name"");
        u.titleId = value(p, ""titleId"");
        u.version = value(p, ""version"");
        u.minimumBaseVersion = value(p, ""minimumBaseVersion"");
        u.packageUrl = value(p, ""packageUrl"");
        u.sha256 = value(p, ""sha256"");
        u.changelog = value(p, ""changelog"");
        if (!u.id.empty() && !u.titleId.empty() && !u.packageUrl.empty())
            entries_.push_back(std::move(u));
        p += 4;
    }
    return true;
}

}

#include "mod/MyMod.h"

#include <filesystem>
#include <pl/Mod.hpp>

namespace clange_me {

ClangeMeMod &ClangeMeMod::instance() {
    static ClangeMeMod instance;
    return instance;
}

ClangeMeMod::ClangeMeMod()
    : mSelf(*ll::mod::NativeMod::current()) {}

bool ClangeMeMod::load() {
    auto &self = getSelf();
    self.getLogger().debug("Loading...");

    std::error_code ec;

    std::filesystem::create_directories(self.getDataDir(), ec);
    if (ec) return false;

    std::filesystem::create_directories(self.getConfigDir(), ec);
    if (ec) return false;

    mConfigFile.emplace();

    if (!mConfigFile->load()) {
        self.getLogger().warn("Failed to load config");
        return false;
    }

    mConfig = mConfigFile->value();

    self.getLogger().info("JavaCombat loaded!");
    return true;
}

bool ClangeMeMod::enable() {
    auto &self = getSelf();

    self.getLogger().debug("Enabling...");

    if (!mConfig.enabled) {
        self.getLogger().info("JavaCombat disabled");
        return true;
    }

    self.getLogger().info("JavaCombat enabled!");
    self.getLogger().info("Combat mode: {}", mConfig.combat_mode);

    return true;
}

bool ClangeMeMod::disable() {
    getSelf().getLogger().debug("Disabling...");
    return true;
}

bool ClangeMeMod::unload() {
    getSelf().getLogger().debug("Unloading...");
    mConfigFile.reset();
    return true;
}

} // namespace clange_me

#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace clange_me {

struct ModConfig {
    int version = 1;
    bool enabled = true;
    bool debug = false;
    bool combat_mode = true;
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace clange_me

template <> struct pl::config::Schema<clange_me::ModConfig> {
    static constexpr std::string_view title = "JavaCombat Config";
    static constexpr std::string_view description = "JavaCombat settings.";

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};
        if (name == "enabled")
            return {.title = "Enabled"};
        if (name == "debug")
            return {.title = "Debug"};
        if (name == "combat_mode")
            return {.title = "Combat Mode"};
        return {};
    }
};

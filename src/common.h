#ifndef COMMON_H
#define COMMON_H

constexpr char kPluginName[] = "switch-graphics-card";
constexpr char kPluginStateKey[] = "enable";

constexpr char kGSettingsSchemaId[] = "com.deepin.dde.dock.module.switch-graphics-card";
constexpr char kGSettingsSchemaPath[] = "/com/deepin/dde/dock/module/switch-graphics-card/";
constexpr char kGSettingsSchemaKeyMenuEnable[] = "menuEnable";

constexpr char kIntelIconName[] = "intel";
constexpr char kNvidiaIconName[] = "nvidia";
constexpr char kDefaultIconName[] = "gpu-indicator";

#endif // COMMON_H

#ifndef SWITCHGRAPHICSCARDPLUGIN_H
#define SWITCHGRAPHICSCARDPLUGIN_H

#include "pluginsiteminterface.h"

#include "switchgraphicscardwidget.h"
#include "switchgraphicscardappletwidget.h"

#include <QGSettings>

namespace Dock {
class TipsWidget;
}

class SwitchGraphicsCardPlugin : public QObject
    , PluginsItemInterface
{
    Q_OBJECT

    // 声明实现了的接口
    Q_INTERFACES(PluginsItemInterface)
    // 插件元数据
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "switch-graphics-card.json")

public:
    explicit SwitchGraphicsCardPlugin(QObject *parent = nullptr);
    ~SwitchGraphicsCardPlugin() override;

    // 返回插件的名称，必须是唯一值，不可以和其它插件冲突
    const QString pluginName() const override;
    const QString pluginDisplayName() const override;

    // 插件初始化函数
    void init(PluginProxyInterface *proxyInter) override;

    // 控制插件启用或禁用
    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;

    // 返回插件的 widget
    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    // 右键菜单
    const QString itemContextMenu(const QString &itemKey) override;
    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;

    // dock 栏显示模式改变
    void displayModeChanged(const Dock::DisplayMode displayMode) override;

    // dock 栏插件排序
    int itemSortKey(const QString &itemKey) override;
    void setSortKey(const QString &itemKey, const int order) override;

    // 插件状态改变（启用或禁用）
    void pluginSettingsChanged() override;

private:
    void loadPlugin();
    void refreshPluginItemsVisible();
    void updateTranslator();

private slots:
    void slotGSettingsChanged(const QString &key);

private:
    QTranslator *m_translator = nullptr;
    QGSettings *m_gsettings = nullptr;

    SwitchGraphicsCardWidget *m_pluginWidget = nullptr;
    Dock::TipsWidget *m_tipsWidget = nullptr;
    SwitchGraphicsCardAppletWidget *m_appletWidget = nullptr;

    bool m_pluginLoaded = false;
};

#endif // SWITCHGRAPHICSCARDPLUGIN_H

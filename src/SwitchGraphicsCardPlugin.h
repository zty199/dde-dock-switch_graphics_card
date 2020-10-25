#ifndef SWITCHCARD_H
#define SWITCHCARD_H

#include "ddeUtil.h"
#include <dde-dock/pluginsiteminterface.h>

#include "SwitchGraphicsCardWidget.h"
#include "SwitchGraphicsCardAppletWidget.h"

class SwitchGraphicsCardPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    // 声明实现了的接口
    Q_INTERFACES(PluginsItemInterface)
    // 插件元数据
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "SwitchGraphicsCardPlugin.json")

public:
    explicit SwitchGraphicsCardPlugin(QObject *parent = nullptr);

    // 返回插件的名称，必须是唯一值，不可以和其它插件冲突
    const QString pluginName() const override;
    const QString pluginDisplayName() const override;

    // 插件初始化函数
    void init(PluginProxyInterface *proxyInter) override;

    // 返回插件的 widget
    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    // 控制插件启用和禁用
    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;

    // 右键菜单
    const QString itemContextMenu(const QString &itemKey) override;
    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;

private:
    QLabel *m_tipsWidget;
    SwitchGraphicsCardWidget *m_pluginWidget;
    SwitchGraphicsCardAppletWidget *m_appletWidget;

};

#endif // HOMEMONITORPLUGIN_H

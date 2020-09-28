#include "SwitchGraphicsCardPlugin.h"

SwitchGraphicsCardPlugin::SwitchGraphicsCardPlugin(QObject *parent)
    : QObject(parent)
{

}

const QString SwitchGraphicsCardPlugin::pluginName() const
{
    return QStringLiteral("switch-graphics-card");
}

const QString SwitchGraphicsCardPlugin::pluginDisplayName() const
{
    if(m_appletWidget->getLocale() == "zh")
        return QString("显卡切换");
    else
        return QString("Switch Graphics Card");
}

void SwitchGraphicsCardPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_pluginWidget = new SwitchGraphicsCardWidget;
    m_tipsWidget = new QLabel;
    m_appletWidget = new SwitchGraphicsCardAppletWidget;

    // 如果插件没有被禁用则在初始化插件时才添加主控件到面板上
    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, pluginName());

        // 初始化显卡信息和系统语言环境
        m_appletWidget->setCardName();
        m_appletWidget->setLocale();
        m_appletWidget->refreshButton();
        m_pluginWidget->getInfo(m_appletWidget);
    }
}

// dock栏插件显示
QWidget *SwitchGraphicsCardPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // 这里暂时返回空指针，这意味着插件会被 dde-dock 加载
    // 但是不会有任何东西被添加到 dde-dock 上
    return this->m_pluginWidget;
}

// 鼠标悬停时显示信息
QWidget *SwitchGraphicsCardPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // 设置/刷新 tips 中的信息
    if(m_appletWidget->getLocale() == "zh")
        m_tipsWidget->setText("当前显卡：" + m_appletWidget->getCardName());
    else
        m_tipsWidget->setText("Current: " + m_appletWidget->getCardName());

    return this->m_tipsWidget;
}

// 单击插件弹出选项框
QWidget *SwitchGraphicsCardPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return this->m_appletWidget;
}

bool SwitchGraphicsCardPlugin::pluginIsAllowDisable()
{
    // 通知 dde-dock 本插件允许禁用
    return true;
}

bool SwitchGraphicsCardPlugin::pluginIsDisable()
{
    // 第二个参数 “disabled” 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认不禁用
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void SwitchGraphicsCardPlugin::pluginStateSwitched()
{
    // 获取当前禁用状态的反值作为新的状态值
    const bool disabledNew = !pluginIsDisable();
    // 存储新的状态值
    m_proxyInter->saveValue(this, "disabled", disabledNew);

    // 根据新的禁用状态值处理主控件的加载和卸载
    if (disabledNew) {
        m_proxyInter->itemRemoved(this, pluginName());
    } else {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

const QString SwitchGraphicsCardPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(3);

    QMap<QString, QVariant> refresh;
    refresh["itemId"] = "refresh";
    if(m_appletWidget->getLocale() == "zh")
        refresh["itemText"] = "刷新";
    else
        refresh["itemText"] = "Refresh";
    refresh["isActive"] = true;
    items.push_back(refresh);

    QMap<QString, QVariant> setting;
    setting["itemId"] = "setting";
    if(m_appletWidget->getLocale() == "zh")
        setting["itemText"] = "显示器设置";
    else
        setting["itemText"] = "Display Settings";
    setting["isActive"] = true;
    items.push_back(setting);

    QMap<QString, QVariant> nvidia;
    nvidia["itemId"] = "nvidia";
    if(m_appletWidget->getLocale() == "zh")
        nvidia["itemText"] = "NVIDIA 显卡设置";
    else
        nvidia["itemText"] = "Run nvidia-settings";
    nvidia["isActive"] = true;
    items.push_back(nvidia);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void SwitchGraphicsCardPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);

    // 根据上面接口设置的 id 执行不同的操作
    if (menuId == "refresh") {
        // 刷新显卡信息和系统语言环境
        m_appletWidget->setCardName();
        m_appletWidget->setLocale();
        m_appletWidget->refreshButton();
        m_pluginWidget->getInfo(m_appletWidget);
    }
    else if(menuId == "setting") {
        // 这里还可以使用 dbus 调用控制中心
        // dbus-send --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter --print-reply com.deepin.dde.ControlCenter.ShowModule string:"display"
        system("dde-control-center -m display");
    }
    else if(menuId == "nvidia") {
        // 这个需要用户自行安装 nvidia-settings
        system("nvidia-settings");
    }
}

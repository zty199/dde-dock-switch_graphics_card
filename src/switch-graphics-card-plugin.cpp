#include "switch-graphics-card-plugin.h"

#include <DDBusSender>

#define PLUGIN_STATE_KEY    "enable"

SwitchGraphicsCardPlugin::SwitchGraphicsCardPlugin(QObject *parent)
    : QObject(parent)
    , process(new QProcess)
    , m_pluginLoaded(false)
    , ts(new QTranslator)
{
    updateTranslator();
}

const QString SwitchGraphicsCardPlugin::pluginName() const
{
    return QStringLiteral("datetime");
}

const QString SwitchGraphicsCardPlugin::pluginDisplayName() const
{
    return QString(tr("Switch Graphics Card"));
}

void SwitchGraphicsCardPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    // 如果插件没有被禁用则在初始化插件时才添加主控件到面板上
    if (!pluginIsDisable())
    {
        loadPlugin();
    }
}

bool SwitchGraphicsCardPlugin::pluginIsAllowDisable()
{
    // 通知 dde-dock 本插件允许禁用
    return true;
}

bool SwitchGraphicsCardPlugin::pluginIsDisable()
{
    // 第二个参数 "enable" 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认启用
    return !(m_proxyInter->getValue(this, PLUGIN_STATE_KEY, true).toBool());
}

void SwitchGraphicsCardPlugin::pluginStateSwitched()
{
    // 获取当前插件启用状态
    m_proxyInter->saveValue(this, PLUGIN_STATE_KEY, pluginIsDisable());

    refreshPluginItemsVisible();
}

// dock 栏插件显示
QWidget *SwitchGraphicsCardPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey)

    // 添加 pluginWidget 到 dde-dock 上
    return this->m_pluginWidget;
}

// 鼠标悬停时显示信息
QWidget *SwitchGraphicsCardPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey)

    return this->m_tipsWidget;
}

// 单击插件弹出选项框
QWidget *SwitchGraphicsCardPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey)

    return this->m_appletWidget;
}

const QString SwitchGraphicsCardPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey)

    QList<QVariant> items;
    items.reserve(3);

    QMap<QString, QVariant> graphicsRefresh;
    graphicsRefresh["itemId"] = "graphics-refresh";
    graphicsRefresh["itemText"] = tr("Refresh");
    graphicsRefresh["isActive"] = true;
    items.push_back(graphicsRefresh);

    QMap<QString, QVariant> displaySettings;
    displaySettings["itemId"] = "display-settings";
    displaySettings["itemText"] = tr("Display Settings");
    displaySettings["isActive"] = true;
    items.push_back(displaySettings);

    QMap<QString, QVariant> nvidiaSettings;
    nvidiaSettings["itemId"] = "nvidia-settings";
    nvidiaSettings["itemText"] = tr("Run nvidia-settings");
    nvidiaSettings["isActive"] = true;
    items.push_back(nvidiaSettings);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void SwitchGraphicsCardPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey)
    Q_UNUSED(checked)

    // 根据上面接口设置的 id 执行不同的操作
    if(menuId == "graphics-refresh")
    {
        // 刷新显卡信息
        m_appletWidget->setCardName();
        m_appletWidget->refreshButton();
        m_pluginWidget->getInfo(m_appletWidget);
    }
    else if(menuId == "display-settings")
    {
        // 使用 dbus 调用控制中心
        // dbus-send --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter --print-reply com.deepin.dde.ControlCenter.ShowModule string:"display"

        DDBusSender()
                .service("com.deepin.dde.ControlCenter")
                .interface("com.deepin.dde.ControlCenter")
                .path("/com/deepin/dde/ControlCenter")
                .method(QString("ShowModule"))
                .arg(QString("display"))
                .call();
    }
    else if(menuId == "nvidia-settings")
    {
        // 需要用户自行安装 nvidia-settings
        process->start("nvidia-settings", QStringList());
    }
}

void SwitchGraphicsCardPlugin::displayModeChanged(const Dock::DisplayMode displayMode)
{
    Q_UNUSED(displayMode)

    if(!pluginIsDisable())
    {
        m_pluginWidget->update();
    }
}

int SwitchGraphicsCardPlugin::itemSortKey(const QString &itemKey)
{
    const QString key = QString("pos_%1_%2").arg(itemKey).arg(Dock::Efficient);
    return m_proxyInter->getValue(this, key, 4).toInt();
}

void SwitchGraphicsCardPlugin::setSortKey(const QString &itemKey, const int order)
{
    const QString key = QString("pos_%1_%2").arg(itemKey).arg(Dock::Efficient);
    m_proxyInter->saveValue(this, key, order);
}

void SwitchGraphicsCardPlugin::pluginSettingsChanged()
{
    refreshPluginItemsVisible();
}

void SwitchGraphicsCardPlugin::loadPlugin()
{
    if(m_pluginLoaded)
    {
        qDebug() << "graphics plugin has been loaded! return";
        return;
    }

    m_pluginLoaded = true;

    m_pluginWidget = new SwitchGraphicsCardWidget;
    m_tipsWidget = new Dock::TipsWidget;
    m_appletWidget = new SwitchGraphicsCardAppletWidget;

    // 初始化显卡信息
    m_pluginWidget->getInfo(m_appletWidget);

    // 初始化 tipsWidget 信息
    m_tipsWidget->setVisible(false);
    m_tipsWidget->setAccessibleName("Switch Graphics Card");
    m_tipsWidget->setText(tr("Current: ") + m_appletWidget->getCardName());

    m_proxyInter->itemAdded(this, pluginName());
    displayModeChanged(displayMode());
}

void SwitchGraphicsCardPlugin::refreshPluginItemsVisible()
{
    if(pluginIsDisable())
    {
        m_proxyInter->itemRemoved(this, pluginName());
    }
    else
    {
        if(!m_pluginLoaded)
        {
            loadPlugin();
            return;
        }
        m_proxyInter->itemAdded(this, pluginName());
    }
}

void SwitchGraphicsCardPlugin::updateTranslator()
{
    if(QLocale::system().name().split("_").at(0) == "zh")
    {
        ts->load("zh_CN.qm", ":/translations/translations");
        QCoreApplication::installTranslator(ts);
    }
}

#include "switchgraphicscardplugin.h"
#include "tipswidget.h"
#include "switchgraphicscardappletwidget.h"
#include "common.h"
#include "utils.h"

#include <DDBusSender>

SwitchGraphicsCardPlugin::SwitchGraphicsCardPlugin(QObject *parent)
    : QObject(parent)
{
    updateTranslator();
}

const QString SwitchGraphicsCardPlugin::pluginName() const
{
    return kPluginName;
}

const QString SwitchGraphicsCardPlugin::pluginDisplayName() const
{
    return QString(QObject::tr("Switch Graphics Card"));
}

void SwitchGraphicsCardPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    // 如果插件没有被禁用则在初始化插件时才添加主控件到面板上
    if (!pluginIsDisable()) {
        loadPlugin();
    }
}

// dock 栏插件显示（V23中作用未知）
QWidget *SwitchGraphicsCardPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey)
    return nullptr;
}

// 鼠标悬停时显示信息
QWidget *SwitchGraphicsCardPlugin::itemTipsWidget(const QString &itemKey)
{
    if (itemKey != kPluginName) {
        return nullptr;
    }

    return m_tipsWidget.data();
}

// 单击插件弹出选项框
QWidget *SwitchGraphicsCardPlugin::itemPopupApplet(const QString &itemKey)
{
    if (itemKey == kPluginName || itemKey == QUICK_ITEM_KEY) {
        return m_appletWidget.data();
    }

    return nullptr;
}

const QString SwitchGraphicsCardPlugin::itemContextMenu(const QString &itemKey)
{
    if (itemKey != kPluginName) {
        return QString();
    }

    QVariantList items;
    items.reserve(3);

    QVariantMap graphicsRefresh;
    graphicsRefresh.insert("itemId", "graphics-refresh");
    graphicsRefresh.insert("itemText", QObject::tr("Refresh"));
    graphicsRefresh.insert("isActive", true);
    items.append(graphicsRefresh);

    QVariantMap displaySettings;
    displaySettings.insert("itemId", "display-settings");
    displaySettings.insert("itemText", QObject::tr("Display Settings"));
    displaySettings.insert("isActive", true);
    items.append(displaySettings);

    QVariantMap nvidiaSettings;
    nvidiaSettings.insert("itemId", "nvidia-settings");
    nvidiaSettings.insert("itemText", QObject::tr("Run nvidia-settings"));
    nvidiaSettings.insert("isActive", true);
    items.append(nvidiaSettings);

    QVariantMap menu;
    menu.insert("items", items);
    menu.insert("checkableMenu", false);
    menu.insert("singleCheck", false);

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void SwitchGraphicsCardPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(checked)

    if (itemKey != kPluginName) {
        return;
    }

    // 根据上面接口设置的 id 执行不同的操作
    if (menuId == "graphics-refresh") {
        // 刷新显卡信息
        Singleton<SwitchGraphicsCardItem>::instance()->refresh();
    } else if (menuId == "display-settings") {
        // 使用 dbus 调用控制中心
        DDBusSender()
            .service("com.deepin.dde.ControlCenter")
            .path("/com/deepin/dde/ControlCenter")
            .interface("com.deepin.dde.ControlCenter")
            .method(QString("ShowModule"))
            .arg(QString("display"))
            .call();
    } else if (menuId == "nvidia-settings") {
        // 使用 dbus 调用 AM 运行 nvidia-settings
        // 需要用户自行安装 nvidia-settings
        DDBusSender()
            .service("org.desktopspec.ApplicationManager1")
            .path("/org/desktopspec/ApplicationManager1/nvidia_2dsettings")
            .interface("org.desktopspec.ApplicationManager1.Application")
            .method(QString("Launch"))
            .arg(QString())
            .arg(QStringList())
            .arg(QVariantMap())
            .call();
    }
}

int SwitchGraphicsCardPlugin::itemSortKey(const QString &itemKey)
{
    const QString key = QString("pos_%1_%2").arg(itemKey).arg(Dock::Efficient);
    return m_proxyInter->getValue(this, key, 0).toInt();
}

void SwitchGraphicsCardPlugin::setSortKey(const QString &itemKey, const int order)
{
    const QString key = QString("pos_%1_%2").arg(itemKey).arg(Dock::Efficient);
    m_proxyInter->saveValue(this, key, order);
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
    return !m_proxyInter->getValue(this, kPluginStateKey, true).toBool();
}

void SwitchGraphicsCardPlugin::pluginStateSwitched()
{
    // 获取当前插件启用状态
    m_proxyInter->saveValue(this, kPluginStateKey, pluginIsDisable());

    refreshPluginItemsVisible();
}

void SwitchGraphicsCardPlugin::pluginSettingsChanged()
{
    refreshPluginItemsVisible();
}

PluginsItemInterface::PluginMode SwitchGraphicsCardPlugin::status() const
{
    return PluginMode::Active;
}

QIcon SwitchGraphicsCardPlugin::icon(const DockPart &dockPart, DGuiApplicationHelper::ColorType themeType)
{
    QString iconName;
    QSize iconSize;

    switch (dockPart) {
    case DockPart::DCCSetting:
        iconName = kDefaultIconName;
        iconSize = QSize(PLUGIN_ICON_MIN_SIZE, PLUGIN_ICON_MIN_SIZE);
        break;
    case DockPart::QuickShow:
        if (Singleton<SwitchGraphicsCardItem>::instance()->cardName() == "Intel") {
            iconName = kIntelIconName;
        } else if (Singleton<SwitchGraphicsCardItem>::instance()->cardName() == "NVIDIA") {
            iconName = kNvidiaIconName;
        } else {
            iconName = kDefaultIconName;
        }
        iconSize = QSize(PLUGIN_ICON_MIN_SIZE, PLUGIN_ICON_MIN_SIZE);
        break;
    default:
        break;
    }

    if (iconName.isEmpty()) {
        return QIcon();
    }

    if (themeType == DGuiApplicationHelper::ColorType::LightType) {
        iconName += PLUGIN_MIN_ICON_NAME;
    }

    return Utils::loadSVG(QString(":/icons/%1.svg").arg(iconName), iconSize);
}

PluginFlags SwitchGraphicsCardPlugin::flags() const
{
    return PluginFlag::Type_Common
           | PluginFlag::Attribute_CanDrag
           | PluginFlag::Attribute_CanInsert
           | PluginFlag::Attribute_CanSetting;
}

void SwitchGraphicsCardPlugin::loadPlugin()
{
    if (m_pluginLoaded) {
        qDebug().noquote() << "Plugin switch-graphics-card has been loaded";
        return;
    }

    m_pluginLoaded = true;

    m_tipsWidget.reset(new Dock::TipsWidget);
    m_tipsWidget->setAccessibleName(pluginDisplayName());
    m_tipsWidget->setText(QObject::tr("Initializing"));
    m_appletWidget.reset(new SwitchGraphicsCardAppletWidget);

    connect(Singleton<SwitchGraphicsCardItem>::instance(), &SwitchGraphicsCardItem::sigStatusChanged, this, &SwitchGraphicsCardPlugin::slotInitializationStatusChanged);

    m_proxyInter->itemAdded(this, pluginName());

    QMetaObject::invokeMethod(Singleton<SwitchGraphicsCardItem>::instance(), &SwitchGraphicsCardItem::refresh, Qt::QueuedConnection);
}

void SwitchGraphicsCardPlugin::refreshPluginItemsVisible()
{
    if (pluginIsDisable()) {
        m_proxyInter->itemRemoved(this, pluginName());
    } else {
        if (!m_pluginLoaded) {
            loadPlugin();
            return;
        }
        m_proxyInter->itemAdded(this, pluginName());
    }
}

void SwitchGraphicsCardPlugin::updateTranslator()
{
    m_translator.reset(new QTranslator);

    m_translator->load(QLocale::system(), QString(), QString(), ":/translations", ".qm");
    QCoreApplication::installTranslator(m_translator.data());
}

void SwitchGraphicsCardPlugin::slotInitializationStatusChanged(SwitchGraphicsCardItem::Status status)
{
    QString cardName;

    switch (status) {
    case SwitchGraphicsCardItem::Initializing:
        m_tipsWidget->setText(QObject::tr("Initializing"));
        return;
    case SwitchGraphicsCardItem::InitializeFailed:
        cardName = "Unknown";
        break;
    case SwitchGraphicsCardItem::InitializeFinished:
        cardName = Singleton<SwitchGraphicsCardItem>::instance()->cardName();
        break;
    }

    m_tipsWidget->setText(QObject::tr("Current: %1").arg(cardName));

    // NOTE: 主动刷新 QuickShow item 图标
    m_proxyInter->itemUpdate(this, pluginName());
}

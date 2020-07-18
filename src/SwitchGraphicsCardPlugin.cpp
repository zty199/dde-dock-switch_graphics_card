#include "SwitchGraphicsCardPlugin.h"

SwitchGraphicsCardPlugin::SwitchGraphicsCardPlugin(QObject *parent)
    : QObject(parent)
{

}

const QString SwitchGraphicsCardPlugin::pluginName() const
{
    return QStringLiteral("Switch Graphics Card");
}

void SwitchGraphicsCardPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;
    
    m_pluginWidget = new SwitchGraphicsCardWidget;
    m_tipsWidget = new QLabel;
    m_appletWidget = new SwitchGraphicsCardAppletWidget;

    m_proxyInter->itemAdded(this, pluginName());
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
    m_tipsWidget->setText(m_appletWidget->GetCardName());

    return this->m_tipsWidget;
}

// 单击插件弹出选项框
QWidget *SwitchGraphicsCardPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return this->m_appletWidget;
}

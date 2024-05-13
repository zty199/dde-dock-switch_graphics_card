#include "switchgraphicscardappletwidget.h"
#include "switchgraphicscarditem.h"

#include <QLayout>

#include <DNotifySender>

SwitchGraphicsCardAppletWidget::SwitchGraphicsCardAppletWidget(QWidget *parent)
    : QWidget(parent)
    , m_intelButton(new Dtk::Widget::DPushButton(this))
    , m_nvidiaButton(new Dtk::Widget::DPushButton(this))
{
    initUI();
    initConnections();
}

SwitchGraphicsCardAppletWidget::~SwitchGraphicsCardAppletWidget()
{
}

void SwitchGraphicsCardAppletWidget::initUI()
{
    // 设置左键点击弹出气泡大小
    resize(150, 80);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(2);
    // 设置按钮大小、位置和文字
    m_intelButton->resize(130, 28);
    layout->addWidget(m_intelButton);

    m_nvidiaButton->resize(130, 28);
    layout->addWidget(m_nvidiaButton);

    m_intelButton->setText(QObject::tr("Intel Graphics"));
    m_nvidiaButton->setText(QObject::tr("NVIDIA Graphics"));
}

void SwitchGraphicsCardAppletWidget::initConnections()
{
    connect(m_intelButton, &Dtk::Widget::DPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::slotIntelButtonClicked);
    connect(m_nvidiaButton, &Dtk::Widget::DPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::slotNvidiaButtonClicked);
}

void SwitchGraphicsCardAppletWidget::slotIntelButtonClicked()
{
    if (Singleton<SwitchGraphicsCardItem>::instance()->status() != SwitchGraphicsCardItem::InitializeFinished) {
        Dtk::Core::DUtil::DNotifySender(QObject::tr(R"(Unknown graphics card, please try to "Refresh")"))
            .appIcon("deepin-graphics-driver-manager")
            .appName("dde-dock-graphics-plugin")
            .timeOut(3000)
            .call();
        return;
    }

    if (Singleton<SwitchGraphicsCardItem>::instance()->cardName() == "Intel") {
        Dtk::Core::DUtil::DNotifySender(QObject::tr("Intel graphics is already in use"))
            .appIcon("deepin-graphics-driver-manager")
            .appName("dde-dock-graphics-plugin")
            .timeOut(3000)
            .call();
        return;
    }

    Dtk::Core::DUtil::DNotifySender(QObject::tr("Preparing to switch graphics card and logout, please save your work in progress in time"))
        .appIcon("deepin-graphics-driver-manager")
        .appName("dde-dock-graphics-plugin")
        .call();

    /**
     * WARNING: 此处需要保证 QProcess 不被销毁，且无法使用 startDetached，
     * 否则调用 pkexec 存在错误 Refusing to render service to dead parents.
     */
    QProcess *process = new QProcess(this);
    process->start("/usr/bin/pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::slotNvidiaButtonClicked()
{
    if (Singleton<SwitchGraphicsCardItem>::instance()->status() != SwitchGraphicsCardItem::InitializeFinished) {
        Dtk::Core::DUtil::DNotifySender(QObject::tr(R"(Unknown graphics card, please try to "Refresh")"))
            .appIcon("deepin-graphics-driver-manager")
            .appName("dde-dock-graphics-plugin")
            .timeOut(3000)
            .call();
        return;
    }

    if (Singleton<SwitchGraphicsCardItem>::instance()->cardName() == "NVIDIA") {
        Dtk::Core::DUtil::DNotifySender(QObject::tr("NVIDIA graphics is already in use"))
            .appIcon("deepin-graphics-driver-manager")
            .appName("dde-dock-graphics-plugin")
            .timeOut(3000)
            .call();
        return;
    }

    Dtk::Core::DUtil::DNotifySender(QObject::tr("Preparing to switch graphics card and logout, please save your work in progress in time"))
        .appIcon("deepin-graphics-driver-manager")
        .appName("dde-dock-graphics-plugin")
        .call();

    /**
     * WARNING: 此处需要保证 QProcess 不被销毁，且无法使用 startDetached，
     * 否则调用 pkexec 存在错误 Refusing to render service to dead parents.
     */
    QProcess *process = new QProcess(this);
    process->start("/usr/bin/pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/NVIDIA.sh");
}

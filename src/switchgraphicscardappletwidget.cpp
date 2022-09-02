#include "switchgraphicscardappletwidget.h"

#include <DNotifySender>

DCORE_USE_NAMESPACE

SwitchGraphicsCardAppletWidget::SwitchGraphicsCardAppletWidget(QWidget *parent)
    : QWidget(parent)
    , m_intelButton(new DPushButton(this))
    , m_nvidiaButton(new DPushButton(this))
    , m_process(new QProcess(this))
{
    initUI();
    initConnections();

    setCardName();
}

SwitchGraphicsCardAppletWidget::~SwitchGraphicsCardAppletWidget()
{
}

void SwitchGraphicsCardAppletWidget::setCardName()
{
    // 获取当前显卡信息
    m_process->start("bash", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/CheckGraphics.sh");
    m_process->waitForFinished(-1);
    m_cardName = m_process->readAllStandardOutput().trimmed();
    m_process->close();
}

QString SwitchGraphicsCardAppletWidget::getCardName() const
{
    return m_cardName;
}

void SwitchGraphicsCardAppletWidget::updateButtonText()
{
    m_intelButton->setText(QObject::tr("Intel Graphics"));
    m_nvidiaButton->setText(QObject::tr("NVIDIA Graphics"));
}

void SwitchGraphicsCardAppletWidget::initUI()
{
    // 设置左键点击弹出气泡大小
    resize(150, 60);

    // 设置按钮大小位置和文字
    m_intelButton->resize(148, 28);
    m_intelButton->move(1, 1);

    m_nvidiaButton->resize(148, 28);
    m_nvidiaButton->move(1, 30);

    updateButtonText();
}

void SwitchGraphicsCardAppletWidget::initConnections()
{
    connect(m_intelButton, &DPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::slotIntelButtonClicked);
    connect(m_nvidiaButton, &DPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::slotNvidiaButtonClicked);
}

void SwitchGraphicsCardAppletWidget::slotIntelButtonClicked()
{
    if (m_cardName == "Intel") {
        DUtil::DNotifySender(QObject::tr("Intel graphics is already in use")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        return;
    }

    DUtil::DNotifySender(QObject::tr("Preparing to switch graphics card and logout, please save your work in progress in time")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();

    QProcess process;
    process.startDetached("pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::slotNvidiaButtonClicked()
{
    if (m_cardName == "NVIDIA") {
        DUtil::DNotifySender(QObject::tr("NVIDIA graphics is already in use")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        return;
    }

    DUtil::DNotifySender(QObject::tr("Preparing to switch graphics card and logout, please save your work in progress in time")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();

    QProcess process;
    process.startDetached("pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/NVIDIA.sh");
}

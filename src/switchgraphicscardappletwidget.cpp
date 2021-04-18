#include "switchgraphicscardappletwidget.h"

#include <DNotifySender>

SwitchGraphicsCardAppletWidget::SwitchGraphicsCardAppletWidget(QWidget *parent)
    : QWidget(parent)
    , btn_intel(new QPushButton(this))
    , btn_nvidia(new QPushButton(this))
    , process(new QProcess)
{
    // 设置左键点击弹出气泡大小
    resize(150, 60);

    // 设置按钮大小位置和文字
    btn_intel->resize(148, 28);
    btn_intel->move(1, 1);

    btn_nvidia->resize(148, 28);
    btn_nvidia->move(1, 30);

    setCardName();
    refreshButton();

    connect(btn_intel, &QPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::switchIntel);
    connect(btn_nvidia, &QPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::switchNVIDIA);
}

void SwitchGraphicsCardAppletWidget::setCardName()
{
    // 获取当前显卡信息
    process->start("sh", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/CheckGraphics.sh");
    process->waitForFinished();
    m_cardName = process->readAllStandardOutput();
    process->close();
    m_cardName.chop(1);
}

QString SwitchGraphicsCardAppletWidget::getCardName()
{
    return this->m_cardName;
}

void SwitchGraphicsCardAppletWidget::switchIntel()
{
    if(this->m_cardName == "Intel")
    {
        Dtk::Core::DUtil::DNotifySender(tr("Intel graphics is already in use")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        return;
    }

    Dtk::Core::DUtil::DNotifySender(tr("Preparing to switch graphics card and logout, please save your work in progress in time")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();

    // 非阻塞调用外部脚本，不需要等待结束
    process->start("pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::switchNVIDIA()
{
    if(this->m_cardName == "NVIDIA")
    {
        Dtk::Core::DUtil::DNotifySender(tr("NVIDIA graphics is already in use")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        return;
    }

    Dtk::Core::DUtil::DNotifySender(tr("Preparing to switch graphics card and logout, please save your work in progress in time")).appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();

    process->start("pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/NVIDIA.sh");
}

void SwitchGraphicsCardAppletWidget::refreshButton()
{
    btn_intel->setText(tr("Intel Graphics"));
    btn_nvidia->setText(tr("NVIDIA Graphics"));
}

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
    setLocale();
    refreshButton();

    connect(btn_intel, &QPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::switchIntel);
    connect(btn_nvidia, &QPushButton::clicked, this, &SwitchGraphicsCardAppletWidget::switchNVIDIA);
}

void SwitchGraphicsCardAppletWidget::setCardName()
{
    // 获取当前显卡信息
    process->start("/opt/apps/dde-dock-graphics-plugin/files/bin/CheckGraphics.sh", QStringList());
    process->waitForFinished();
    m_cardName = process->readAllStandardOutput();
    process->close();
    m_cardName.chop(1);
}

QString SwitchGraphicsCardAppletWidget::getCardName()
{
    return this->m_cardName;
}

void SwitchGraphicsCardAppletWidget::setLocale()
{
    // 获取系统语言环境
    m_locale = QLocale::system().name().split("_").at(0);
}

QString SwitchGraphicsCardAppletWidget::getLocale()
{
    return this->m_locale;
}

void SwitchGraphicsCardAppletWidget::switchIntel()
{
    if(this->m_cardName == "Intel")
    {
        if(this->m_locale == "zh")
        {
            // 使用 notify-send 向通知中心发送系统通知
            Dtk::Core::DUtil::DNotifySender("已经是 Intel 显卡").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        }
        else
        {
            Dtk::Core::DUtil::DNotifySender("Intel graphics is already in use").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        }
        return;
    }

    if(this->m_locale == "zh")
    {
        Dtk::Core::DUtil::DNotifySender("即将切换显卡并注销登录，请及时保存您的工作进度").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(3000).call();
        Dtk::Core::DUtil::DNotifySender("正在刷新内核参数，请稍后...").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();
    }
    else
    {
        Dtk::Core::DUtil::DNotifySender("Preparing to switch graphics card and logout, please save your work in progress in time").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(3000).call();
        Dtk::Core::DUtil::DNotifySender("Updating initramfs, please wait...").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();
    }

    // 非阻塞调用外部脚本，不需要等待结束
    process->start("pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::switchNVIDIA()
{
    if(this->m_cardName == "NVIDIA")
    {
        if(this->m_locale == "zh")
        {
            Dtk::Core::DUtil::DNotifySender("已经是 NVIDIA 显卡").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        }
        else
        {
            Dtk::Core::DUtil::DNotifySender("NVIDIA graphics is already in use").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(2000).call();
        }
        return;
    }

    if(this->m_locale == "zh")
    {
        Dtk::Core::DUtil::DNotifySender("即将切换显卡并注销登录，请及时保存您的工作进度").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(3000).call();
        Dtk::Core::DUtil::DNotifySender("正在刷新内核参数，请稍后...").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();
    }
    else
    {
        Dtk::Core::DUtil::DNotifySender("Preparing to switch graphics card and logout, please save your work in progress in time").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").timeOut(3000).call();
        Dtk::Core::DUtil::DNotifySender("Updating initramfs, please wait...").appIcon("deepin-graphics-driver-manager").appName("dde-dock-graphics-plugin").call();
    }

    process->start("pkexec", QStringList() << "/opt/apps/dde-dock-graphics-plugin/files/bin/NVIDIA.sh");
}

void SwitchGraphicsCardAppletWidget::refreshButton()
{
    if(this->m_locale == "zh")
    {
        btn_intel->setText("切换 Intel 显卡");
        btn_nvidia->setText("切换 NVIDIA 显卡");
    }
    else
    {
        btn_intel->setText("Intel Graphics");
        btn_nvidia->setText("NVIDIA Graphics");
    }
}

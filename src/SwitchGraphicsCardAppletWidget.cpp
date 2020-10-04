#include "SwitchGraphicsCardAppletWidget.h"

SwitchGraphicsCardAppletWidget::SwitchGraphicsCardAppletWidget(QWidget *parent) : 
        QWidget(parent),
        RefreshTimer(new QTimer(this))
{
    process = new QProcess();

    // 设置左键点击弹出气泡大小
    resize(150, 60);

    // 设置按钮大小和位置
    Intel = new QPushButton(this);
    Intel->resize(148, 28);
    Intel->move(1, 1);

    NVIDIA = new QPushButton(this);
    NVIDIA->resize(148, 28);
    NVIDIA->move(1, 30);

    connect(Intel, SIGNAL(clicked(bool)), this, SLOT(switchIntel()));
    connect(NVIDIA, SIGNAL(clicked(bool)), this, SLOT(switchNVIDIA()));

    /* 可以设置定时刷新 */
    // 连接 Timer 超时的信号到更新数据的槽上
    //connect(RefreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardAppletWidget::setCardName);
    //connect(RefreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardAppletWidget::setLocale);
    //connect(RefreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardAppletWidget::refreshButton);

    // 设置 Timer 超时为 10s，即每 10s 更新一次控件上的数据，并启动这个定时器
    //RefreshTimer->start(10000);

    //setCardName();
    //setLocale();
    //refreshButton();
}

void SwitchGraphicsCardAppletWidget::setCardName()
{
    // 获取当前显卡信息
    process->start("/opt/apps/dde-dock-graphics-plugin/files/bin/CheckGraphics.sh");
    process->waitForFinished();
    CardName = process->readAllStandardOutput();
    process->close();
    CardName.chop(1);
}

QString SwitchGraphicsCardAppletWidget::getCardName()
{
    return this->CardName;
}

void SwitchGraphicsCardAppletWidget::setLocale()
{
    // 获取系统语言环境（如果直接使用 QProcess 执行 locale 命令，会受到 tty 环境配置影响，原因未知）
    process->start("/opt/apps/dde-dock-graphics-plugin/files/bin/CheckLocale.sh");
    process->waitForFinished();
    Locale = process->readAllStandardOutput();
    process->close();
    Locale.chop(1);
}

QString SwitchGraphicsCardAppletWidget::getLocale()
{
    return this->Locale;
}

void SwitchGraphicsCardAppletWidget::switchIntel()
{
    if(this->CardName == "Intel")
    {
        if(this->Locale == "zh")
        {
            // QMessageBox::warning(NULL, "警告", "已经是 Intel 显卡！");
            // 使用 notify-send 向通知中心发送系统通知
            system("notify-send -t 2000 -a dde-dock-graphics-plugin -i dialog-warning \"已经是 Intel 显卡\"");
        }
        else
        {
            // QMessageBox::warning(NULL, "Warning", "Intel graphics is already in use!");
            system("notify-send -t 2000 -a dde-dock-graphics-plugin -i dialog-warning \"Intel graphics is already in use\"");
        }
        return;
    }

    if(this->Locale == "zh")
    {
        system("notify-send -t 3000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"即将切换显卡并注销登录，请及时保存您的工作进度\"");
        system("notify-send -t 10000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"正在刷新内核参数，请稍后...\"");
    }
    else
    {
        system("notify-send -t 3000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"Preparing to switch graphics card and logout, please save your work in progress in time\"");
        system("notify-send -t 10000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"Updating initramfs, please wait...\"");
    }
    system("pkexec /opt/apps/dde-dock-graphics-plugin/files/bin/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::switchNVIDIA()
{
    if(this->CardName == "NVIDIA")
    {
        if(this->Locale == "zh")
        {
            // QMessageBox::warning(NULL, "警告", "已经是 NVIDIA 显卡！");
            system("notify-send -t 2000 -a dde-dock-graphics-plugin -i dialog-warning \"已经是 NVIDIA 显卡\"");
        }
        else
        {
            // QMessageBox::warning(NULL, "Warning", "NVIDIA graphics is already in use!");
            system("notify-send -t 2000 -a dde-dock-graphics-plugin -i dialog-warning \"NVIDIA graphics is already in use\"");
        }
        return;
    }

    if(this->Locale == "zh")
    {
        system("notify-send -t 3000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"即将切换显卡并注销登录，请及时保存您的工作进度\"");
        system("notify-send -t 10000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"正在刷新内核参数，请稍后...\"");
    }
    else
    {
        system("notify-send -t 3000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"Preparing to switch graphics card and logout, please save your work in progress in time\"");
        system("notify-send -t 10000 -a dde-dock-graphics-plugin -i deepin-graphics-driver-manager \"Updating initramfs, please wait...\"");
    }
    system("pkexec /opt/apps/dde-dock-graphics-plugin/files/bin/NVIDIA.sh");
}

void SwitchGraphicsCardAppletWidget::refreshButton()
{
    if(this->Locale == "zh")
    {
        Intel->setText("切换 Intel 显卡");
        NVIDIA->setText("切换 NVIDIA 显卡");
    }
    else
    {
        Intel->setText("Intel Graphics");
        NVIDIA->setText("NVIDIA Graphics");
    }
}

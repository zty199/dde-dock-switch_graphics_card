#include "SwitchGraphicsCardAppletWidget.h"

SwitchGraphicsCardAppletWidget::SwitchGraphicsCardAppletWidget(QWidget *parent) : 
        QWidget(parent),
        RefreshTimer(new QTimer(this))
{
    resize(150, 60);

    IntelCard = new QPushButton(this);
    IntelCard->resize(148, 28);
    IntelCard->move(1, 1);
    if(GetLocale() == "zh")
        IntelCard->setText("切换 Intel 显卡");
    else
        IntelCard->setText("Intel Graphics");

    NvidiaCard = new QPushButton(this);
    NvidiaCard->resize(148, 28);
    NvidiaCard->move(1, 30);
    if(GetLocale() == "zh")
        NvidiaCard->setText("切换 NVIDIA 显卡");
    else
        NvidiaCard->setText("NVIDIA Graphics");

    // 连接 Timer 超时的信号到更新数据的槽上
    connect(RefreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardAppletWidget::UpdateGraphicsInfo);
    connect(IntelCard, SIGNAL(clicked(bool)), this, SLOT(SwitchIntel()));
    connect(NvidiaCard, SIGNAL(clicked(bool)), this, SLOT(SwitchNvidia()));

    // 设置 Timer 超时为 10s，即每 10s 更新一次控件上的数据，并启动这个定时器
    RefreshTimer->start(10000);

    UpdateGraphicsInfo();
}

QString SwitchGraphicsCardAppletWidget::GetCardName()
{
    return this->CardName;
}

QString SwitchGraphicsCardAppletWidget::GetLocale()
{
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + LocalePath);
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();
    Config.close();
    locale = QString(TextByte);

    return this->locale;
}

void SwitchGraphicsCardAppletWidget::SwitchIntel()
{
    if(this->CardName == "Intel")
    {
        if(GetLocale() == "zh")
            QMessageBox::warning(NULL, "警告", "已经是 Intel 显卡！");
        else
            QMessageBox::warning(NULL, "Warning", "Intel graphics is already in use!");
        return;
    }

    system("pkexec /opt/apps/dde-dock-graphics-plugin/files/bin/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::SwitchNvidia()
{
    if(this->CardName == "NVIDIA")
    {
        if(GetLocale() == "zh")
            QMessageBox::warning(NULL, "警告", "已经是 NVIDIA 显卡！");
        else {
            QMessageBox::warning(NULL, "Warning", "NVIDIA graphics is already in use!");
        }
        return;
    }

    system("pkexec /opt/apps/dde-dock-graphics-plugin/files/bin/NVIDIA.sh");
}

void SwitchGraphicsCardAppletWidget::UpdateGraphicsInfo()
{
    // 刷新显卡信息
    system("/opt/apps/dde-dock-graphics-plugin/files/bin/CheckConf.sh");
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();
    Config.close();
    CardName = QString(TextByte);
}
